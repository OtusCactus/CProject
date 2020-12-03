// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActorComponent.h"
#include "Engine/DataTable.h"
#include "D:\IIM\A4\Unreal\Projet\CProject\Source\CProject\CProjectCharacter.h"

// Sets default values for this component's properties
UPickableActorComponent::UPickableActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPickableActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UPickableActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickableActorComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag("Player")) {
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));

	ACProjectCharacter* player = Cast<ACProjectCharacter>(OtherActor);

	FItemStructure* item = itemsData->FindRow<FItemStructure>(itemRowName, "", true);

	if (item != nullptr) {
		FString pwease = item->itemName;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pwease);
		if (player != nullptr) {
			player->AddItem(*item);
		}

		GetOwner()->Destroy();
	}

}

void UPickableActorComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void UPickableActorComponent::AddCollisionDynamic()
{
	OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &UPickableActorComponent::OnBeginOverlap);
	OverlapVolume->OnComponentEndOverlap.AddDynamic(this, &UPickableActorComponent::OnEndOverlap);
}

