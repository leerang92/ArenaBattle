// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ABPawn.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	PEACE,
	BATTLE,
};

UCLASS(config=Game)
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeletale")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UCapsuleComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movment")
	class UFloatingPawnMovement* Movement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	// Config 폴더의 ini 파일에서 초기화 시킬 변수
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHP;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stat")
	float CurrentHP;

	UPROPERTY(config, VisibleInstanceOnly, BlueprintReadOnly, Category = "Asset")
	TArray<FStringAssetReference> CharacterAssets;

	EPlayerState CurrentState;

private:

	float CurrentLeftRightVal;
	float CurrentUpDownVal;

	UFUNCTION()
	void UpDownInput(float NewInputVal);

	UFUNCTION()
	void LeftRightInput(float NewInputVal);

	UFUNCTION()
	void OnPressNormalAttack();

	UFUNCTION()
		void OffPressNormalAttack();
};
