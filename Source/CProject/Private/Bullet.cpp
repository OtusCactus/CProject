// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
	//sphereTrigger->InitSphereRadius(52.0f);
	//sphereTrigger->SetCollisionProfileName(TEXT("SphereTrigger"));
	//sphereTrigger->SetupAttachment(RootComponent);

	//this->GetSphereComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);

	sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	RootComponent = sphere;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		sphere->SetStaticMesh(SphereVisualAsset.Object);
		sphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		sphere->SetWorldScale3D(FVector(0.2f));
	}

	sphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	sphereTrigger->SetupAttachment(RootComponent);
	sphereTrigger->InitSphereRadius(52.0f);
	sphereTrigger->SetCollisionProfileName(TEXT("Pawn"));
	sphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);

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

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("miaou"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

