// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiprojectileWeaponComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Majewski_TestTaskCharacter.h"
#include "SpecializedProjectile.h"
#include "EnhancedInputComponent.h"
#include "DamageSubsystem.h"

bool UMultiprojectileWeaponComponent::AttachWeapon(AMajewski_TestTaskCharacter* TargetCharacter)
{
	bool Result = Super::AttachWeapon(TargetCharacter);
	if (Result)
	{
		// Handle binding all the inputs related to changing damage type of the projectiles shot by the weapon
		if (APlayerController* PlayerController = Cast<APlayerController>(TargetCharacter->GetController()))
		{		
			UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
			UDamageSubsystem* DamageSystem = GetOwner()->GetGameInstance()->GetSubsystem<UDamageSubsystem>();

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DamageSystem->Settings->InputMappingContext, 1);
			}

			for (const auto& BindingEntry : DamageSystem->Settings->DamageTypeInputs)
			{
				if (EnhancedInputComponent != nullptr)
				{
					EnhancedInputComponent->BindAction(BindingEntry.InputAction, ETriggerEvent::Triggered,
						this, &UMultiprojectileWeaponComponent::ChangeProjectile, BindingEntry.DamageType);
				}
			}
		}
	}
	return Result;
}

void UMultiprojectileWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	// Cleanup damage type input
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(GetOwner()->GetGameInstance()->GetSubsystem<UDamageSubsystem>()->Settings->InputMappingContext);
		}
	}
}

void UMultiprojectileWeaponComponent::ChangeProjectile(EDamageType DamageType)
{
	ProjectileClass = GetOwner()->GetGameInstance()->GetSubsystem<UDamageSubsystem>()->Settings->ProjectilesForDamageTypes[DamageType];
}
