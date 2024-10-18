// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSubsystem.h"

void UDamageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("Damage Subsystem Initialized Successfully"));
}

float UDamageSubsystem::CalculateDamage(EDamageType Type, float Value, const FDamageResistanceData& ResistanceData)
{
	if (ResistanceData.DamageMultipliers.Contains(Type))
	{
		Value *= ResistanceData.DamageMultipliers[Type];
	}
	return Value * Settings->GlobalDamageMultiplier;
}
