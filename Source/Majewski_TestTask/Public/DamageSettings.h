// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DamageEnums.h"
#include "DamageTypeInputData.h"
#include "DamageSettings.generated.h"

class ASpecializedProjectile;

/**
 * The main file for designers to modify in order to balance the gameplay. Makes it easy to maintain and keep track of,
 * and the fact that it's referenced in a Subsystem makes sure that this file is accessible easily both from C++ and BP
 * so that elements of this system (in this case DamageSystem) can read those values. 
 */
UCLASS()
class MAJEWSKI_TESTTASK_API UDamageSettings : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Maps a projectile class a gun should spawn depending on the damage type of said gun
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EDamageType, TSubclassOf<ASpecializedProjectile>> ProjectilesForDamageTypes;

	// Global max health value that should not be exceeded when healing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 100.f;

	// Just some example balancing setting value to show the wider purpose of this data asset
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GlobalDamageMultiplier = 1.f;

	// Defines the inputs related to switching damage types on applicable guns
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FDamageTypeInputData> DamageTypeInputs;

	// The Input Context containing Damage System-related inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	class UInputMappingContext* InputMappingContext;
};
