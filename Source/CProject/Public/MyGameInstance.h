// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	float myHealth = 100;

};
