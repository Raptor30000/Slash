// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Slash\DebugMacros.h"
#include "Components/SphereComponent.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	int32 AveInt = Avg<int32>(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("Average of 1 and 3: %d"), AveInt);

	float AveFloat = Avg<float>(3.45f, 7.14f);
	UE_LOG(LogTemp, Warning, TEXT("Average of 3.45 and 7.14: %f"), AveFloat);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
}

float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);;
}

float AItem::transformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);;;
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FString OtherActorName = OtherActor->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Red, OtherActorName);
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

}

