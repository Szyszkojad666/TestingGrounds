// Fill out your copyright notice in the Description page of Project Settings.

#include "GunActor.h"
#include "TestingGroundsProjectile.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/Engine/World.h"

AGunActor::AGunActor()
{
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
}

void AGunActor::OnFire()
{
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetActorRotation();
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
			// try and play a firing animation if specified
			/*
			if (FireAnimation != NULL)
			{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
			}
			*/
		}
	}
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
}



