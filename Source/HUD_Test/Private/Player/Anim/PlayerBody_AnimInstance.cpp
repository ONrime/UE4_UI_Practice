// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Anim/PlayerBody_AnimInstance.h"
#include "Player/HUD_TestCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerBody_AnimInstance::UPlayerBody_AnimInstance()
{
	IsMove = true;
}

void UPlayerBody_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		AHUD_TestCharacter* Player = Cast<AHUD_TestCharacter>(Pawn);

		IsFalling = Player->GetMovementComponent()->IsFalling();
		//IsJumped = false;

		PlayerSpeed = Player->GetVelocity().Size();
		
		// 컨트롤러와 액터 사이의 pitch 값을 구한다.
		FRotator PitchAngle = (Player->GetControllerRot() - Player->GetActorRotation()).GetNormalized();
		// 허리를 180도로 꺽는게 아니기 때문에 90도로 제한을 둔다.
		UpperPitch = FMath::ClampAngle(PitchAngle.Pitch, -90.0f, 90.0f);

		TurnBodyYaw(Player, UpperYaw, IsTurn);
		//UE_LOG(LogTemp, Warning, TEXT("UpperYaw: %f"), UpperYaw);
	}
}

void UPlayerBody_AnimInstance::TurnBodyYaw(AHUD_TestCharacter* Player, float& Yaw, bool& Turn)
{
	if (Player->GetVelocity().X > 0.0f || Player->GetVelocity().Y > 0.0f)
	{ // 움직일 때 하체가 따라가게한다.
		TurnDir = Player->GetActorRotation();
		TurnDirEnd = Player->GetActorRotation();
		Turn = false;
	}
	else
	{ // 움직이지 않을 때 하체가 따로 움직이게 한다.
		if (!Turn) 
		{
			Turn = true;
			TurnDirEnd = Player->GetActorRotation();
		}
		else {
			if (Yaw >= 70.0f || Yaw <= -70.0f) {
				TurnDirEnd = Player->GetActorRotation();
			}
		}
	}
	TurnDir = FMath::RInterpTo(TurnDir, TurnDirEnd, GetWorld()->GetDeltaSeconds(), 5.0f);
	FRotator interpToAngle = (Player->GetActorRotation() - TurnDir).GetNormalized();
	Yaw = FMath::ClampAngle(interpToAngle.Yaw, -90.0f, 90.0f) * -1.0f;
}
