// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TG_FPS_OldGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;

UCLASS()
class TG_FPS_OLD_API AInfiniteTerrainGameMode : public ATG_FPS_OldGameMode
{
	GENERATED_BODY()
	
public:

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category="BoundsVolume")
	void PopulateBoundsVolumePool();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UActorPool* NavMeshBoundsVolume = nullptr;

private:

	void AddToPool(ANavMeshBoundsVolume* NavMeshVolume);
};
