// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "D:\IIM\A4\Unreal\Projet\CProject\Source\CProject\Public\PickableActorComponent.h"
#include "SaveGameInSlot.generated.h"
/**
 * 
 */
UCLASS()
class CPROJECT_API USaveGameInSlot : public USaveGame
{
	GENERATED_BODY()
	

public :
	
int saveHealth;

};
