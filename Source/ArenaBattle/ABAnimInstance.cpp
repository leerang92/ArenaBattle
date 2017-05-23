// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABAnimInstance.h"




UABAnimInstance::UABAnimInstance()
{
	VelocityAnim = 0.0f;
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* OwnerPawn = TryGetPawnOwner();
	if (OwnerPawn != nullptr)
	{
		if (OwnerPawn->IsValidLowLevel())
		{
			VelocityAnim = OwnerPawn->GetVelocity().Size();
			AABPawn* Character = Cast<AABPawn>(OwnerPawn);
			if (Character)
			{
				CurrentStateAnim = Character->CurrentState;
			}
		}
	}
}

void UABAnimInstance::AnimNotify_AttackEnd(UAnimNotify * Notify)
{
	AABPawn* Character = Cast<AABPawn>(TryGetPawnOwner());
	if (Character)
	{
		Character->CurrentState = EPlayerState::PEACE;
	}
}
