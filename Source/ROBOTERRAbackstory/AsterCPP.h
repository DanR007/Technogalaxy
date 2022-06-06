// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsterCPP.generated.h"

UCLASS()
class ROBOTERRABACKSTORY_API AAsterCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsterCPP();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float speed = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int HP = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float speedRel = 4;
};
