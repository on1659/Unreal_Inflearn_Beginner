// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Data(TEXT("DataTable'/Game/Data/StatTable.StatTable'"));
	if (Data.Succeeded())
	{
		MyStats = Data.Object;
	}

}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance"), GetStatData(1)->Attack);
}


FMyCharcaterData* UMyGameInstance::GetStatData(int32 Level)
{
	return MyStats->FindRow<FMyCharcaterData>(*FString::FromInt(Level), TEXT(""));
}