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
class AController;

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

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float LineTraceRange = 10000.f;

	UPROPERTY(EditAnywhere, Category = "Aiming")
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Aiming")
	float CrosshairYLocation = 0.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void UnPossessed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	APlayerController* PlayerController = nullptr;

	AGun* Gun = nullptr;

	UFUNCTION(BlueprintCallable)
	void PullTrigger();

	bool GetLookDirection(FVector & LookDirection);

	FVector CameraLookDirection;
};
