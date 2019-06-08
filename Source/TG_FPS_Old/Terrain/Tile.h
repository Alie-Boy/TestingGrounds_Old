// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TG_FPS_OLD_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 minSpawn = 1, int32 maxSpawn = 1, int32 Radius = 500);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// returns true if something if something exists near this radius
	bool DoesAnythingExistNearby(FVector Location, int32 Radius);

	bool GetEmptyLocation(FVector & OutSpawnPoint, int32 Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint);
};
