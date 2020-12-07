// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "D:\IIM\A4\Unreal\Projet\CProject\Source\CProject\Public\PickableActorComponent.h"
#include "MyGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class CPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public :


UFUNCTION(BlueprintCallable)
void SaveGame(int slotID);


UFUNCTION(BlueprintCallable)
void LoadGame(int slotID);

int playerHealth;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
int playerMaxHealth = 100;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
bool isGameLoaded = false;

TArray<FItemStructure> playerInventory;

TArray<int> playerInventoryTracking;


};
