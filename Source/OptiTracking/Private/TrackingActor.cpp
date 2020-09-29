// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackingActor.h"

// Sets default values
ATrackingActor::ATrackingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrackingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrackingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrackingActor::InitTracking() {
	if (instance == nullptr)
		instance = IOptiTracking::Get().GetTestClass();
	auto status = instance->init();
	UE_LOG(LogTemp, Warning, TEXT("Init status = %d"), status);
}

void ATrackingActor::ReadFile() {
	instance->readFile();
	UE_LOG(LogTemp, Warning, TEXT("Files read!"));
}

void ATrackingActor::DoLabeling() {
	instance->labelMarkers();
	UE_LOG(LogTemp, Warning, TEXT("Labeling done!"));
}

TArray<FMarkerLabel> ATrackingActor::GetMarkerLabel() {
	TArray<FMarkerLabel> data;
	int noMarker = 19;
	float* marker = new float[3 * noMarker];
	bool* label = new bool[noMarker];
	instance->getNextMarkerDataLabels(marker, label, noMarker);
	for (int i = 0; i < noMarker; ++i) {
		FMarkerLabel tmp;
		tmp.label = label[i];
		tmp.Marker = FVector(marker[3 * i], marker[3 * i + 1], marker[3 * i + 2]);
		data.Add(tmp);
	}
	return data;
}
