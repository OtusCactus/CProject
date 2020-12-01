// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameInSlot.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API USaveGameInSlot : public USaveGame
{
	GENERATED_BODY()
	

public :
	
UPROPERTY(EditAnywhere)
float health = 100;

};
