// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageEnums.h"
#include "DamageTypeInputData.generated.h"

USTRUCT(BlueprintType)
struct MAJEWSKI_TESTTASK_API FDamageTypeInputData
{
	GENERATED_BODY()
public:
	FDamageTypeInputData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDamageType DamageType;
};
