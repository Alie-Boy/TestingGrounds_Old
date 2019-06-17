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

	TArray<FSpawnPosition> GenerateSpawnPositions(int32 minSpawn, int32 maxSpawn, int32 Radius = 500, float minScale = 1.f, float maxScale = 1.f);

	// returns true if something if something exists near this radius
	bool DoesAnythingExistNearby(FVector Location, int32 Radius);

	bool GetEmptyLocation(FVector & OutSpawnPoint, int32 Radius);

	void PositionActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition & SpawnPosition);

	UActorPool* Pool = nullptr;

	AActor* NavMeshBoundsVolume;
};
