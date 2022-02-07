// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/IconLocation_UserWidget.h"
#include "Widget/Minimap_UserWidget.h"
#include "Components/Image.h"

void UIconLocation_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UIconLocation_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("!OnwerActor"));

	if (OnwerActor && Minimap_Widget)
	{
		// 아이콘의 회전 구하기
		// 액터의 방향에 따라 회전시킵니다.
		SetRenderTransformAngle(OnwerActor->GetActorRotation().Yaw);


		// 아이콘의 위치 구하기
		FVector OnwerLoc = OnwerActor->GetActorLocation(); // 이 아이콘의 액터
		FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		
		// 줌과 크기등을 곱한 미니맵 설정값입니다.
		// 미니맵 설정 값을 곱해야 미니맵에 맞게 좌표가 설정됩니다.
		// 300은 미니맵 크기 입니다.
		float MiniMapSetting = (Minimap_Widget->Map_Dimensions / 300.0f) * Minimap_Widget->Map_Zoom;

		float IconLocX = ((OnwerLoc.X - PlayerLoc.X) * -1.0f) / MiniMapSetting;
		float IconLocY = (OnwerLoc.Y - PlayerLoc.Y) / MiniMapSetting;

		// 아이콘의 위치입니다.
		FVector2D IconLoc = FVector2D(IconLocX, IconLocY);

		// 여기서 끝내도 되지만 미니맵 끝으로 가면 아이콘이 미니맵을 나와버립니다.
		// 이를 방지하기 위해서는 미니맵이 원형태임으로 각도를 활용하여 거리를 넘어가지 않게 해야 합니다.

		// 미니맵 중앙에 있는 플레이어와 이 아이콘과의 각도입니다.
		float IconAngle = FMath::RadiansToDegrees(FMath::Atan2(IconLocY, IconLocX));

		// 130인 이유는 미니맵의 크기가 300 절반은 150 약간더 안쪽으로 들어가기 위해 -20해서 130입니다.
		float IconScala = FMath::Clamp(IconLoc.Size(), 0.0f, 130.0f);

		// 구한 좌표에 따라 움직입니다.
		SetRenderTranslation(FVector2D(IconScala * FMath::Sin(PI / (180.f) * IconAngle)
			, IconScala * FMath::Cos(PI / (180.f) * IconAngle)));

		// 아이콘 설정에 따른 계산
		// IsStatic가 true면 미니맵에 벗어나면 사라지게 합니다.
		if (Icon_Image && !IsStatic)
		{
			if (IconScala >= 130.0f)
			{
				Icon_Image->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				Icon_Image->SetVisibility(ESlateVisibility::Visible);
			}
		}

	}
}
