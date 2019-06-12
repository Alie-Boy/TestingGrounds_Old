// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TG_FPS_OLD_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UGrassComponent();

	UPROPERTY(EditDefaultsOnly)
	FBox SpawningExtents;

	UPROPERTY(EditDefaultsOnly)
	int32 SpawnCount;

protected:

	void BeginPlay() override;

private:

	void SpawnGrass();
};
