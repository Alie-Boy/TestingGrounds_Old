// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"

#include "Camera\CameraComponent.h"
#include "Components\SkeletalMeshComponent.h"
#include "Components\CapsuleComponent.h"
#include "Components\ChildActorComponent.h"
#include "Components\InputComponent.h"
#include "Weapons\Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera    = CreateDefaultSubobject<UCameraComponent>(FName("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->SetRelativeLocation(FVector(-4.56, 6.75, 69.0));
	FPCamera->bUsePawnControlRotation = true;

	FPArms      = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FPArms"));
	FPArms->SetupAttachment(FPCamera);
	FPArms->SetRelativeLocation(FVector(5.61,-10.52,-160.0));
	FPArms->SetRelativeRotation(FRotator(2.667564, -16.737473, 2.950280));

	/*FPGun       = CreateDefaultSubobject<UChildActorComponent>(FName("FPGun"));
	FPGun->SetupAttachment(FPArms, FName("GripPoint"));*/
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (!GunBlueprint) { UE_LOG(LogTemp, Warning, TEXT("No blueprint assigned to GunBlueprint in Mannequin")) }
	else
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
		Gun->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->AnimInstance = FPArms->GetAnimInstance();
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::OnFire);
}

void AMannequin::OnFire()
{
	Gun->OnFire();
}

