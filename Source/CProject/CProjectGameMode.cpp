// Copyright Epic Games, Inc. All Rights Reserved.

#include "CProjectGameMode.h"
#include "CProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACProjectGameMode::ACProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	FStringAssetReference itemRef = "Blueprint'/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter'";
	UObject* itemObj = itemRef.ResolveObject();
	PlayerToSpawn = Cast<UBlueprint>(itemObj);

}

void ACProjectGameMode::RewpawnPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Respawn"));

    if (PlayerToSpawn == nullptr) return;

    APlayerController* player = GetWorld()->GetFirstPlayerController();
    FVector playerLocation;
    FRotator quat;
    if (player != nullptr)
    {
        quat = player->GetPawn()->GetActorRotation();
        playerLocation = player->GetPawn()->GetActorLocation();
        player->GetPawn()->Destroy();
    }

    const FActorSpawnParameters spawnParameters;


    const FVector respawnLocation = respawnPosition->GetDefaultAttachComponent()->GetComponentLocation();
    const FRotator respawnRotation = respawnPosition->GetDefaultAttachComponent()->GetComponentRotation();
    //spawn new player, doesn't work in build ?? but works in editor

    AActor* newPlayer = GetWorld()->SpawnActor<AActor>(PlayerToSpawn->GeneratedClass, respawnLocation, respawnRotation, spawnParameters);

    APawn* newPlayerPawn = Cast<APawn>(newPlayer);

    player->Possess(newPlayerPawn);
    DefaultPawnClass = newPlayerPawn->GetClass();

}

void ACProjectGameMode::SetRespawnPoint(AActor* respawnPoint)
{
    respawnPosition = respawnPoint;
}

//void ACProjectGameMode::SaveGame(int slotID)
//{
//    USaveGameInSlot* SaveInstance = Cast<USaveGameInSlot>(UGameplayStatics::CreateSaveGameObject(USaveGameInSlot::StaticClass()));
//
//    if (SaveInstance == nullptr) {
//        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Couldn't save"));
//        return;
//    }
//
//    myHealth -= 10;
//    SaveInstance->health = myHealth;
//
//    GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Health: %f"), myHealth));
//
//    if (UGameplayStatics::SaveGameToSlot(SaveInstance, "SaveGame", slotID)) {
//        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Game saved in slot %lld"), slotID));
//    }
//
//}
//
//void ACProjectGameMode::LoadGame(int slotID)
//{
//    USaveGameInSlot* SaveInstance = Cast<USaveGameInSlot>(UGameplayStatics::LoadGameFromSlot("SaveGame", slotID));
//
//    if (SaveInstance == nullptr) {
//        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No save available"));
//        return;
//    }
//
//    myHealth = SaveInstance->health;
//
//    GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Health: %f"), myHealth));
//
//}
