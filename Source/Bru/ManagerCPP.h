// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ManagerCPP.generated.h"

UCLASS()
class BRU_API AManagerCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AManagerCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle timer;
	FTimerHandle up_timer;

	void SpawnUpgrades();
	void SpawnSMTH();
	void FillArr();

	TSubclassOf<AActor> enemyShuttle;
	TSubclassOf<AActor> Updates;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> PointOfSpawn;

	TArray<AActor*> PointOfSpawnUsed;

	UPROPERTY(BlueprintReadOnly)
		int score;
	UPROPERTY(BlueprintReadOnly)
		bool GameOver;
	UPROPERTY(BlueprintReadOnly)
		int levelMultiplier = 1;
	UPROPERTY(BlueprintReadOnly)
		int levelCount = 1;

	UFUNCTION(BlueprintCallable)
		void AddScore() { score++; }
	UFUNCTION(BlueprintCallable)
		void SetGameOver(bool isGameOver);
	UFUNCTION(BlueprintCallable)
		void NewLevel() { levelMultiplier ++;
	levelCount++;
	levelMultiplier = UKismetMathLibrary::Clamp(levelMultiplier, 1, PointOfSpawn.Num() - 5);
	}
	
};
