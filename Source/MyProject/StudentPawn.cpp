// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPawn.h"

// Sets default values
AStudentPawn::AStudentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Dodajemy domyœlne wartoœci
	TestProgress = 0.0f;
	WritingSpeed = 5.0f; // Piszesz 5% testu w sekundê
	bIsWriting = false;

	PhoneBattery = 100.0f;     // Startujemy ze 100% baterii
	bIsLookingAtPhone = false; // Na starcie nie patrzymy w telefon

}

// Called when the game starts or when spawned
void AStudentPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStudentPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Jeœli gracz trzyma przycisk, zwiêkszaj postêp testu
	if (bIsWriting)
	{
		TestProgress += WritingSpeed * DeltaTime;

		// Blokujemy postêp na maksymalnie 100%
		if (TestProgress > 100.0f)
		{
			TestProgress = 100.0f;
		}
	}

	// Zu¿ycie baterii, gdy telefon jest w³¹czony
	if (bIsLookingAtPhone)
	{
		// Bateria spada np. o 2% na sekundê
		PhoneBattery -= 2.0f * DeltaTime;

		// Blokada, ¿eby nie spad³a poni¿ej zera
		if (PhoneBattery <= 0.0f)
		{
			PhoneBattery = 0.0f;
			bIsLookingAtPhone = false; // Telefon siê roz³adowuje i wy³¹cza
		}
	}

}

// Called to bind functionality to input
void AStudentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AStudentPawn::StartWriting()
{
	// Mo¿emy pisaæ TYLKO, gdy nie patrzymy w telefon
	if (!bIsLookingAtPhone)
	{
		bIsWriting = true;
	}
}

void AStudentPawn::StopWriting()
{
	bIsWriting = false;
}

void AStudentPawn::TogglePhone()
{
	// Jeœli bateria jest roz³adowana, nie mo¿emy u¿yæ telefonu
	if (PhoneBattery <= 0.0f)
	{
		bIsLookingAtPhone = false;
		return;
	}

	// Zamieniamy stan na przeciwny (jeœli by³ schowany, to wyci¹gamy i na odwrót)
	bIsLookingAtPhone = !bIsLookingAtPhone;

	// Jeœli gracz wyci¹gn¹³ telefon, musi automatycznie przestaæ pisaæ test!
	if (bIsLookingAtPhone)
	{
		StopWriting();
	}
}