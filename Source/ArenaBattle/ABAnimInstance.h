// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "ABPawn.h"
#include "ABAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
public:

	UABAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
	void AnimNotify_AttackEnd(UAnimNotify* Notify);

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly, Category = "Pawn")
	float VelocityAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EPlayerState CurrentStateAnim;
	
};
