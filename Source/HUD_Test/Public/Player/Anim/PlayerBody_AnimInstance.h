// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerBody_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HUD_TEST_API UPlayerBody_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerBody_AnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
		bool IsFalling = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
		bool IsJumped = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Base, Meta = (AllowPrivateAccess = true))
		bool IsMove = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
		float PlayerSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
		float UpperYaw = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aim, Meta = (AllowPrivateAccess = true))
		float UpperPitch = 0.0f;

	void TurnBodyYaw(class AHUD_TestCharacter* Player, float& Yaw, bool& Turn);
	bool IsTurn = false;
	FRotator TurnDir = FRotator::ZeroRotator;
	FRotator TurnDirEnd = FRotator::ZeroRotator;

};
