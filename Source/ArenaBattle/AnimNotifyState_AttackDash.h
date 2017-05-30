// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AttackDash.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UAnimNotifyState_AttackDash : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	UAnimNotifyState_AttackDash();

	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashPower;
};
