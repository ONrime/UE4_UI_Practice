#include "Player/HUD_TestCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Game/HUD_PlayerHUD.h"


AHUD_TestCharacter::AHUD_TestCharacter()
{
	// ��Ƽ ����
	SetReplicates(true);
	SetReplicateMovement(true);

	// tick on
	PrimaryActorTick.bCanEverTick = true;

	// ĸ�� �ݸ��� ����
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// ȸ�� ���� (��Ʈ�ѷ��� ���� ĳ���� ȸ�� ����)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true; //
	bUseControllerRotationRoll = false;

	// �����Ʈ
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	Cast<UCharacterMovementComponent>(GetMovementComponent())->NetworkSmoothingMode = ENetworkSmoothingMode::Linear;

	// ī�޶� ��
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.0f, 60.0f, 80.0f));
	CameraBoom->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = true;

	// ī�޶�
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Mesh(��)
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -97.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName("CharacterMesh");

	// Mesh(�ٸ�)
	LegMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LegMesh"));
	LegMesh->SetupAttachment(RootComponent);
	LegMesh->SetCollisionProfileName("CharacterMesh");
	LegMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -97.0f));
	LegMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	LegMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>FULLBODY_SKELETALMESH(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (FULLBODY_SKELETALMESH.Succeeded()) 
	{ 
		GetMesh()->SetSkeletalMesh(FULLBODY_SKELETALMESH.Object); 
		LegMesh->SetSkeletalMesh(FULLBODY_SKELETALMESH.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>FULLBODY_ANIMBP(TEXT("AnimBlueprint'/Game/Player/Anim/Body/PlayerBodyAnimBP.PlayerBodyAnimBP_C'"));
	if (FULLBODY_ANIMBP.Succeeded()) 
	{ 
		GetMesh()->SetAnimInstanceClass(FULLBODY_ANIMBP.Class); 
		LegMesh->SetAnimInstanceClass(FULLBODY_ANIMBP.Class);
	}

	// Mesh(��)
	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMesh"));
	ArmMesh->SetupAttachment(FollowCamera, "CameraLoc");
	ArmMesh->SetCollisionProfileName("CharacterMesh");
	ArmMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -155.712738));
	ArmMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	ArmMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ARM_SKELETALMESH(TEXT("SkeletalMesh'/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	if (ARM_SKELETALMESH.Succeeded())
	{ // Mesh ����
		ArmMesh->SetSkeletalMesh(ARM_SKELETALMESH.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>ARM_ANIMBP(TEXT("AnimBlueprint'/Game/Player/Anim/Arm/PlayerArmAnimBP.PlayerArmAnimBP_C'"));
	if (ARM_ANIMBP.Succeeded())
	{ // AnimIns ����
		ArmMesh->SetAnimInstanceClass(ARM_ANIMBP.Class);
	}

	
	// �ʱ�ȭ
	IsMove = true; // ĳ���Ͱ� �����̰� ����
	ControllerRot = FRotator::ZeroRotator; // ��Ʈ�ѷ� ȸ�� ��
	MoveDir = FVector::ZeroVector;         // �Է� ���� ���� �����̴� ���� ��
	PlayerSpeed = 100.0f;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

}

void AHUD_TestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("ChangeMode", IE_Released, this, &AHUD_TestCharacter::PlayerModChange);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHUD_TestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHUD_TestCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AHUD_TestCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AHUD_TestCharacter::LookUpAtRate);
}

void AHUD_TestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsLocallyControlled())
	{
		IconState = EMapIconState::PLAYER;
	}
	else {
		IconState = EMapIconState::ALLIANCE; // ������ ����
	}
}

void AHUD_TestCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾�, �ٸ� �÷��̾�� ���̰ų� ������ �ϴ� �κ��� ���մϴ�.
	ArmMesh->SetHiddenInGame(true);
	ArmMesh->SetOnlyOwnerSee(false);   // ���� �÷��̾�Ը� ���̰� �մϴ�. (��)
	ArmMesh->SetCastShadow(false);    // ��ο��� �׸��ڰ� ������ �ʰ� �մϴ�. (��)
	LegMesh->HideBoneByName(FName("spine_02"), PBO_None); // �ٸ� Mesh�� ��ü�� �����ϴ�. (�ٸ�)
	LegMesh->SetHiddenInGame(true);
	LegMesh->SetOnlyOwnerSee(false); // ���� �÷��̾�Ը� ���̰� �մϴ�. (�ٸ�)
	LegMesh->SetCastShadow(false);  // ��ο��� �׸��ڰ� ������ �ʰ� �մϴ�. (�ٸ�)
	GetMesh()->SetOwnerNoSee(false);      // ���� �÷��̾�Ը� ������ �ʰ� �մϴ�. (��)		
	GetMesh()->bCastHiddenShadow = true; // ��ο��� �׸��ڰ� ���̰� �մϴ�. (��)


	if (IsLocallyControlled())
	{
		// �÷��̾� �� ��
		PlayerHUD = Cast<AHUD_PlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		IconState = EMapIconState::PLAYER;
		PlayerHUD->StartMiniMap();
		//StartIcon(IconState);
		//UE_LOG(LogTemp, Warning, TEXT("AHUD_TestCharacter: BeginPlay"));
	}
	else
	{
		// �÷��̾ �ƴҶ� (��, ����)
		PlayerHUD = nullptr;
		IconState = EMapIconState::ALLIANCE; // ������ ����

		// �÷��̾�� �˸���
		AHUD_PlayerHUD* OtherPlayerHUD = Cast<AHUD_PlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		//if(OtherPlayer && OtherPlayer->PlayerHUD) OtherPlayer->PlayerHUD->UpdateMinimapEvent.Broadcast(this, (int)IconState);
		//if(OtherPlayer && OtherPlayer->PlayerHUD) OtherPlayer->PlayerHUD->UpdateMinimapEvent.Execute(this, (int)IconState);
		if (OtherPlayerHUD) OtherPlayerHUD->UpdateMiniMap(this, (int)IconState);

	}
	
	
}

