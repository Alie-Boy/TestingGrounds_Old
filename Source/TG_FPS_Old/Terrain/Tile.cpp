// Fill out your copyright notice in the Description page of Project Settings.
#define OUT   

#include "Terrain/Tile.h"
#include "Components\ArrowComponent.h"
#include "DrawDebugHelpers.h"
#include "Components\HierarchicalInstancedStaticMeshComponent.h"
#include "ActorPool.h"
#include "NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NavigationBoundOffsets = FVector(2000.f, 0.f, 0.f);
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
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation()+NavigationBoundOffsets);
	FNavigationSystem::Build(*GetWorld());
}


void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 minSpawn, int32 maxSpawn, int32 Radius, float minScale, float maxScale)
{
	if (!ToSpawn) return;
	TArray<FSpawnPosition> SpawnPositions = GenerateSpawnPositions(minSpawn, maxSpawn, Radius, minScale, maxScale);
	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PositionActor(ToSpawn, SpawnPosition);
	}
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 minSpawn, int32 maxSpawn, int32 Radius)
{
	if (!ToSpawn) return;
	TArray<FSpawnPosition> SpawnPositions = GenerateSpawnPositions(minSpawn, maxSpawn, Radius, 1.f, 1.f);
	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		APawn* Pawn = GetWorld()->SpawnActor<APawn>(ToSpawn);
		Pawn->SetActorLocation(SpawnPosition.Location);
		Pawn->SetActorRotation(FRotator(0.f, SpawnPosition.Rotation, 0.f));
		//Pawn->SpawnDefaultController();		Using "Placed in World or Spawned" option in BP_Character.
	}
}

TArray<FSpawnPosition> ATile::GenerateSpawnPositions(int32 minSpawn, int32 maxSpawn, int32 Radius, float minScale, float maxScale)
{
	TArray<FSpawnPosition> SpawnPositions;
	int32 NumberOfSpawns = FMath::RandRange(minSpawn, maxSpawn);
	for (size_t i = 0; i < NumberOfSpawns; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
		SpawnPosition.Scale = FMath::RandRange(minScale, maxScale);
		if (GetEmptyLocation(OUT SpawnPosition.Location, Radius * SpawnPosition.Scale))
		{
			SpawnPositions.Add(SpawnPosition);
		}
	}
	return SpawnPositions;
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

void ATile::PositionActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition & SpawnPosition)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorLocation(SpawnPosition.Location);
	SpawnedActor->SetActorRotation(FRotator(0.f, SpawnPosition.Rotation, 0.f));
	SpawnedActor->SetActorScale3D( GetActorScale3D() * SpawnPosition.Scale );
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
