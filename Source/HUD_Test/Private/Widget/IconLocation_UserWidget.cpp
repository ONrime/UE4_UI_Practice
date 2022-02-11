// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/IconLocation_UserWidget.h"
#include "Widget/Minimap_UserWidget.h"
#include "Components/Image.h"

void UIconLocation_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*IsStatic = false;		// �̴ϸ��� ���̴� ���� ����(�̴ϸ��� ����� ���̰� ���� ����)
	IsSoundWave = false;	// ���̺�
	IsVision = false;		// �þ߰�
	IsControllerRotation = false;*/

	HideIcone(IsHiddenIcon);
}

void UIconLocation_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("!OnwerActor"));

	if (OnwerActor && Minimap_Widget)
	{
		// �������� ȸ�� ���ϱ�
		if (IsControllerRotation)
		{
			// ��Ʈ�ѷ��� ȸ�� ���� ���� ������ ȸ��
			SetRenderTransformAngle(GetWorld()->GetFirstPlayerController()->GetControlRotation().Yaw);
		}
		else
		{
			// ������ ���⿡ ���� ȸ����ŵ�ϴ�.
			SetRenderTransformAngle(OnwerActor->GetActorRotation().Yaw);
		}
		


		// �������� ��ġ ���ϱ�
		FVector OnwerLoc = OnwerActor->GetActorLocation(); // �� �������� ����
		FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		
		// �ܰ� ũ����� ���� �̴ϸ� �������Դϴ�.
		// �̴ϸ� ���� ���� ���ؾ� �̴ϸʿ� �°� ��ǥ�� �����˴ϴ�.
		// 300�� �̴ϸ� ũ�� �Դϴ�.
		float MiniMapSetting = (Minimap_Widget->Map_Dimensions / 300.0f) * Minimap_Widget->Map_Zoom;

		float IconLocX = ((OnwerLoc.X - PlayerLoc.X) * -1.0f) / MiniMapSetting;
		float IconLocY = (OnwerLoc.Y - PlayerLoc.Y) / MiniMapSetting;

		// �������� ��ġ�Դϴ�.
		FVector2D IconLoc = FVector2D(IconLocX, IconLocY);

		// ���⼭ ������ ������ �̴ϸ� ������ ���� �������� �̴ϸ��� ���͹����ϴ�.
		// �̸� �����ϱ� ���ؼ��� �̴ϸ��� ������������ ������ Ȱ���Ͽ� �Ÿ��� �Ѿ�� �ʰ� �ؾ� �մϴ�.

		// �̴ϸ� �߾ӿ� �ִ� �÷��̾�� �� �����ܰ��� �����Դϴ�.
		float IconAngle = FMath::RadiansToDegrees(FMath::Atan2(IconLocY, IconLocX));

		// 130�� ������ �̴ϸ��� ũ�Ⱑ 300 ������ 150 �ణ�� �������� ���� ���� -20�ؼ� 130�Դϴ�.
		float IconScala = FMath::Clamp(IconLoc.Size(), 0.0f, 130.0f);

		// ���� ��ǥ�� ���� �����Դϴ�.
		SetRenderTranslation(FVector2D(IconScala * FMath::Sin(PI / (180.f) * IconAngle)
			, IconScala * FMath::Cos(PI / (180.f) * IconAngle)));

		// ������ ������ ���� ���
		// IsStatic�� true�� �̴ϸʿ� ����� ������� �մϴ�.

		if (!IsStatic && !IsHiddenIcon)
		{
			if (IconScala >= 130.0f)
			{
				// ������
				if (Icon_Image->GetVisibility() != ESlateVisibility::Hidden)
				{
					HideIcone(true);
				}
			}
			else
			{
				// ���̱�
				if (Icon_Image->GetVisibility() != ESlateVisibility::Visible)
				{
					HideIcone(false);
				}
			}
		}
		/*/bool HideIcone = IsHiddenIcon;
		if (!IsStatic && !IsHiddenIcon)
		{
			if (IconScala >= 130.0f)
			{
				HideIcone = true;
			}
			else
			{
				HideIcone = false;
			}
		}

		if (HideIcone)
		{
			if (Icon_Image) Icon_Image->SetVisibility(ESlateVisibility::Hidden);
			if (Icon_Sight_Widget) Icon_Sight_Widget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if (Icon_Image) Icon_Image->SetVisibility(ESlateVisibility::Visible);
			if (Icon_Sight_Widget) Icon_Sight_Widget->SetVisibility(ESlateVisibility::Visible);
		}*/
	}
}

void UIconLocation_UserWidget::HideIcone(bool State)
{
	if (State)
	{
		if (Icon_Image) Icon_Image->SetVisibility(ESlateVisibility::Hidden);
		if (Icon_Sight_Widget) Icon_Sight_Widget->SetVisibility(ESlateVisibility::Hidden);
	}
	else 
	{
		if (Icon_Image) Icon_Image->SetVisibility(ESlateVisibility::Visible);
		if (Icon_Sight_Widget) Icon_Sight_Widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UIconLocation_UserWidget::HideIconEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("HideIconEnd"));
	IsHiddenIcon = true;
	HideIcone(IsHiddenIcon);
}

void UIconLocation_UserWidget::IconOnwerAttack(bool Set)
{
	IsHiddenIcon = Set;
	HideIcone(IsHiddenIcon);
	if (GetWorld()->GetTimerManager().IsTimerActive(HiddenEndTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(HiddenEndTimer);
	}
	UE_LOG(LogTemp, Warning, TEXT("HiddenEndTimer"));
	GetWorld()->GetTimerManager().SetTimer(HiddenEndTimer, this, &UIconLocation_UserWidget::HideIconEnd, 3.0f, false);
}
