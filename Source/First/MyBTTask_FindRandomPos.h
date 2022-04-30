// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_FindRandomPos.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UMyBTTask_FindRandomPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMyBTTask_FindRandomPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
