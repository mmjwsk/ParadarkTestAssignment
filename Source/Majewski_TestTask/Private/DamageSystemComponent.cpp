// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageSystemComponent.h"
#include "DamageOverTimeTicker.h"
#include "DamageSubsystem.h"

UDamageSystemComponent::UDamageSystemComponent()
{
	// Tick only when necessary for DoT handling so we switch it off by the start to avoid needless ticking
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);
}

void UDamageSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	DamageSubsystem = GetOwner()->GetGameInstance()->GetSubsystem<UDamageSubsystem>();
	Health = DamageSubsystem->Settings->MaxHealth;
	UpdateHealthVisualization();
}

void UDamageSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (const auto& entry : DamageOverTimeTickers)
	{
		entry.Value->Tick(*this, DeltaTime);
	}

	CleanupTickers();
}

void UDamageSystemComponent::OnReceivedNewDamage(const FDamageData& DamageData)
{
	DealDirectDamage(DamageData.DamageType, DamageData.ImmediateDamage);
	HandleDamageTickerUpdate(DamageData);
}

void UDamageSystemComponent::DealDirectDamage(EDamageType Type, float Value)
{
	Value = DamageSubsystem->CalculateDamage(Type, Value, DamageResistance);

	FString LogWord = "damaged";
	if (Value < 0.f)
	{
		LogWord = "healed";
	}
	UE_LOG(LogTemp, Log, TEXT("%s %s for %f from type %s"), *GetOwner()->GetName(), *LogWord, FMath::Abs(Value), *UEnum::GetDisplayValueAsText(Type).ToString());

	// Min to make sure MaxHealth is never exceeded
	Health = FMath::Min(Health - Value, DamageSubsystem->Settings->MaxHealth);

	UpdateHealthVisualization();
	CheckDeathConditions();
}

void UDamageSystemComponent::RegisterDamageTicker(const FDamageData& DamageData)
{
	if (DamageOverTimeTickers.Contains(DamageData.DamageType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to register DoT Ticker of type that is already active. Did you mean to call HandleDamageTickerUpdate instead?"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("DoT effect of type %s registered on %s"), *UEnum::GetDisplayValueAsText(DamageData.DamageType).ToString(), *GetOwner()->GetName());

	DamageOverTimeTickers.Add(DamageData.DamageType, MakeUnique<DamageOverTimeTicker>(DamageData));
	SetComponentTickEnabled(true);
}

void UDamageSystemComponent::UnregisterDamageTicker(EDamageType TickerType)
{
	TickersMarkedForDeletion.Add(TickerType);
}

void UDamageSystemComponent::HandleDamageTickerUpdate(const FDamageData& NewDamageData)
{
	// Handling of countering the DoT e.g. Water damage canceling Fire DoT etc.
	TArray<EDamageType> CounteredTickers;
	for (const auto& TickerPair : DamageOverTimeTickers)
	{
		if (TickerPair.Value->DamageData.bCanBeCancelled
			&& TickerPair.Value->DamageData.DamageOverTimeCancellationType == NewDamageData.DamageType)
		{
			TickersMarkedForDeletion.Add(TickerPair.Value->DamageData.DamageType);
			UE_LOG(LogTemp, Log, TEXT("%s DoT countered by %s"),
				*UEnum::GetDisplayValueAsText(TickerPair.Value->DamageData.DamageType).ToString(),
				*UEnum::GetDisplayValueAsText(NewDamageData.DamageType).ToString());
		}
	}
	for (auto CounteredTickerType : CounteredTickers)
	{
		UE_LOG(LogTemp, Log, TEXT("%s DoT countered by %s"),
			*UEnum::GetDisplayValueAsText(CounteredTickerType).ToString(),
			*UEnum::GetDisplayValueAsText(NewDamageData.DamageType).ToString());

		UnregisterDamageTicker(CounteredTickerType);
	}

	if (NewDamageData.bTriggersDamageOverTime)
	{
		// Duration refreshing - e.g. getting hit by Fire damage while having Fire type DoT already active should not double the
		// effect (e.g. 2 separate "OnFire" statuses) but instead should refresh the duration of the DoT)
		if (DamageOverTimeTickers.Contains(NewDamageData.DamageType))
		{
			DamageOverTimeTickers[NewDamageData.DamageType]->DamageData.DamageOverTimeDuration = NewDamageData.DamageOverTimeDuration;
		}
		else
		{
			RegisterDamageTicker(NewDamageData);
		}
	}
}

void UDamageSystemComponent::CheckDeathConditions()
{
	if (Health <= 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("%s health dropped to 0. Destroying."), *GetOwner()->GetName());
		GetOwner()->Destroy();
	}
}

void UDamageSystemComponent::CleanupTickers()
{
	if (TickersMarkedForDeletion.Num() == 0) return;

	for (auto TickerToCleanUp : TickersMarkedForDeletion)
	{
		if (!DamageOverTimeTickers.Contains(TickerToCleanUp)) continue;

		DamageOverTimeTickers.Remove(TickerToCleanUp);

		if (DamageOverTimeTickers.Num() == 0)
		{
			SetComponentTickEnabled(false);
		}
	}

	TickersMarkedForDeletion.Empty();
}
