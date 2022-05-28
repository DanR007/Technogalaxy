// Fill out your copyright notice in the Description page of Project Settings.
#include<iostream>
#include<time.h>
#include "ManagerCPP.h"
#include <vector>
#include "AsterCPP.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AManagerCPP::AManagerCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<AActor> aster_bp(TEXT("/Game/Blueprint/NeededBP/Asteroid"));
	ConstructorHelpers::FClassFinder<AActor> power_bp(TEXT("/Game/Blueprint/PowerUp"));
	ConstructorHelpers::FClassFinder<AActor> enemy_bp(TEXT("/Game/Blueprint/NeededBP/EnemyShuttles"));
	asteroid = aster_bp.Class;
	Updates = power_bp.Class;
	enemyShuttle = enemy_bp.Class;
}

// Called when the game starts or when spawned
void AManagerCPP::BeginPlay()
{

	Super::BeginPlay();
	std::srand(std::time(NULL));
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AManagerCPP::SpawnSMTH, 7, true, 6);
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
	std::vector<TSubclassOf<AActor>> arr;
	AActor* smthAct;
	levelCount = score / 10;
	
	if (levelCount < 3)
	{
		arr = { asteroid,asteroid, asteroid };
		if (levelCount == 0)
		{
			speed = 1;
		}
		else
		{
			speed = 1.1;
		}
		HP = 10;
	}
	else
		if(levelCount < 5)
		{
			arr = { asteroid,asteroid, asteroid,asteroid,asteroid };
			if (levelCount == 3)
				HP = 10;
			else
				HP = 13;
			speed = 1.1;
		}
		else
		{
			if (levelCount == 5)
			{
				arr = { asteroid,asteroid, asteroid,asteroid,enemyShuttle};
			}
			else
			{
				if (levelCount == 6)
				{
					arr = { asteroid,asteroid, asteroid,enemyShuttle,enemyShuttle };
				}
				else
				{
					if (levelCount == 7)
					{
						arr = { enemyShuttle,enemyShuttle, enemyShuttle,enemyShuttle };
					}
					else
					{
						arr = { enemyShuttle,enemyShuttle, enemyShuttle,enemyShuttle,enemyShuttle };
						if (score % 40 == 0)
						{
							HP++;
						}
						else
						{
							if (score % 30 == 0)
							{
								speed += 0.005;
							}
						}
						if (score % 60 == 0)
						{
							maxPower++;
						}
						if (score % 70 == 0)
						{
							speedRel-=0.2f;
						}
					}
				}
			}
		}

	levelMultiplier = arr.size();
	for (int i = 0; i < arr.size(); i++)
	{
		int j = std::rand() % PointOfSpawn.Num();
		smthAct = GetWorld()->SpawnActor<AActor>(arr[i], PointOfSpawn[j]->GetActorTransform());
		Cast<AAsterCPP>(smthAct)->speed = speed;
		Cast<AAsterCPP>(smthAct)->HP = HP;
		Cast<AAsterCPP>(smthAct)->speedRel = speedRel;
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
	for (int i = 0; i < levelMultiplier; i++)
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