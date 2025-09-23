// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

class UBoxComponent;
class UDataTable;
struct FPlatformSpawnRow;
UCLASS()
class HW6_MOVINGPLATFORM_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* PlatformDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 NumToSpawn;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector GetRandomPointInVolume() const;

	FPlatformSpawnRow* GetRandomPlatformRow() const;

	void SpawnPlatform(TSubclassOf<AActor> PlatformClass);

};
