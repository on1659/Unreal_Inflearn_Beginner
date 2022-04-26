// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class FIRST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	void Attack();

	void AttackCheck();

	UFUNCTION()
	void onAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	UPROPERTY(VisibleAnywhere);
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere);
	class UCameraComponent* Camera;


	UPROPERTY(VisibleAnywhere, Category = Pawn);
	bool isAttacking = false;

	UPROPERTY();
	class UMyAnimInstance* AnimInstance;


	UPROPERTY();
	int32 AttackIndex = 0;


public:
	UPROPERTY();
	float UpDownValue = 0.f;

	UPROPERTY();
	float LeftRightValue = 0.f;
};