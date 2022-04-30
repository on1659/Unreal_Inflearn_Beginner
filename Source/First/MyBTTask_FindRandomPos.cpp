// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindRandomPos.h"
#include "MyAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_FindRandomPos::UMyBTTask_FindRandomPos()
{
	NodeName = TEXT("FindRandomPos");
}

EBTNodeResult::Type UMyBTTask_FindRandomPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return EBTNodeResult::Failed;

	FNavLocation RandomPos;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandomPos")), RandomPos.Location);
		return EBTNodeResult::Succeeded;
		// UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	}
	return EBTNodeResult::Failed;
}
