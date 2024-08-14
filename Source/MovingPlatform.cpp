


#include "MovingPlatform.h"
#include "math.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();

	/*FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("Begin play: %s"), *Name);*/
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime){ //class adını koymayı unutma!
	
	if(ShouldPlatformReturn()){
		//To prevent an overshot we update StartingLocation this way (using GetSafeNormal())
		FVector MoveDirection = PlatformVelocity.GetSafeNormal(); //PlatformVelocity vektörünün aynı yönde ama uzuluğu 1 olan hali
		StartingLocation = StartingLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartingLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else{
		FVector currentLocation = GetActorLocation();
		currentLocation += PlatformVelocity*DeltaTime;
		SetActorLocation(currentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime){
	AddActorLocalRotation(RotationVelocity * DeltaTime);

}

bool AMovingPlatform::ShouldPlatformReturn() const{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const{
	return FVector::Dist(StartingLocation, GetActorLocation());
}
