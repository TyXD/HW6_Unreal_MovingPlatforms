// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	

	MoveSpeed = 200.0f;
	MaxRange = 500.0f;
	MoveDirection = FVector(1.0f, 0.0f, 0.0f);
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + (MoveDirection.GetSafeNormal() * MaxRange);
	TargetLocation = EndLocation;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

	float DistanceToMove = MoveSpeed * DeltaTime;

	if (DistanceToMove >= DistanceToTarget)
	{
		SetActorLocation(TargetLocation);

		if (TargetLocation.Equals(EndLocation))
		{
			TargetLocation = StartLocation;
		}
		else
		{
			TargetLocation = EndLocation;
		}
	}
	else
	{
		SetActorLocation(CurrentLocation + Direction * DistanceToMove);
	}
}

// Called to bind functionality to input
void AMovingPlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}