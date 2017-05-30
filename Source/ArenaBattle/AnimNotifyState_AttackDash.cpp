// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "AnimNotifyState_AttackDash.h"

UAnimNotifyState_AttackDash::UAnimNotifyState_AttackDash()
{
	DashPower = 1000.0f;
}

void UAnimNotifyState_AttackDash::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	AActor* Owner = MeshComp->GetOwner();

	if (Owner != nullptr && Owner->IsValidLowLevel())
	{
		APawn* OwnerPawn = Cast<APawn>(Owner);
		if (OwnerPawn->GetMovementComponent())
		{
			OwnerPawn->GetMovementComponent()->Velocity = OwnerPawn->GetActorForwardVector() * DashPower;
		}
	}
}
