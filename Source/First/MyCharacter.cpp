// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "MyAnimInstance.h"

#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

} 

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::onAttackMontageEnded);
		AnimInstance->OnAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
	} 

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
	UE_LOG(LogTemp, Warning, TEXT("BindAxis Yaw"));
}

void AMyCharacter::UpDown(float Value)
{
//	if (Value == 0.f)
//		return;

	//	UE_LOG(LogTemp, Warning, TEXT("UpDown %1.f"), Value);

	UpDownValue = Value;
	AddMovementInput(GetActorForwardVector(), Value);

}

void AMyCharacter::LeftRight(float Value)
{
//	if (Value == 0.f)
//		return;

	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %1.f"), Value);
	LeftRightValue = Value;
	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::Yaw(float Value)
{
	if (Value == 0.f)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("Yawn %1.f"), Value);
	AddControllerYawInput(Value);
}

void AMyCharacter::Attack()
{
	if (isAttacking)
		return;

	if (AnimInstance == nullptr)
		return;

	AnimInstance->PlayAttackMontage();
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;
	isAttacking = true;
}
void AMyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f; 
	
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
		);
	
	FVector Foward = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Foward * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Foward).ToQuat();
	FColor DrawColor;
	if (bResult)
	{
		DrawColor = FColor::Green;
	}
	else
	{
		DrawColor = FColor::Red;
	}

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius
		, Rotation, DrawColor, false, 2.f);

	if (bResult && HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor : %d"), *HitResult.Actor->GetName());
	}

}

void AMyCharacter::onAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking = false;
}