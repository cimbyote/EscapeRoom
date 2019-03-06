// Copyright Your Mom

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_UDEMY02_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Ray-cast and grab what's in reach
	void Grab();
	void Release();

private:
	//how far the player can reach
	float Reach = 100.f;
	
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* input = nullptr;

	void BindInput();
	void BindPhysics();

	const FHitResult GetFirstPhysicsBodyInReach();
	FVector GetReachLineEnd();
	FVector GetReachLineStart();
};
