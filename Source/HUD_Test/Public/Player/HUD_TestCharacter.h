// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/MapIcon_Interface.h"
#include "HUD_TestCharacter.generated.h"

UCLASS(config=Game)
class AHUD_TestCharacter : public ACharacter, public IMapIcon_Interface
{
	GENERATED_BODY()

	// ������Ʈ
	// ī�޶� ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// �� Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ArmMesh;

	// �ٸ� Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* LegMesh;

// ������ ������
public:
	AHUD_TestCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.0f;   // �þ� �̵� �ӵ�(��, ��)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.0f; // �þ� �̵� �ӵ�(��, ��)

// ������ �ϴ�
protected:

	// �̵� ���õ� ó��
	void PlayerMove(bool IsAactive, float Forward, float Right, FVector& Dir, float Speed, float DeltaSecond);
	UPROPERTY()
	bool IsMove;                    // �������� �Ǵ��� ���� ���� ǥ��
	float InputForwardDir;          // �Էµ� ���� ǥ��
	float InputRightDir;            // �Էµ� ���� ǥ��
	FVector MoveDir; // �Էµ� ���� ���� ������ ǥ��
	float PlayerSpeed;	           // �÷��̾� �ӵ�(���� ���� �޶���)

	// �þ� ����
	FRotator ControllerRot;

	// ���(��Ī ����) ����
	bool IsFPS = false; // 1��Ī ���� ���� Ȯ��

	// HUD //////////////////////////////////////////////////////////////////////////////////
	class AHUD_PlayerHUD* PlayerHUD;

	// �̴ϸ�
	EMapIconState IconState;							   // ������ ����
	class UIconLocation_UserWidget* Icon_Widget = nullptr; // ����� ������ ����

	/////////////////////////////////////////////////////////////////////////////////////////
	
	
	// ��Ʈ�ѷ� //////////////////////////////////////////////////////////////////////////////
	// �Է� ����
	void PlayerModChange();// ��� ü����

	// Axis ����
	void MoveForward(float Value); // ��, �� �̵� ����
	void MoveRight(float Value);   // ��, �� �̵� ����
	void TurnAtRate(float Rate);   // ��, �� �þ� ����
	void LookUpAtRate(float Rate); // ��, �� �þ� ����
	/////////////////////////////////////////////////////////////////////////////////////////

// �̺�Ʈ
protected:
	// �Է� ��ġ�� �Լ� ���ε�
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ������Ʈ �ʱ�ȭ ���Ŀ� �۵��Ǵ� �Լ�
	virtual void PostInitializeComponents() override;
	// �غ� �� ��ġ�� ���� ������ ��
	virtual void BeginPlay() override;
	// �Ź� �۵��Ǵ� �Լ�
	virtual void Tick(float DeltaTime) override;

// �޼��� ����(��Ƽ�÷���)
public:

	// ��Ʈ�ѷ� Rotation�� �����ϴ� �뵵
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void NetMulticast_SendControllerRot(FRotator Send);
	bool NetMulticast_SendControllerRot_Validate(FRotator Send);
	void NetMulticast_SendControllerRot_Implementation(FRotator Send);

// �����ϱ�
public:
	// ������Ʈ
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// �̵�
	float GetPlayerSpeed() { return PlayerSpeed; } 
	float SetPlayerSpeed(float Set) { PlayerSpeed = Set; }

	// �þ�
	FRotator GetControllerRot() { return ControllerRot; }

	// �̴ϸ� ////////////////////////////////////////////////////////////////////////////////
	// 
	// �̴ϸ� ���� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MapIcon")
	EMapIconState GetIconState();
	virtual EMapIconState GetIconState_Implementation() override;

	// ���Ϳ� �������� �����ϱ�
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MapIcon")
	void SetIconWidget(class UUserWidget* Set);
	virtual void SetIconWidget_Implementation(class UUserWidget* Set) override;

	/////////////////////////////////////////////////////////////////////////////////////////


};

