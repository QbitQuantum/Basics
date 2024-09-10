bool ADEPRECATED_VolumeAdaptiveBuilder::GrowNAVVolumeByIndex(UDoNNavigationVolumeComponent* volume, int32 XGrowth, int32 YGrowth, int32 ZGrowth)
{	
	bool infantVolume = XGrowth == 1 && ZGrowth == 1 && YGrowth == 1;

	float xBoxExtent = (XGrowth * XBaseUnit + (XGrowth - 1)*OffsetThickness) / 2;
	float yBoxExtent = (YGrowth * YBaseUnit + (YGrowth - 1)*OffsetThickness) / 2;
	float zBoxExtent = (ZGrowth * ZBaseUnit + (ZGrowth - 1)*OffsetThickness) / 2;

	float x = xBoxExtent + (XBaseUnit + OffsetThickness) * volume->X + GetActorLocation().X;
	float y = yBoxExtent + (YBaseUnit + OffsetThickness) * volume->Y + GetActorLocation().Y;	
	float z = zBoxExtent + (ZBaseUnit + OffsetThickness) * (volume->Z + 1 - ZGrowth) + GetActorLocation().Z;
	
	FVector originalWorldLocation = volume->GetComponentLocation();
	FVector originalBoxExtent = volume->GetUnscaledBoxExtent();		
	volume->SetWorldLocation(FVector(x, y, z));
	volume->SetBoxExtent(FVector(xBoxExtent, yBoxExtent, zBoxExtent));

	TArray<UPrimitiveComponent*> obstacles;	
	UKismetSystemLibrary::ComponentOverlapComponents_NEW(volume, volume->GetComponentTransform(), ObstacleList, NULL, ActorsToIgnoreForCollision, obstacles);

	if (obstacles.Num() > 0)
	{
		if (infantVolume)
		{
			/*volume->CanNavigate = false;volume->ShapeColor = FColor::Red;*/
			NAVVolumeComponents.Remove(volume);
			volume->DestroyComponent();

			return false;
		}
		else
		{
			volume->SetWorldLocation(originalWorldLocation);
			volume->SetBoxExtent(originalBoxExtent);
		}

		return false;
	}
	else
	{
		TArray<UPrimitiveComponent*> neighboringVolumeComponents;		
		UKismetSystemLibrary::ComponentOverlapComponents_NEW(volume, volume->GetComponentTransform(), NAVOverlapQuery, UDoNNavigationVolumeComponent::StaticClass(), ActorsToIgnoreForCollision, neighboringVolumeComponents);
		neighboringVolumeComponents.Remove(volume);		

		if (neighboringVolumeComponents.Num() > 0)
		{
			if (infantVolume)
			{
				// Seed has landed on existing volume, destroy it immediately
				NAVVolumeComponents.Remove(volume);
				volume->DestroyComponent();

				return false;
			}
			else
			{
				volume->SetWorldLocation(originalWorldLocation);
				volume->SetBoxExtent(originalBoxExtent);
			}

			return false;
		}
		else
		{
			volume->UpdateBounds();
			return true;
		}
			
	}
	
}