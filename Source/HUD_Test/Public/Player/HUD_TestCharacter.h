// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HUD_TestCharacter.generated.h"

UCLASS(config=Game)
class AHUD_TestCharacter : public ACharacter
{
	GENERATED_BODY()

	// 컴포넌트
	// 카메라 팔
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// 팔 Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ArmMesh;

	// 다리 Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* LegMesh;

// 에디터 공개용
public:
	AHUD_TestCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.0f;   // 시야 이동 속도(좌, 우)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.0f; // 시야 이동 속도(상, 하)

// 가려야 하는
protected:

	// 이동 관련된 처리
	void PlayerMove(bool IsAactive, float Forward, float Right, FVector& Dir, float Speed, float DeltaSecond);
	UPROPERTY()
	bool IsMove;                    // 움직여도 되는지 상태 여부 표시
	float InputForwardDir;          // 입력된 값을 표현
	float InputRightDir;            // 입력된 값을 표현
	FVector MoveDir; // 입력된 값에 따른 방향을 표현
	float PlayerSpeed;	           // 플레이어 속도(상태 별로 달라짐)

	// 시야 관련
	FRotator ControllerRot;
	// 모드 관련
	bool IsFPS = false; // 1인칭 시점 인지 확인

	// 입력 관련
	void PlayerModChange();// 모드 체인지

	// Axis 관련
	void MoveForward(float Value); // 앞, 뒤 이동 관련
	void MoveRight(float Value);   // 좌, 우 이동 관련

	void TurnAtRate(float Rate);   // 좌, 우 시야 관련
	void LookUpAtRate(float Rate); // 상, 하 시야 관련

// 이벤트
protected:
	// 입력 장치와 함수 바인딩
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 준비를 다 마치고 나서 시작할 때
	virtual void BeginPlay() override;
	// 매번 작동되는 함수
	virtual void Tick(float DeltaTime) override;

// 메세지 전달(멀티플레이)
public:

	// 컨트롤러 Rotation을 전달하는 용도
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void NetMulticast_SendControllerRot(FRotator Send);
	bool NetMulticast_SendControllerRot_Validate(FRotator Send);
	void NetMulticast_SendControllerRot_Implementation(FRotator Send);

// 공개하기
public:
	// 컴포넌트
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// 이동
	float GetPlayerSpeed() { return PlayerSpeed; } 
	float SetPlayerSpeed(float Set) { PlayerSpeed = Set; }

	// 시야
	FRotator GetControllerRot() { return ControllerRot; }

};

