// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Slash\DebugMacros.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Amplitude = 0.25f;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	int32 AveInt = Avg<int32>(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("Average of 1 and 3: %d"), AveInt);

	float AveFloat = Avg<float>(3.45f, 7.14f);
	UE_LOG(LogTemp, Warning, TEXT("Average of 3.45 and 7.14: %f"), AveFloat);
}

float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);;
}

float AItem::transformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);;;
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	//float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

	//AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));

	DRAW_SPHERE_SingleFrame(GetActorLocation());
	DRAW_VECTOR_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100);

	FVector AvgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
	DRAW_POINT_SingleFrame(AvgVector);

	FRotator AvgRotator = Avg<FRotator>(GetActorRotation(), FRotator::ZeroRotator);
}

