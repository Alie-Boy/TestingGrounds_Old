// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class TG_FPS_OLD_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void CycleIndex(int32 Index, UBehaviorTreeComponent &OwnerComp);

	int32 FindNextWaypoint(UBehaviorTreeComponent &OwnerComp);

	void FindPatrolPoints(UBehaviorTreeComponent &OwnerComp);

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector IndexKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector WaypointKey;

private:

	TArray<AActor*> PatrolPoints;
};
