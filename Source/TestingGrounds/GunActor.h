// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class TESTINGGROUNDS_API AGunActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGunActor();

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	FName AttachSocket;

	UFUNCTION(BlueprintCallable)
	void OnFire();

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	FName MuzzleSocket;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATestingGroundsProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
