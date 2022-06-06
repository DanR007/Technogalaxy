// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/FileHelper.h"
#include "ProgressActor.generated.h"

UCLASS()
class ROBOTERRABACKSTORY_API AProgressActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgressActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FString file;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetGameComplete();
	UFUNCTION(BlueprintCallable)
		bool GetGameComplete() { return gameComplete; }
private:

	bool gameComplete;
	
	
};
