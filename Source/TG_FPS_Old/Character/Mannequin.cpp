// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"

#include "Camera\CameraComponent.h"
#include "Components\SkeletalMeshComponent.h"
#include "Components\CapsuleComponent.h"
#include "Components\ChildActorComponent.h"
#include "Components\InputComponent.h"
#include "Weapons\Gun.h"
#include "GameFramework\PlayerController.h"

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
	if (!GunBlueprint) { 
		UE_LOG(LogTemp, Warning, TEXT("No blueprint assigned to GunBlueprint in Mannequin"));
		return;
	}
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	if (IsPlayerControlled()) {
		Gun->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->FPAnimInstance = FPArms->GetAnimInstance();
		PlayerController = Cast<APlayerController>(GetController());
	}
	else {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->TPAnimInstance = GetMesh()->GetAnimInstance();
	}
	FPCamera->Activate();

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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();
	if (!Gun) return;
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void AMannequin::PullTrigger()
{
	FVector AimLocation = FVector(0.f);
	if (IsPlayerControlled())
	{
		if (GetLookDirection(CameraLookDirection))
		{
			FHitResult HitResult;
			FVector StartTraceLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
			FVector EndTraceLocation = StartTraceLocation + (CameraLookDirection * LineTraceRange);
			FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(FName(""), false, this);
			if (GetWorld()->LineTraceSingleByChannel(
				HitResult,
				StartTraceLocation,
				EndTraceLocation,
				ECC_Camera,
				CollisionQueryParams
			))
			{
				AimLocation = HitResult.ImpactPoint;
			}
			else
			{
				AimLocation = EndTraceLocation;
			}
		}
	}
	else
	{
		APawn* Character = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (Character == nullptr) return;
		AimLocation = Character->GetActorLocation();
	}
	Gun->FireAt(AimLocation);
}

bool AMannequin::GetLookDirection(FVector & OUTLookDirection)
{
	FVector CameraLocation;
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	return PlayerController->DeprojectScreenPositionToWorld(
		ViewportSizeX * CrosshairXLocation,
		ViewportSizeY * CrosshairYLocation,
		CameraLocation,
		OUTLookDirection
	);
}
