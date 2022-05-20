// Fill out your copyright notice in the Description page of Project Settings.
#include<iostream>
#include<time.h>
#include "ManagerCPP.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AManagerCPP::AManagerCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<AActor> enemy_bp(TEXT("/Game/Blueprint/NeededBP/EnemyShuttle"));
	ConstructorHelpers::FClassFinder<AActor> power_bp(TEXT("/Game/Blueprint/PowerUp"));
	enemyShuttle = enemy_bp.Class;
	Updates = power_bp.Class;
}

// Called when the game starts or when spawned
void AManagerCPP::BeginPlay()
{

	Super::BeginPlay();
	std::srand(std::time(NULL));
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AManagerCPP::SpawnSMTH, 5, true);
	GetWorld()->GetTimerManager().SetTimer(up_timer, this, &AManagerCPP::SpawnUpgrades, 20, true);
	GameOver = false;
}

// Called every frame
void AManagerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AManagerCPP::SpawnSMTH()
{
	for (int i = 0; i < 2 + levelMultiplier; i++)
	{
		int j = std::rand() % PointOfSpawn.Num();
		GetWorld()->SpawnActor<AActor>(enemyShuttle, PointOfSpawn[j]->GetActorTransform());
		PointOfSpawnUsed.Add(PointOfSpawn[j]);
		PointOfSpawn.RemoveSingle(PointOfSpawn[j]);
	}
	FillArr();
}


void AManagerCPP::SpawnUpgrades()
{
	GetWorld()->SpawnActor<AActor>(Updates, PointOfSpawn[std::rand() % PointOfSpawn.Num()]->GetActorTransform());
}

void AManagerCPP::FillArr()
{
	for (int i = 0; i < 2 + levelMultiplier; i++)
	{
		PointOfSpawn.Add(PointOfSpawnUsed[0]);
		PointOfSpawnUsed.RemoveSingle(PointOfSpawnUsed[0]);
	}
}

void AManagerCPP::SetGameOver(bool isGameOver) 
{
	GameOver = isGameOver;
	
	GetWorld()->GetFirstPlayerController()->SetPause(true);
}