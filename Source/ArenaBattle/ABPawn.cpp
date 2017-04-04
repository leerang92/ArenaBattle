// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	Mesh->SetupAttachment(Body); // Capsule Collider의 하의 객체로 설정

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	// 카메라 설정
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetRelativeLocationAndRotation(FVector(-200.0f, 0, 160.0f), FRotator(-20.0f, 0, 0));
	Camera->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

