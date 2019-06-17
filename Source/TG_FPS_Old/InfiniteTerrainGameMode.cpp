// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerrainGameMode.h"
#include "NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>("NavMeshBoundsVolume");
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* NavMeshVolume)
{
	NavMeshBoundsVolumePool->Add(NavMeshVolume);
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> NavMeshIterator(GetWorld());
	while (NavMeshIterator)
	{
		ANavMeshBoundsVolume* NavMesh = *NavMeshIterator;
		AddToPool(NavMesh);
		++NavMeshIterator;
	}
}

void AInfiniteTerrainGameMode::NewTileConquered() { Score++; }
