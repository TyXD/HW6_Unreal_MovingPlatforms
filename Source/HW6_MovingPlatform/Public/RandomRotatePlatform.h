// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RotatePlatform.h"
#include "RandomRotatePlatform.generated.h"

/**
 * 
 */
UCLASS()
class HW6_MOVINGPLATFORM_API ARandomRotatePlatform : public ARotatePlatform
{
	GENERATED_BODY()

public:
	ARandomRotatePlatform();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer Settings")
	float VisibleDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer Settings")
	float HiddenDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D RotationSpeedRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D ScaleRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D VisibleRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Settings")
	FVector2D HiddenRange;

private:
	FTimerHandle VisibilityTimerHandle;

protected:
	virtual void BeginPlay() override;

private:
	void HidePlatform();

	void ShowPlatform();
};
