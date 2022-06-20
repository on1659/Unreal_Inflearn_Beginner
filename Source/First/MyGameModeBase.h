// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostInitializeComponents() override;

	UUserWidget* GetCurrentHudWidget();

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> HUD_Class;

	UPROPERTY()
	UUserWidget* CurrentWidget;


	UPROPERTY(EditAnywhere, Category = "MyCharcater");
	class AMyCharacter* MyCharcater;

};
