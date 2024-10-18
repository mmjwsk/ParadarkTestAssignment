// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DamageSettings.h"
#include "DamageResistanceData.h"
#include "DamageEnums.h"
#include "DamageSubsystem.generated.h"

/**
 * Usage of Subsystem in a task of this size may seem like an overkill as basically all of its current responsibilities could be
 * handled from within the DamageSystemComponent but it's really beneficial for scalability in larger projects - and that was one of the goals
 */
UCLASS(Abstract, Blueprintable)
class MAJEWSKI_TESTTASK_API UDamageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UDamageSubsystem() { }
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDamageSettings> Settings;
	
public:
	UFUNCTION(BlueprintPure)
	float CalculateDamage(EDamageType Type, float Value, const FDamageResistanceData& ResistanceData);
};
