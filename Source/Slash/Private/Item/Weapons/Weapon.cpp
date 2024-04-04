// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/Weapon.h"
#include "Characters\SlashCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components\SphereComponent.h"
#include "Components\BoxComponent.h"



AWeapon::AWeapon()
{
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(FName("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());

}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	AttachMeshToSocket(InParent, InSocketName);
	ItemState = EItemState::EIS_Equipped;
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRule(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRule, InSocketName);
	if (EquipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, EquipSound, GetActorLocation()
		);
	}
	if (Sphere)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
