// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecializedProjectile.h"
#include "DamageSystemComponent.h"

void ASpecializedProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		UDamageSystemComponent* DamageComponent = OtherActor->GetComponentByClass<UDamageSystemComponent>();
		if (DamageComponent != nullptr)
		{
			DamageComponent->OnReceivedNewDamage(DamageData);
		}
	}

	// Intentionally the parent method is called after and not before the added functionality because it can cause the destruction of THIS
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
