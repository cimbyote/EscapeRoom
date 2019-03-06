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
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab"));

	///Try & Reach actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	///if we hit something, then attach a physics handle
	//TODO: Attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release"));

	//TODO: Detach physics handle
}

///Bind Buttons to Functions
void UGrabber::BindInput()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

///Bind Physics
void UGrabber::BindPhysics()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector viewPosition;
	FRotator viewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPosition, OUT viewRotation);

	FVector LineTraceEnd = viewPosition + viewRotation.Vector() * Reach;

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

	return FHitResult();
}
