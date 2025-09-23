// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomRotatePlatform.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

ARandomRotatePlatform::ARandomRotatePlatform()
{
	VisibleDuration = 10.0f;
	HiddenDuration = 2.0f;

	VisibleRange = FVector2D(8.0f, 12.0f);
	HiddenRange = FVector2D(1.4f, 3.2f);
	RotationSpeedRange = FVector2D(180.0f, 720.0f);
	ScaleRange = FVector2D(0.6f, 1.5f);
}

void ARandomRotatePlatform::BeginPlay()
{
	VisibleDuration = FMath::RandRange(VisibleRange.X, VisibleRange.Y);
	HiddenDuration = FMath::RandRange(HiddenRange.X, HiddenRange.Y);

	float RandomRotationSpeed = FMath::RandRange(RotationSpeedRange.X, RotationSpeedRange.Y);

	if (FMath::RandBool())
	{
		RandomRotationSpeed *= -1.0f;
	}
	RotationSpeed = RandomRotationSpeed;

	float RandomScale = FMath::RandRange(ScaleRange.X, ScaleRange.Y);
	SetActorScale3D(FVector(RandomScale));

	FRotator RandomRotation = FRotator(0.0f, FMath::RandRange(0.f, 360.f), 0.0f);
	SetActorRotation(RandomRotation);

	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer
	(
		VisibilityTimerHandle, 
		this,
		&ARandomRotatePlatform::HidePlatform,
		VisibleDuration,             
		false                       
	);
}

void ARandomRotatePlatform::HidePlatform()
{
	SetActorHiddenInGame(true);

	SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(
		VisibilityTimerHandle,
		this,
		&ARandomRotatePlatform::ShowPlatform,
		HiddenDuration,
		false
	);
}

void ARandomRotatePlatform::ShowPlatform()
{
	SetActorHiddenInGame(false);

	SetActorEnableCollision(true);

	GetWorld()->GetTimerManager().SetTimer(
		VisibilityTimerHandle,
		this,
		&ARandomRotatePlatform::HidePlatform,
		VisibleDuration,
		false
	);
}
