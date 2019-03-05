// Copyright Your Mom

#include "Grabber.h"
#include "EscapeRoom_udemy02.h"
#include "DrawDebugHelpers.h"

#define OUT //use just to mark an out parameter
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//UE_LOG(LogTemp, Warning, TEXT("grabber works yo"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector viewPosition;
	FRotator viewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPosition, OUT viewRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	FVector LineTraceEnd = viewPosition + viewRotation.Vector() * Reach;

	///Draw a red trace to to visualize grabber reach
	//DrawDebugLine(GetWorld(), viewPosition, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0, 10.f);

	///Setup raycast stuff
	FCollisionQueryParams raytraceParams(FName(TEXT("")), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, viewPosition, LineTraceEnd, 
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
				raytraceParams
		);

	///Report what is hit
	AActor* ActorHit = hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitting: %s"), *(ActorHit->GetName()));
	}

}

