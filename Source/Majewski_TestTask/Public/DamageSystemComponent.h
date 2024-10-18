// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DamageEnums.h"
#include "DamageData.h"
#include "DamageResistanceData.h"
#include "DamageOverTimeTicker.h"
#include "DamageSystemComponent.generated.h"

class UDamageSubsystem;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAJEWSKI_TESTTASK_API UDamageSystemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UDamageSystemComponent();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDamageResistanceData DamageResistance;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthVisualization();

	UFUNCTION(BlueprintPure)
	float GetHealth(){ return Health; }

	// Handles being damaged by a damage source that can trigger a DoT effect
	void OnReceivedNewDamage(const FDamageData& DamageData);

	// Directly deals damage to the owning actor without additional logic
	void DealDirectDamage(EDamageType Type, float Value);

	void UnregisterDamageTicker(EDamageType TickerType);

private:
	void RegisterDamageTicker(const FDamageData& DamageData);
	void HandleDamageTickerUpdate(const FDamageData& NewDamageData);
	void CheckDeathConditions();
	void CleanupTickers();

private:
	// TMap to make clear the intended design of only one specific DoT source being possibly active at the same time per type,
	// e.g. only one Fire-typed DoT can be active on the same target at the same time
	TMap<EDamageType, TUniquePtr<DamageOverTimeTicker>> DamageOverTimeTickers;

	// Cached to optimize repeated access
	TObjectPtr<UDamageSubsystem> DamageSubsystem;

	float Health;
	TArray<EDamageType> TickersMarkedForDeletion;
};
