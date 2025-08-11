// Fill out your copyright notice in the Description page of Project Settings.


#include "LukasHelperLibrary.h"

#include "LukasHelperModuleEditor.h"
#include "DataLayer/DataLayerEditorSubsystem.h"
#include "WorldPartition/WorldPartition.h"
#include "WorldPartition/WorldPartitionActorDescInstance.h"
#include "WorldPartition/WorldPartitionHelpers.h"

void ULukasHelperLibrary::TestHelperPrint(USkeletalMesh* InSkeletalMesh)
{
	if (!IsValid(InSkeletalMesh))
	{
		return;
	}
	UE_LOG(LogLukasHelperEditor, Error, TEXT("Processing %s"), *InSkeletalMesh->GetName());
}

void ULukasHelperLibrary::GetAllActorDescriptorsInWorld(FName TargetClass, bool bAutoEnableDataLayers)
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		UE_LOG(LogLukasHelperEditor, Warning, TEXT("Could not get the editor world."));
		return;
	}
	
	UWorldPartition* WorldPartition = World->GetWorldPartition();
	if (!WorldPartition)
	{
		UE_LOG(LogLukasHelperEditor, Warning, TEXT("This is not a World Partition map."));
		return;
	}

	UE_LOG(LogLukasHelperEditor, Log, TEXT("--- Start: Iterating all actor descriptors ---"));

	TArray<FGuid> ActorsToPin;
	TArray<const FWorldPartitionActorDescInstance*> WorldPartitionActorDescInstances;
	UDataLayerEditorSubsystem* DataLayerEditorSubsystem = GEditor->GetEditorSubsystem<UDataLayerEditorSubsystem>();

	FWorldPartitionHelpers::ForEachActorDescInstance(WorldPartition, AActor::StaticClass(), [WorldPartition, bAutoEnableDataLayers, DataLayerEditorSubsystem, &ActorsToPin, &WorldPartitionActorDescInstances, &TargetClass](const FWorldPartitionActorDescInstance* ActorDescInstance)
	{
		FName CurrentActorNativeClass = ActorDescInstance->GetActorDesc()->GetNativeClass().GetAssetName();
		if (CurrentActorNativeClass == TargetClass)
		{
			FGuid Guid = ActorDescInstance->GetGuid();
			ActorsToPin.AddUnique(Guid);
			WorldPartitionActorDescInstances.AddUnique(ActorDescInstance);
			if (bAutoEnableDataLayers)
			{
				if (ActorDescInstance->GetDataLayers().Num() > 0)
				{
					for (const FName& DataLayerName : ActorDescInstance->GetDataLayerInstanceNames())
					{
						UDataLayerInstance* DataLayerInstance = DataLayerEditorSubsystem->GetDataLayerInstance(DataLayerName);
						if (IsValid(DataLayerInstance))
						{
							DataLayerInstance->SetIsLoadedInEditor(true, true);
						}
					}
				}
			}
		}
		
		return true;
	});

	WorldPartition->PinActors(ActorsToPin);
	GEditor->SelectNone(true, true);
	for (const FWorldPartitionActorDescInstance* ActorDescInstance : WorldPartitionActorDescInstances)
	{
		if (IsValid(ActorDescInstance->GetActor()))
		{
			GEditor->SelectActor(ActorDescInstance->GetActor(), true, true);
		}
	}
	

	UE_LOG(LogLukasHelperEditor, Log, TEXT("--- End: Iteration complete ---"));
}
