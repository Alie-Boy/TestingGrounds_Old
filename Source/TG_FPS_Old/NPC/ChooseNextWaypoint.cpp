// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FindPatrolPoints(OwnerComp);
	auto Index = FindNextWaypoint(OwnerComp);
	CycleIndex(Index, OwnerComp);

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::FindPatrolPoints(UBehaviorTreeComponent &OwnerComp)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	
	if (!ensure(PatrolRoute)) { return; }
	else {
		PatrolPoints = PatrolRoute->GetPatrollingPoints();
	}
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
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Patrol Points in %s"), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
		return;
	}

	if (Index >= PatrolPoints.Num()-1) // choosing >= because second last iteration through Tree sets Index last
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(IndexKey.SelectedKeyName, 0);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(IndexKey.SelectedKeyName, Index+1);
	}
}
