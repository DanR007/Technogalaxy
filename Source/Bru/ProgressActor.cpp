// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressActor.h"


// Sets default values
AProgressActor::AProgressActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProgressActor::BeginPlay()
{
	Super::BeginPlay();
    file = FPaths::ProjectConfigDir();
    file.Append(TEXT("data.txt"));

    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    FString FileContent;
    // Always first check if the file that you want to manipulate exist.
    if (FileManager.FileExists(*file))
    {
        // We use the LoadFileToString to load the file into
        if (FFileHelper::LoadFileToString(FileContent, *file, FFileHelper::EHashOptions::None))
        {
            UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Text From File: %s"), *FileContent);
            gameComplete = *FileContent == FString("True");
        }
        else
        {
            FFileHelper::SaveStringToFile(FString(TEXT("False")), *file);
            UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Did not load text from file"));
        }
    }
    else
    {
        FFileHelper::SaveStringToFile(FString(TEXT("False")), *file);
        UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
        UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"), *file);
    }
	
	
}

// Called every frame
void AProgressActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProgressActor::SetGameComplete()
{

    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    // Always first check if the file that you want to manipulate exist.
    if (FileManager.FileExists(*file))
    {
        // We use the LoadFileToString to load the file into
        if (FFileHelper::SaveStringToFile(FString(TEXT("True")), *file))
        {
            UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Sucsesfuly Written: True"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Failed to write FString to file."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
        UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"), *file);
    }
	gameComplete = true;
}

