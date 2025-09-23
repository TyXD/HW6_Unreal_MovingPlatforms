// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
#include "PlatformSpawnRow.h"

// Sets default values
APlatformSpawner::APlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	RootComponent = SpawningBox;

	PlatformDataTable = nullptr;
	NumToSpawn = 15;
}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (!PlatformDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlatformDataTable is not set in %s"), *GetName());
		return;
	}

	for (int32 i = 0; i < NumToSpawn; ++i)
	{
		if (FPlatformSpawnRow* SelectedRow = GetRandomPlatformRow())
		{
			SpawnPlatform(SelectedRow->ItemClass);
		}
	}
}

FVector APlatformSpawner::GetRandomPointInVolume() const
{
	const FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	const FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

FPlatformSpawnRow* APlatformSpawner::GetRandomPlatformRow() const
{
	if (!PlatformDataTable) return nullptr;

	TArray<FPlatformSpawnRow*> AllRows;
	PlatformDataTable->GetAllRows<FPlatformSpawnRow>(TEXT(""), AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FPlatformSpawnRow* Row : AllRows)
	{
		TotalChance += Row->SpawnChance;
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	for (FPlatformSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

void APlatformSpawner::SpawnPlatform(TSubclassOf<AActor> PlatformClass)
{
	if (!PlatformClass) return;
	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<AActor>(
			PlatformClass,
			GetRandomPointInVolume(),
			FRotator::ZeroRotator
		);
	}
}


