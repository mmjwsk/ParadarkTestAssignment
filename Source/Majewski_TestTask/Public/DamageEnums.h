// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Basic,
	Fire,
	Water,
	Healing,
	Poison
};