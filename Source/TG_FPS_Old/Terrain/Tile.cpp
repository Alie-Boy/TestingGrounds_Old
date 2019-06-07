// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain/Tile.h"
#include "Components\ArrowComponent.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 minSpawn, int32 maxSpawn)
{
	if (!ToSpawn) return;
	UArrowComponent* Arrow = FindComponentByClass<UArrowComponent>();
	FVector min = (Arrow->GetComponentLocation()) + FVector(-4000.f, -2000.f, 100.f);
	FVector max = (Arrow->GetComponentLocation()) + FVector(-100.f , 2000.f, 100.f);
	/*FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);*/
	int32 NumberOfSpawns = FMath::RandRange(minSpawn, maxSpawn);
	for (size_t i = 0; i < NumberOfSpawns; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(FBox(min, max));
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
		SpawnedActor->SetActorLocation(SpawnLocation);
		SpawnedActor->SetActorRotation(FRotator(0.f, FMath::RandRange(0.f, 359.f), 0.f));
		SpawnedActor->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		/*FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));*/
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

