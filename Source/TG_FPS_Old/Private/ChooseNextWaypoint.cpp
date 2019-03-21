// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Public/PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FindPatrolPoints(OwnerComp);
	auto Index = FindNextWaypoint(OwnerComp);
	CycleIndex(Index, OwnerComp);

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::FindPatrolPoints(UBehaviorTreeComponent &OwnerComp)
{
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto ControlledGuard = Cast<APatrollingGuard>(ControlledPawn);
	PatrolPoints = ControlledGuard->GetPatrollingPoints();
}

int32 UChooseNextWaypoint::FindNextWaypoint(UBehaviorTreeComponent &OwnerComp)
{
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	return Index;
}
void UChooseNextWaypoint::CycleIndex(int32 Index, UBehaviorTreeComponent &OwnerComp)
{
	if (Index >= PatrolPoints.Num()-1) // choosing >= because second last iteration through Tree sets Index last
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(IndexKey.SelectedKeyName, 0);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(IndexKey.SelectedKeyName, Index+1);
	}
}


