// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHud.h"
#include "MyStatsComponent.h"
#include "Components/ProgressBar.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMainHud::BindHp(class UMyStatsComponent* StatComp)
{
	CurrentStatComp = StatComp;
	if (StatComp)
	{
		StatComp->OnHpChanged.AddUObject(this, &UMainHud::UpdateHp);
	}
}

void UMainHud::InitializeComponent()
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		BindHp(MyGameInstance->GetPlayerStatsComponet());
	}
}
void UMainHud::UpdateHp()
{
	if (CurrentStatComp.IsValid())
	{	
		UE_LOG(LogTemp, Warning, TEXT("Percent "), CurrentStatComp->GetHpRatio());
		PB_HPGauge->SetPercent(CurrentStatComp->GetHpRatio());
	}
}