// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition {
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

class UHierarchicalInstancedStaticMeshComponent;
class UActorPool;

UCLASS()
class TG_FPS_OLD_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 minSpawn = 1, int32 maxSpawn = 1, int32 Radius = 500, float minScale = 1.f, float maxScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 minSpawn = 1, int32 maxSpawn = 1, int32 Radius = 500);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetNavMeshBoundPool(UActorPool* ActorPool);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundOffsets;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void PositionNavMeshBoundsVolume();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 minSpawn, int32 maxSpawn, int32 Radius, float minScale, float maxScale)
	{
		if (!ToSpawn) return;
		int32 NumberOfSpawns = FMath::RandRange(minSpawn, maxSpawn);
		for (int32 i = 0; i < NumberOfSpawns; i++)
		{
			FSpawnPosition SpawnPosition;
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnPosition.Scale = FMath::RandRange(minScale, maxScale);
			if (GetEmptyLocation(SpawnPosition.Location, Radius))
			{
				PlaceActor(ToSpawn, SpawnPosition);
			}
		}
	}

	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition & SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition & SpawnPosition);

	bool DoesAnythingExistNearby(FVector Location, int32 Radius);

	bool GetEmptyLocation(FVector & OutSpawnPoint, int32 Radius);


	UActorPool* Pool = nullptr;

	AActor* NavMeshBoundsVolume;
};
