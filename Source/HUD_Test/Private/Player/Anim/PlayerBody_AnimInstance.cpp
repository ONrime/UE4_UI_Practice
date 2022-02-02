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
		
		// ��Ʈ�ѷ��� ���� ������ pitch ���� ���Ѵ�.
		FRotator PitchAngle = (Player->GetControllerRot() - Player->GetActorRotation()).GetNormalized();
		// �㸮�� 180���� ���°� �ƴϱ� ������ 90���� ������ �д�.
		UpperPitch = FMath::ClampAngle(PitchAngle.Pitch, -90.0f, 90.0f);

		TurnBodyYaw(Player, UpperYaw, IsTurn);
		//UE_LOG(LogTemp, Warning, TEXT("UpperYaw: %f"), UpperYaw);
	}
}

void UPlayerBody_AnimInstance::TurnBodyYaw(AHUD_TestCharacter* Player, float& Yaw, bool& Turn)
{
	if (Player->GetVelocity().X > 0.0f || Player->GetVelocity().Y > 0.0f)
	{ // ������ �� ��ü�� ���󰡰��Ѵ�.
		TurnDir = Player->GetActorRotation();
		TurnDirEnd = Player->GetActorRotation();
		Turn = false;
	}
	else
	{ // �������� ���� �� ��ü�� ���� �����̰� �Ѵ�.
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
