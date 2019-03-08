// Copyright Your Mom

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_UDEMY02_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	float LastDoorOpenTime;
private:

	AActor* Owner = nullptr;
	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(VisibleAnywhere) float OpenAngle = 90.f;
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere) float DoorCloseDelay = 1.f;	
	UPROPERTY(EditAnywhere) float triggerMass = 50.f;
};
