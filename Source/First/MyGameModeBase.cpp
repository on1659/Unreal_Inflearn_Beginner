// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"
#include "MyCharacter.h"
#include "MainHud.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "MyGameInstance.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter> BP_Char(TEXT("Blueprint'/Game/BluePrints/BP_MyCharacterS.BP_MyCharacterS_C'"));
	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}

	HUDClass = UMainHud::StaticClass();
	static ConstructorHelpers::FClassFinder<UMainHud> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_Hud.WBP_HUD_C'"));
	if (UW.Succeeded())
	{
		HUD_Class = UW.Class;
	
		CurrentWidget = CreateWidget(GetWorld(), HUD_Class);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("AddToViewport"));
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AddToViewport FailAddToViewport FailAddToViewport FailAddToViewport FailAddToViewport Fail"));
	}

	UE_LOG(LogTemp, Warning, TEXT("HUDClassHUDClassHUDClassHUDClassHUDClassHUDClassHUDClassHUDClass;"));
}
void AMyGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

APlayerController* AMyGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AMyGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

UUserWidget* AMyGameModeBase::GetCurrentHudWidget()
{
	return CurrentWidget;
}
