// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Bullet.generated.h"

UCLASS()
class CPROJECT_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

UFUNCTION()
void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

UFUNCTION(BlueprintCallable, Category = "Bullet")
void SpawnDecal(FVector spawnLocation);

private :

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
USphereComponent* sphereCollider;

UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
UMaterialInterface* decalToSpawn;

};
