// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	//RootComponent = sphereCollider;
	//sphereCollider->InitSphereRadius(52.0f);
	//sphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	//sphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);
	//sphereCollider->bHiddenInGame = false;



	//CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	//CollisionSphere->SetSphereRadius(15.0f);
	////CollisionSphere->bGenerateOverlapEvents = true;
	//CollisionSphere->SetupAttachment(RootComponent);
	//CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//CollisionSphere->bHiddenInGame = true;

	//FindComponentByClass<USphereComponent>()->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);

	//sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);


	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	sphereCollider->SetSphereRadius(15.0f);
	RootComponent = sphereCollider;
	sphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlap);
	sphereCollider->bHiddenInGame = false;

	//sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	//sphere->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	//if (SphereVisualAsset.Succeeded())
	//{
	//	sphere->SetStaticMesh(SphereVisualAsset.Object);
	//	sphere->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//	sphere->SetWorldScale3D(FVector(0.2f));
	//}


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin 1"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

