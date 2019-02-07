// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SelectWaypoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PatrolCharacter.h"

EBTNodeResult::Type UBTTask_SelectWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Controller = OwnerComp.GetAIOwner();
	APatrolCharacter* ControlledCharacter;
	if (Controller)
	{
		ControlledCharacter = Cast<APatrolCharacter>(Controller->GetPawn());
		if (ControlledCharacter)
		{
			Index = FMath::Fmod(Index + 1, ControlledCharacter->PatrolPoints.Num());
			if (ControlledCharacter->PatrolPoints[Index])
			{
				BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, ControlledCharacter->PatrolPoints[Index]);
				BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);
			}
		}	
	}
	UE_LOG(LogTemp, Warning, TEXT("Index: %i"), Index);
	return EBTNodeResult::Succeeded;
}


