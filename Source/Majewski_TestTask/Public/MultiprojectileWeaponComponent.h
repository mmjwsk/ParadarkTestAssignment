// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TP_WeaponComponent.h"
#include "DamageEnums.h"
#include "MultiprojectileWeaponComponent.generated.h"

/**
 * Weapon Component capable of firing multiple projectile types based on Player input
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAJEWSKI_TESTTASK_API UMultiprojectileWeaponComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()

public:
	virtual bool AttachWeapon(AMajewski_TestTaskCharacter* TargetCharacter) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void ChangeProjectile(EDamageType DamageType);
};
