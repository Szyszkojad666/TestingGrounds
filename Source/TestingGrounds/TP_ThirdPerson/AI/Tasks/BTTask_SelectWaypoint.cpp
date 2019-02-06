// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SelectWaypoint.h"

EBTNodeResult::Type UBTTask_SelectWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UE_LOG(LogTemp, Warning, TEXT("Chuj"));
	return EBTNodeResult::Succeeded;
}


