// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatsComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UMyStatsComponent::UMyStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Level = 1;
}

// Called when the game starts
void UMyStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMyStatsComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UMyStatsComponent::OnAttacked(float DamageAmount)
{
	Hp -= DamageAmount;
	if (Hp < 0)
		Hp = 0;
}

void UMyStatsComponent::SetLevel(const int32 _Level)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(Level);
		if (StatData)
		{
			Level = StatData->Level;
			Hp = StatData->MaxHp;
			Attack = StatData->Attack;
		}
	}
}

void UMyStatsComponent::SetHp(const int32 _Hp)
{
}

void UMyStatsComponent::SetAttack(const int32 _Attack)
{
}

