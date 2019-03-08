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

	BindPhysics();
	BindInput();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	if (!physicsHandle) { return; }
	if (physicsHandle->GrabbedComponent)
	{
		physicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	///Try & Reach actors with physics body collision channel set
	FHitResult hitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* grabbedComponent = hitResult.GetComponent();
	AActor* ActorHit = hitResult.GetActor();

	///if we hit something, then attach a physics handle
	if (ActorHit)
	{
		physicsHandle->GrabComponent(grabbedComponent, NAME_None, grabbedComponent->GetOwner()->GetActorLocation(), true);
	}
	
}

void UGrabber::Release()
{
	physicsHandle->ReleaseComponent();
	
}

///Bind Buttons to Functions
void UGrabber::BindInput()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::BindPhysics()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physicsHandle) { 
		UE_LOG(LogTemp, Error, TEXT("NO PHYSICS HANDLE SET")); 
	}
}


///Setup raycast stuff
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	
	FCollisionQueryParams raytraceParams(FName(TEXT("")), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, GetReachLineStart(), GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		raytraceParams
	);

	return hit;
}
///used to find origin of player view point
FVector UGrabber::GetReachLineStart()
{
	FVector viewPosition;
	FRotator viewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPosition, OUT viewRotation);

	return viewPosition;
}
///used to find point at end of player reach
FVector UGrabber::GetReachLineEnd()
{
	FVector viewPosition;
	FRotator viewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPosition, OUT viewRotation);

	return viewPosition + viewRotation.Vector() * Reach;
}

