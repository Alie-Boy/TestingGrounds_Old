// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

//Forward Declarations
class UCameraComponent;
class USkeletalMeshComponent;
class UChildActorComponent;
class AGun;

UCLASS()
class TG_FPS_OLD_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPCamera = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FPArms = nullptr;

	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* FPGun = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunBlueprint;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	AGun* Gun = nullptr;

	void OnFire();
};
