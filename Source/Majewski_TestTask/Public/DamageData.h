// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageEnums.h"
#include "DamageData.generated.h"

USTRUCT(BlueprintType)
struct MAJEWSKI_TESTTASK_API FDamageData
{
	GENERATED_BODY()

public:
	FDamageData();

public:
	// Type of damage dealt
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDamageType DamageType;

	// Damage dealt immediately on hit (before reduction)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ImmediateDamage;

	// Whether getting damaged should trigger a DoT effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bTriggersDamageOverTime;

	// Damage dealt on every DoT tick (before reduction)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bTriggersDamageOverTime", EditConditionHides))
	float DamageOverTimeTickValue;

	// Time (in seconds) the DoT effect will be active
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bTriggersDamageOverTime", EditConditionHides))
	float DamageOverTimeDuration;

	// Time (in seconds) between ticks of this DoT effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bTriggersDamageOverTime", EditConditionHides))
	float DamageOverTimeTickDeltaTime;

	// Time (in seconds) before the first tick of this DoT effect activates - useful for delayed DoT to e.g. match with animation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bTriggersDamageOverTime", EditConditionHides))
	float DamageOverTimeInitialDelay;

	// Whether the DoT should be cancelled upon receiving damage of DamageOverTimeancellationType
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bTriggersDamageOverTime", EditConditionHides))
	bool bCanBeCancelled;

	// Type of damage that - when received - will immediately cancel this DoT effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bTriggersDamageOverTime && bCanBeCancelled", EditConditionHides))
	EDamageType DamageOverTimeCancellationType;
};