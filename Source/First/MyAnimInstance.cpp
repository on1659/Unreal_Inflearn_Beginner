// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "GameFrameWork/Character.h"
#include "MyCharacter.h"
#include "GameFrameWork/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));
	if (AM.Succeeded())
	{
		if (AM.Object)
		{
			 AttackMontage = AM.Object;
			 UE_LOG(LogTemp, Warning, TEXT("UMyAnimInstance AM Succ"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UMyAnimInstance AM Nullptr"));
		}
	}

}

void UMyAnimInstance::NativeUpdateAnimation(float DelltaSecond)
{
	Super::NativeUpdateAnimation(DelltaSecond);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<AMyCharacter>(Pawn);
		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
			
			Vertical = Character->UpDownValue;
			Horizontal = Character->LeftRightValue;
			//UE_LOG(LogTemp, Warning, TEXT("Character - %1.3f, %1.3f"), Vertical, Horizontal);
		}
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage);

	//UE_LOG(LogTemp, Warning, TEXT("JumpToSection %d"), SectionIndex);
}

FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	//UE_LOG(LogTemp, Warning, TEXT("AnimNotify_AttackHit"));
	OnAttackHit.Broadcast();
}
