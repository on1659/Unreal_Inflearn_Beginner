// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AMyAIController();

	void OnPossess(APawn* lnPawn) override;
	void OnUnPossess() override;

private:
	void RandomMove();

private:
	FTimerHandle TimerHandle;

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;


	UPROPERTY()
	class UBlackboardData* BlackBoardData;

};
