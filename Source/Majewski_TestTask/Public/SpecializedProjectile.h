// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Majewski_TestTaskProjectile.h"
#include "DamageData.h"
#include "SpecializedProjectile.generated.h"

UCLASS()
class MAJEWSKI_TESTTASK_API ASpecializedProjectile : public AMajewski_TestTaskProjectile
{
	GENERATED_BODY()
	
public:
	// Details of damage dealt by this Projectile to any Actors having a DamageSystemComponent
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDamageData DamageData;
	
public:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
