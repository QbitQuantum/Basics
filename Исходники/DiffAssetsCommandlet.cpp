bool UDiffAssetsCommandlet::ExportFile(const FString& Filename, const TArray<UObject *>& LoadedObjects)
{
	FString Extension = TEXT("t3d");
	FStringOutputDevice Buffer;
	const FExportObjectInnerContext Context;
	for (int32 Index = 0; Index < LoadedObjects.Num(); Index++)
	{
		UExporter* Exporter = UExporter::FindExporter( LoadedObjects[Index], *Extension );
		if (!Exporter)
		{
			UE_LOG(LogDiffAssetsCommandlet, Warning, TEXT("Could not find exporter."));
			return false;
		}
		UExporter::ExportToOutputDevice( &Context, LoadedObjects[Index], Exporter, Buffer, *Extension, 0, PPF_ExportsNotFullyQualified, false );
		TMap<FString,FString> NativePropertyValues;
		if ( LoadedObjects[Index]->GetNativePropertyValues(NativePropertyValues) && NativePropertyValues.Num())
		{
			int32 LargestKey = 0;
			for ( TMap<FString,FString>::TIterator It(NativePropertyValues); It; ++It )
			{
				LargestKey = FMath::Max(LargestKey, It.Key().Len());
			}
			for ( TMap<FString,FString>::TIterator It(NativePropertyValues); It; ++It )
			{
				Buffer.Logf(TEXT("  %s=%s"), *It.Key().RightPad(LargestKey), *It.Value());
			}
		}
	}
	if (!Buffer.Len())
	{
		UE_LOG(LogDiffAssetsCommandlet, Warning, TEXT("No text was exported!"));
		return false;
	}
	if( !FFileHelper::SaveStringToFile( Buffer, *Filename ) )
	{
		UE_LOG(LogDiffAssetsCommandlet, Warning, TEXT("Could not write %s"), *Filename);
		return false;
	}
	return true;
}