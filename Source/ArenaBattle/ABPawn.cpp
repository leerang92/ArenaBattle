// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"
#include "ABAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHP = 100.0f;
	
	// 콜리더 설정
	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	Body->SetCapsuleHalfHeight(88.0f);
	Body->SetCapsuleRadius(33.0f);
	RootComponent = Body;
	
	// 스켈레탈 메쉬 설정
	// static 으로 선언하여 CDO를 사용하는 모든 객체들이 공유할 수 있도록 한다. (중복 방지)
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mesh
	(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Robo.SK_CharM_Robo'"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	Mesh->SetRelativeLocationAndRotation(FVector(0, 0, -80.0f), FRotator(0, -90.0f, 0));
	Mesh->SetSkeletalMesh(SK_Mesh.Object);
	Mesh->SetupAttachment(Body); // Capsule Collider의 하위(자식) 객체로 설정

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 600.0f;

	// 스프링 암 설정
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(Body);
	SpringArm->SetRelativeRotation(FRotator(-35.0f, 0, 0));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;


	// 카메라 설정
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetRelativeLocationAndRotation(FVector(-200.0f, 0, 160.0f), FRotator(-20.0f, 0, 0));
	Camera->SetupAttachment(SpringArm);

	CurrentState = EPlayerState::PEACE;
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;
	int32 NewIndex = FMath::RandRange(0, CharacterAssets.Num() - 1);
	UABGameInstance* ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	if (ABGameInstance)
	{
		TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ABGameInstance->AssetLoader.SynchronousLoad(CharacterAssets[NewIndex]));
		if (NewCharacter)
		{
			Mesh->SetSkeletalMesh(NewCharacter.Get());
		}
	}
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	FVector InputVector = FVector(CurrentUpDownVal, CurrentLeftRightVal, 0.0F);

	switch (CurrentState)
	{
	case EPlayerState::PEACE:
	{
		if (InputVector.SizeSquared() > 0.0F)
		{
			FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(InputVector);
			SetActorRotation(TargetRotation);
			AddMovementInput(GetActorForwardVector());
		}
		break;
	}
	case EPlayerState::BATTLE:
		break;
	}	

}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("LeftRight", this, &AABPawn::LeftRightInput);
	InputComponent->BindAxis("UpDown", this, &AABPawn::UpDownInput);

	InputComponent->BindAction("NormalAttack", IE_Pressed, this, &AABPawn::OnPressNormalAttack);
}

void AABPawn::UpDownInput(float NewInputVal)
{
	CurrentUpDownVal = NewInputVal;
}

void AABPawn::LeftRightInput(float NewInputVal)
{
	CurrentLeftRightVal = NewInputVal;
}

void AABPawn::OnPressNormalAttack()
{
	CurrentState = EPlayerState::BATTLE;
	UABAnimInstance* AnimIns = Cast<UABAnimInstance>(Mesh->GetAnimInstance());
	if (AnimIns)
	{
		AnimIns->ReceiveNormalAttackInput();
	}
}

void AABPawn::OnNormalAttackEnd()
{
	CurrentState = EPlayerState::PEACE;
}

