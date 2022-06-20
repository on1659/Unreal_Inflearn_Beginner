// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"

class UMyStatsComponent;

USTRUCT()
struct FMyCharcaterData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 MaxHp;
};

/**
 * 
 */

UCLASS()
class FIRST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override;

	FMyCharcaterData* UMyGameInstance::GetStatData(int32 Level);

	void SetPlayerStatsComponet(UMyStatsComponent* StatComp);
	UMyStatsComponent* GetPlayerStatsComponet();

private:
	UPROPERTY()
	class UDataTable* MyStats;

	UPROPERTY(VisibleAnywhere);
	class UMyStatsComponent* PlayerStat;
};
