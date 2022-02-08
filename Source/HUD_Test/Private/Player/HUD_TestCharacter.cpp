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
	// 멀티 복제
	SetReplicates(true);
	SetReplicateMovement(true);

	// tick on
	PrimaryActorTick.bCanEverTick = true;

	// 캡슐 콜리전 설정
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 회전 설정 (컨트롤러에 따라 캐릭터 회전 설정)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true; //
	bUseControllerRotationRoll = false;

	// 무브먼트
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	Cast<UCharacterMovementComponent>(GetMovementComponent())->NetworkSmoothingMode = ENetworkSmoothingMode::Linear;

	// 카메라 팔
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.0f, 60.0f, 80.0f));
	CameraBoom->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = true;

	// 카메라
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Mesh(몸)
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -97.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName("CharacterMesh");

	// Mesh(다리)
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

	// Mesh(팔)
	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMesh"));
	ArmMesh->SetupAttachment(FollowCamera, "CameraLoc");
	ArmMesh->SetCollisionProfileName("CharacterMesh");
	ArmMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -155.712738));
	ArmMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	ArmMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ARM_SKELETALMESH(TEXT("SkeletalMesh'/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	if (ARM_SKELETALMESH.Succeeded())
	{ // Mesh 설정
		ArmMesh->SetSkeletalMesh(ARM_SKELETALMESH.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>ARM_ANIMBP(TEXT("AnimBlueprint'/Game/Player/Anim/Arm/PlayerArmAnimBP.PlayerArmAnimBP_C'"));
	if (ARM_ANIMBP.Succeeded())
	{ // AnimIns 설정
		ArmMesh->SetAnimInstanceClass(ARM_ANIMBP.Class);
	}

	
	// 초기화
	IsMove = true; // 캐릭터가 움직이게 설정
	ControllerRot = FRotator::ZeroRotator; // 컨트롤러 회전 값
	MoveDir = FVector::ZeroVector;         // 입력 값에 따른 움직이는 방향 값
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
		IconState = EMapIconState::ALLIANCE; // 아이콘 설정
	}
}

void AHUD_TestCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어, 다른 플레이어에게 보이거나 가려야 하는 부분을 정합니다.
	ArmMesh->SetHiddenInGame(true);
	ArmMesh->SetOnlyOwnerSee(false);   // 오직 플레이어에게만 보이게 합니다. (팔)
	ArmMesh->SetCastShadow(false);    // 모두에게 그림자가 보이지 않게 합니다. (팔)
	LegMesh->HideBoneByName(FName("spine_02"), PBO_None); // 다리 Mesh의 상체를 가립니다. (다리)
	LegMesh->SetHiddenInGame(true);
	LegMesh->SetOnlyOwnerSee(false); // 오직 플레이어에게만 보이게 합니다. (다리)
	LegMesh->SetCastShadow(false);  // 모두에게 그림자가 보이지 않게 합니다. (다리)
	GetMesh()->SetOwnerNoSee(false);      // 오직 플레이어에게만 보이지 않게 합니다. (몸)		
	GetMesh()->bCastHiddenShadow = true; // 모두에게 그림자가 보이게 합니다. (몸)


	if (IsLocallyControlled())
	{
		// 플레이어 일 때
		PlayerHUD = Cast<AHUD_PlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		IconState = EMapIconState::PLAYER;
		PlayerHUD->StartMiniMap();
		//StartIcon(IconState);
		//UE_LOG(LogTemp, Warning, TEXT("AHUD_TestCharacter: BeginPlay"));
	}
	else
	{
		// 플레이어가 아닐때 (적, 동료)
		PlayerHUD = nullptr;
		IconState = EMapIconState::ALLIANCE; // 아이콘 설정

		// 플레이어에게 알리기
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
	{ // 3인칭으로 변환
		IsFPS = false;
		// 플레이어, 다른 플레이어에게 보이거나 가려야 하는 부분을 정합니다.
		ArmMesh->SetHiddenInGame(true);
		ArmMesh->SetOnlyOwnerSee(false);   // 오직 플레이어에게만 보이게 합니다. (팔)
		ArmMesh->SetCastShadow(false);    // 모두에게 그림자가 보이지 않게 합니다. (팔)
		GetMesh()->SetOwnerNoSee(false);      // 오직 플레이어에게만 보이지 않게 합니다. (몸)		
		GetMesh()->bCastHiddenShadow = true; // 모두에게 그림자가 보이게 합니다. (몸)
		LegMesh->SetHiddenInGame(false);
		LegMesh->SetOnlyOwnerSee(false); // 오직 플레이어에게만 보이게 합니다. (다리)
		LegMesh->SetCastShadow(false);  // 모두에게 그림자가 보이지 않게 합니다. (다리)

		// 카메라 설정
		CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CameraBoom->SetRelativeLocation(FVector(0.0f, 60.0f, 80.0f));
		CameraBoom->TargetArmLength = 300.0f;
	}
	else
	{ // 1인칭으로 변환
		IsFPS = true;
		// 플레이어, 다른 플레이어에게 보이거나 가려야 하는 부분을 정합니다.
		ArmMesh->SetHiddenInGame(false);
		ArmMesh->SetOnlyOwnerSee(true);   // 오직 플레이어에게만 보이게 합니다. (팔)
		ArmMesh->SetCastShadow(false);    // 모두에게 그림자가 보이지 않게 합니다. (팔)
		GetMesh()->SetOwnerNoSee(true);      // 오직 플레이어에게만 보이지 않게 합니다. (몸)		
		GetMesh()->bCastHiddenShadow = true; // 모두에게 그림자가 보이게 합니다. (몸)
		LegMesh->SetHiddenInGame(false);
		LegMesh->SetOnlyOwnerSee(true); // 오직 플레이어에게만 보이게 합니다. (다리)
		LegMesh->SetCastShadow(false);  // 모두에게 그림자가 보이지 않게 합니다. (다리)

		// 카메라 설정
		CameraBoom->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "CameraLoc");
		CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		CameraBoom->TargetArmLength = 0.0f;
	}
}

void AHUD_TestCharacter::PlayerMove(bool IsAactive, float Forward, float Right, FVector& Dir, float Speed, float DeltaSecond)
{
	if (IsAactive)
	{ // 이동 여부 확인
		// 움직이는 방향이 0이라면 반환합니다.
		if (Dir.IsZero()) return; 

		Dir.Normalize();
		float InputForce = 0.0f;

		// 입력 값이 더 강한 쪽으로 움직이는 힘들 설정합니다.
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
