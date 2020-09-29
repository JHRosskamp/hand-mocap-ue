// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OptiTracking.h"
#include "Classes/Components/PoseableMeshComponent.h"
#include "TrackingActor.generated.h"

USTRUCT(BlueprintType)
struct FMarkerLabel {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector Marker;
	UPROPERTY(BlueprintReadWrite)
	bool label;
};

UCLASS()
class OPTITRACKING_API ATrackingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	iue_interface* instance;

	UFUNCTION(BlueprintCallable)
		TArray<FMarkerLabel> GetMarkerLabel();

	UFUNCTION(BlueprintCallable)
		void InitTracking();

	UFUNCTION(BlueprintCallable)
		void ReadFile();

	UFUNCTION(BlueprintCallable)
		void DoLabeling();

};
