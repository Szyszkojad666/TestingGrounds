// Fill out your copyright notice in the Description page of Project Settings.

#include "GunActor.h"
#include "TestingGroundsProjectile.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TestingGroundsCharacter.h"
#include "Animation/AnimInstance.h"

AGunActor::AGunActor()
{
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
}

void AGunActor::OnFire()
{
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = FP_Gun->GetSocketRotation(MuzzleSocket);
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = FP_Gun->GetSocketLocation(MuzzleSocket);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ATestingGroundsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			// try and play the sound if specified
			if (FireSound != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
		}
	}
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
}



