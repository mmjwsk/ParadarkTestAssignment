// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageOverTimeTicker.h"
#include "DamageSystemComponent.h"

DamageOverTimeTicker::DamageOverTimeTicker(const FDamageData& DamageData)
{
	this->DamageData = DamageData;
	Timer = 0.f;
}

void DamageOverTimeTicker::Tick(UDamageSystemComponent& Owner, float DeltaTime)
{
	DamageData.DamageOverTimeDuration -= DeltaTime;
	if (DamageData.DamageOverTimeDuration > 0.f)
	{
		Timer += DeltaTime;
		if (Timer >= DamageData.DamageOverTimeInitialDelay + DamageData.DamageOverTimeTickDeltaTime)
		{
			// Ensures the delay is only active at the beginning
			Timer = DamageData.DamageOverTimeInitialDelay;

			Owner.DealDirectDamage(DamageData.DamageType, DamageData.DamageOverTimeTickValue);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s Damage Over Time effect finished (Duration ended)"), *UEnum::GetDisplayValueAsText(DamageData.DamageType).ToString());
		Owner.UnregisterDamageTicker(DamageData.DamageType);
	}
}
