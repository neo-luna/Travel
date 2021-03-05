// Travel v.0.0


#include "StarSpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Star.h"

// Sets default values
AStarSpawnVolume::AStarSpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;
}

// Called when the game starts or when spawned
void AStarSpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnStars();
}

// Called every frame
void AStarSpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AStarSpawnVolume::RandomPointInVolume()
{
	FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
	FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void AStarSpawnVolume::SpawnStars()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	FVector Spawnlocaion = RandomPointInVolume();

	Star = GetWorld()->SpawnActor<AStar>(BP_Star, Spawnlocaion, RootComponent->GetComponentRotation(), SpawnParams);

}