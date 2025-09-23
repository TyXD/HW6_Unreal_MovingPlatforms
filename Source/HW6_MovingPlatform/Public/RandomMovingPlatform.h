// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingPlatform.h"
#include "RandomMovingPlatform.generated.h"


/**
 * 
 */
UCLASS()
class HW6_MOVINGPLATFORM_API ARandomMovingPlatform : public AMovingPlatform
{
	GENERATED_BODY()

public:
	ARandomMovingPlatform();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer Settings")
	float ChangeDirectionInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D RandomRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D MoveSpeedRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D IntervalRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D ScaleRange;

private:
	FTimerHandle ChangeDirectionTimerHandle;

protected:
	virtual void BeginPlay() override;

private:
	void ChangeMoveDirection();

};
