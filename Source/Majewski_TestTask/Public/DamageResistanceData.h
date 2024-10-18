// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageEnums.h"
#include "DamageResistanceData.generated.h"

USTRUCT(BlueprintType)
struct MAJEWSKI_TESTTASK_API FDamageResistanceData
{
	GENERATED_BODY()

	/* Maps damage types with the multipliers for its damage type. Note:
	- if damage type is not present here, the multiplier is equal to 1
	- Negative damage multiplier can be used to turn damage into healing
	- Damage multipliers <1 mean damage reduction while damage multipliers >1 mean damage increase (e.g. value of 2 means double damage)
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EDamageType, float> DamageMultipliers;
};