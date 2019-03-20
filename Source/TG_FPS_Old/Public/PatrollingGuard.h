// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TG_FPS_OLD_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Patrol Points CPP")
	TArray<AActor*> PatrolPoints;
	
};
