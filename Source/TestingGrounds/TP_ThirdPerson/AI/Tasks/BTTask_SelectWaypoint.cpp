// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SelectWaypoint.h"
#include "Components/PatrolComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UBTTask_SelectWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Controller = OwnerComp.GetAIOwner();
	UPatrolComponent* PatrolComp;
	if (Controller)
	{
		UActorComponent* ActorComponent = Controller->GetPawn()->GetComponentByClass(UPatrolComponent::StaticClass());
		PatrolComp = Cast<UPatrolComponent>(ActorComponent);
		if (PatrolComp)
		{
			Index = FMath::Fmod(Index + 1, PatrolComp->PatrolPoints.Num());
			if (PatrolComp->PatrolPoints[Index])
			{
				BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolComp->PatrolPoints[Index]);
				BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);
			}
		}	
	}
	//UE_LOG(LogTemp, Warning, TEXT("Index: %i"), Index);
	return EBTNodeResult::Succeeded;
}


