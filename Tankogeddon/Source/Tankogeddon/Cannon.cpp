// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"



// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	USceneComponent * sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);


}

void ACannon::Fire()
{
	if(ProjectileCount==0) GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Out of Ammo");
	if(!ReadyToFire)
	{
		return;	
	}
	ReadyToFire = false;
		
	if(Type == ECannonType::FireProjectile && ProjectileCount!=0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire - projectile");
		ProjectileCount--;
		UE_LOG(LogTemp, Warning, TEXT("ProjectileCount= %f "), ProjectileCount);
	}	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);

}

void ACannon::FireSpecial()
{
	if(ProjectileCount==0) GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Out of Ammo");
	if(!ReadyToFire)
	{
		return;	
	}
	ReadyToFire = false;
	if(Type == ECannonType::FireProjectile && ProjectileCount!=0)
	{				
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::TripleShot, 1 / FireRate/3, true,0);
		ProjectileCount--;
		UE_LOG(LogTemp, Warning, TEXT("ProjectileCount= %f "), ProjectileCount);
	}	
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;

}

void ACannon::TripleShot()
{	
	GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire - special");
	UE_LOG(LogTemp, Warning, TEXT("Count = %f "), MultiShot);
	MultiShot--;
	if(MultiShot==0)
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
		MultiShot=3;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);	
	}
	
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();

}

void ACannon::Reload()
{
	ReadyToFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

