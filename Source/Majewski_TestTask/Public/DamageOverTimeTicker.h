// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageData.h"

class UDamageSystemComponent;

class MAJEWSKI_TESTTASK_API DamageOverTimeTicker
{
public:
	DamageOverTimeTicker(const FDamageData& DamageData);

public:
	void Tick(UDamageSystemComponent& Owner, float DeltaTime);

public:
	FDamageData DamageData;

private:
	float Timer;
};