void AHUD_TestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerMove(IsMove, InputForwardDir, InputRightDir, MoveDir, PlayerSpeed, DeltaTime);
	if (HasAuthority())
	{
		if (IsLocallyControlled())
		{
			
		}
		else 
		{

		}

		ControllerRot = GetControlRotation();
		NetMulticast_SendControllerRot(ControllerRot);
	}
	
}


bool AHUD_TestCharacter::NetMulticast_SendControllerRot_Validate(FRotator Send)
{
	return true;
}

void AHUD_TestCharacter::NetMulticast_SendControllerRot_Implementation(FRotator Send)
{
	ControllerRot = Send;
}

void AHUD_TestCharacter::TurnAtRate(float Rate)
{
	//UE_LOG(LogTemp, Warning, TEXT("TurnAtRate: %f"), Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHUD_TestCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHUD_TestCharacter::PlayerModChange()
{
	if (IsFPS)
	{ // 3��Ī���� ��ȯ
		IsFPS = false;
		// �÷��̾�, �ٸ� �÷��̾�� ���̰ų� ������ �ϴ� �κ��� ���մϴ�.
		ArmMesh->SetHiddenInGame(true);
		ArmMesh->SetOnlyOwnerSee(false);   // ���� �÷��̾�Ը� ���̰� �մϴ�. (��)
		ArmMesh->SetCastShadow(false);    // ��ο��� �׸��ڰ� ������ �ʰ� �մϴ�. (��)
		GetMesh()->SetOwnerNoSee(false);      // ���� �÷��̾�Ը� ������ �ʰ� �մϴ�. (��)		
		GetMesh()->bCastHiddenShadow = true; // ��ο��� �׸��ڰ� ���̰� �մϴ�. (��)
		LegMesh->SetHiddenInGame(false);
		LegMesh->SetOnlyOwnerSee(false); // ���� �÷��̾�Ը� ���̰� �մϴ�. (�ٸ�)
		LegMesh->SetCastShadow(false);  // ��ο��� �׸��ڰ� ������ �ʰ� �մϴ�. (�ٸ�)

		// ī�޶� ����
		CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CameraBoom->SetRelativeLocation(FVector(0.0f, 60.0f, 80.0f));
		CameraBoom->TargetArmLength = 300.0f;
	}
	else
	{ // 1��Ī���� ��ȯ
		IsFPS = true;
		// �÷��̾�, �ٸ� �÷��̾�� ���̰ų� ������ �ϴ� �κ��� ���մϴ�.
		ArmMesh->SetHiddenInGame(false);
		ArmMesh->SetOnlyOwnerSee(true);   // ���� �÷��̾�Ը� ���̰� �մϴ�. (��)
		ArmMesh->SetCastShadow(false);    // ��ο��� �׸��ڰ� ������ �ʰ� �մϴ�. (��)
		GetMesh()->SetOwnerNoSee(true);      // ���� �÷��̾�Ը� ������ �ʰ� �մϴ�. (��)		
		GetMesh()->bCastHiddenShadow = true; // ��ο��� �׸��ڰ� ���̰� �մϴ�. (��)
		LegMesh->SetHiddenInGame(false);
		LegMesh->SetOnlyOwnerSee(true); // ���� �÷��̾�Ը� ���̰� �մϴ�. (�ٸ�)
		LegMesh->SetCastShadow(false);  // ��ο��� �׸��ڰ� ������ �ʰ� �մϴ�. (�ٸ�)

		// ī�޶� ����
		CameraBoom->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "CameraLoc");
		CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		CameraBoom->TargetArmLength = 0.0f;
	}
}

void AHUD_TestCharacter::PlayerMove(bool IsAactive, float Forward, float Right, FVector& Dir, float Speed, float DeltaSecond)
{
	if (IsAactive)
	{ // �̵� ���� Ȯ��
		// �����̴� ������ 0�̶�� ��ȯ�մϴ�.
		if (Dir.IsZero()) return; 

		Dir.Normalize();
		float InputForce = 0.0f;

		// �Է� ���� �� ���� ������ �����̴� ���� �����մϴ�.
		if (FMath::Abs(Forward) > FMath::Abs(Right)) 
		{
			InputForce = FMath::Abs(Forward);
		}
		else { InputForce = FMath::Abs(Right); }

		//UE_LOG(LogTemp, Warning, TEXT("Input: %f"), FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, PlayerSpeed), InputForce));
		AddMovementInput(Dir, FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, Speed), InputForce) * DeltaSecond);
	}
}

void AHUD_TestCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr))
	{
		InputForwardDir = Value;

		FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X);
		Direction.Z = 0.0f;
		Direction.Normalize();
		MoveDir += Direction * FMath::Clamp(Value, -1.0f, 1.0f);
	}
}

void AHUD_TestCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) )
	{
		InputRightDir = Value;

		FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);
		Direction.Z = 0.0f;
		Direction.Normalize();
		MoveDir += Direction * FMath::Clamp(Value, -1.0f, 1.0f);
	}
}

EMapIconState AHUD_TestCharacter::GetIconState_Implementation()
{
	if (PlayerHUD)
	{
		//PlayerHUD
		//PlayerHUD->UpdateMinimapEvent.Execute();
		//PlayerHUD->StartMiniMap((int)Set);
	}
	return IconState;
}
