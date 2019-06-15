// Fill out your copyright notice in the Description page of Project Settings.
#define OUT   

#include "Terrain/Tile.h"
#include "Components\ArrowComponent.h"
#include "DrawDebugHelpers.h"
#include "Components\HierarchicalInstancedStaticMeshComponent.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Pool->Return(NavMeshBoundsVolume);
}

void ATile::SetNavMeshBoundPool(UActorPool * ActorPool)
{
	Pool = ActorPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (!NavMeshBoundsVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in the pool"), *(GetName()));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] checked out {%s}"), *(GetName()), *(NavMeshBoundsVolume->GetName()));
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}


void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 minSpawn, int32 maxSpawn, int32 Radius,
	bool HasRandomScale, float minScaleMultiplier, float maxScaleMultiplier)
{
	if (!ToSpawn) return;
	int32 NumberOfSpawns = FMath::RandRange(minSpawn, maxSpawn);
	for (size_t i = 0; i < NumberOfSpawns; i++)
	{
		FVector SpawnPoint;
		if (GetEmptyLocation(OUT SpawnPoint, Radius))
		{
			float ScaleMultiplier = 1.f;
			if (HasRandomScale)
			{
				ScaleMultiplier = FMath::RandRange(minScaleMultiplier, maxScaleMultiplier);
			}
			PlaceActor(ToSpawn, SpawnPoint, ScaleMultiplier);
		}
	}
}

bool ATile::GetEmptyLocation(FVector & OutSpawnPoint, int32 Radius)
{	
	UArrowComponent* Arrow = FindComponentByClass<UArrowComponent>();
	FVector min = (Arrow->GetComponentLocation()) + FVector(-4000.f, -2000.f, 100.f);
	FVector max = (Arrow->GetComponentLocation()) + FVector(-100.f , 2000.f, 100.f);
	const int32 MAX_ATTEMPTS = 20;
	for (size_t i = 0; i != MAX_ATTEMPTS; ++i)
	{
		OutSpawnPoint = FMath::RandPointInBox(FBox(min, max));
		if (DoesAnythingExistNearby(OutSpawnPoint, Radius)) { continue; } // if Sphere cast hits something, try again
		else { return true; }
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Scale)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorLocation(SpawnPoint);
	SpawnedActor->SetActorRotation(FRotator(0.f, FMath::RandRange(-180.f, 180.f), 0.f));
	SpawnedActor->SetActorScale3D( GetActorScale3D() * Scale );
	SpawnedActor->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::DoesAnythingExistNearby(FVector Location, int32 Radius)
{
	FHitResult HitResult;
	
	// this is not needed in my case as my Location provided is already Global.
	//FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		Location,
		Location + 0.1f, // Sweep won't detect any hit without any difference between start and end location
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	/*FColor Color = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, Color, true, 100);*/
	return HasHit;
}
