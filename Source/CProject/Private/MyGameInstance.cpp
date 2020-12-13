// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "D:\IIM\A4\Unreal\Projet\CProject\Source\CProject\Public\SaveGameInSlot.h"
#include "D:\IIM\A4\Unreal\Projet\CProject\Source\CProject\CProjectCharacter.h"

void UMyGameInstance::SaveGame(int slotID)
{
    USaveGameInSlot* SaveInstance = Cast<USaveGameInSlot>(UGameplayStatics::CreateSaveGameObject(USaveGameInSlot::StaticClass()));

    if (SaveInstance == nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Couldn't save"));
        return;
    }


    AActor* Avatar = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    ACProjectCharacter* player = Cast<ACProjectCharacter>(Avatar);

    if (player != nullptr) {
        playerHealth = player->health;

        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Health player: %lld"), player->health));
        SaveInstance->saveHealth = playerHealth;
    }

    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Health instance: %lld"), playerHealth));
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Health save: %lld"), SaveInstance->saveHealth));

    if (UGameplayStatics::SaveGameToSlot(SaveInstance, "SaveGame" + slotID, 0)) {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Game saved in slot %lld"), slotID));
    }

}

void UMyGameInstance::LoadGame(int slotID)
{
    USaveGameInSlot* SaveInstance = Cast<USaveGameInSlot>(UGameplayStatics::LoadGameFromSlot("SaveGame" + slotID, 0));

    if (SaveInstance == nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No save available"));
        return;
    }

    isGameLoaded = true;

    playerHealth = SaveInstance->saveHealth;


    GEngine->AddOnScreenDebugMessage(-10, 3.f, FColor::Yellow, FString::Printf(TEXT("Health save: %lld"), SaveInstance->saveHealth));
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Health instance: %d"), playerHealth));

}