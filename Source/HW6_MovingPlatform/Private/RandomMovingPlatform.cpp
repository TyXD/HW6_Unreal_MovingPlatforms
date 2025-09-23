// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMovingPlatform.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

ARandomMovingPlatform::ARandomMovingPlatform()
{
	ChangeDirectionInterval = 0.0f;
	RandomRange = FVector2D(800.0f, 1500.0f);
	MoveSpeedRange = FVector2D(350.0f, 750.0f);
	ScaleRange = FVector2D(0.6f, 1.5f);
	IntervalRange = FVector2D(12.0f, 21.0f);

}

void ARandomMovingPlatform::BeginPlay()
{
	MaxRange = FMath::RandRange(RandomRange.X, RandomRange.Y);
	MoveSpeed = FMath::RandRange(MoveSpeedRange.X, MoveSpeedRange.Y);
	ChangeDirectionInterval = FMath::RandRange(IntervalRange.X, IntervalRange.Y);

	MoveDirection = FVector(FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f), 0.f).GetSafeNormal();

	float RandomScale = FMath::RandRange(ScaleRange.X, ScaleRange.Y);
	SetActorScale3D(FVector(RandomScale));

	FRotator RandomRotation = FRotator(0.0f, FMath::RandRange(0.f, 360.f), 0.0f);
	SetActorRotation(RandomRotation);

	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		ChangeDirectionTimerHandle,
		this,
		&ARandomMovingPlatform::ChangeMoveDirection,
		ChangeDirectionInterval,
		true
	);
}

void ARandomMovingPlatform::ChangeMoveDirection()
{
    StartLocation = GetActorLocation();

	float RandYaw = FMath::RandRange(0.0f, 360.0f);
	FRotator Rotation = FRotator(0.0f, RandYaw, 0.0f);
	SetActorRotation(Rotation);

	FVector ForwardDirection = Rotation.Vector();

	EndLocation = StartLocation + (ForwardDirection * MaxRange);

	TargetLocation = EndLocation;

}
