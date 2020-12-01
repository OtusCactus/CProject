// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "D:\IIM\A4\Unreal\Projet\CProject\Source\CProject\Public\SaveGameInSlot.h"

void UMyGameInstance::SaveGame(int slotID)
{
    USaveGameInSlot* SaveInstance = Cast<USaveGameInSlot>(UGameplayStatics::CreateSaveGameObject(USaveGameInSlot::StaticClass()));

    if (SaveInstance == nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Couldn't save"));
        return;
    }

    myHealth -= 10;
    SaveInstance->health = myHealth;

    GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Health: %f"), myHealth));

    if (UGameplayStatics::SaveGameToSlot(SaveInstance, "SaveGame" + slotID, 0)) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Game saved in slot %lld"), slotID));
    }

}

void UMyGameInstance::LoadGame(int slotID)
{
    USaveGameInSlot* SaveInstance = Cast<USaveGameInSlot>(UGameplayStatics::LoadGameFromSlot("SaveGame" + slotID, 0));

    if (SaveInstance == nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No save available"));
        return;
    }

    myHealth = SaveInstance->health;
    GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Health: %f"), myHealth));

}