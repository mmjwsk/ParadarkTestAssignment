// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageData.h"

FDamageData::FDamageData()
{
	DamageType = EDamageType::Basic;
	ImmediateDamage = 0.f;
	bTriggersDamageOverTime = false;
	DamageOverTimeTickValue = 0.f;
	DamageOverTimeDuration = 0.f;
	DamageOverTimeTickDeltaTime = 0.f;
	DamageOverTimeInitialDelay = 0.f;
	bCanBeCancelled = false;
	DamageOverTimeCancellationType = EDamageType::Basic;
}
