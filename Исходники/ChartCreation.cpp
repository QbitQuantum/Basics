/**
 * Dumps the FPS chart information to the special stats log file.
 */
void UEngine::DumpFPSChartToStatsLog( float TotalTime, float DeltaTime, int32 NumFrames, const FString& InMapName )
{
#if ALLOW_DEBUG_FILES
	const FString OutputDir = CreateOutputDirectory();
	
	// Create archive for log data.
	const FString ChartType = GetFPSChartType();
	const FString ChartName = OutputDir / CreateFileNameForChart( ChartType, InMapName, TEXT( ".log" ) );
	FArchive* OutputFile = IFileManager::Get().CreateDebugFileWriter( *ChartName, FILEWRITE_Append );

	if( OutputFile )
	{
		OutputFile->Logf(TEXT("Dumping FPS chart at %s using build %s built from changelist %i"), *FDateTime::Now().ToString(), *GEngineVersion.ToString(), GetChangeListNumberForPerfTesting() );

		// Get OS info
		FString OSMajor;
		FString OSMinor;
		FPlatformMisc::GetOSVersions(OSMajor, OSMinor);

		// Get settings info
		const Scalability::FQualityLevels& Quality = GEngine->GetGameUserSettings()->ScalabilityQuality;

		OutputFile->Logf(TEXT("Machine info:"));
		OutputFile->Logf(TEXT("\tOS: %s %s"), *OSMajor, *OSMinor);
		OutputFile->Logf(TEXT("\tCPU: %s %s"), *FPlatformMisc::GetCPUVendor(), *FPlatformMisc::GetCPUBrand());
		OutputFile->Logf(TEXT("\tGPU: %s"), *FPlatformMisc::GetPrimaryGPUBrand());
		OutputFile->Logf(TEXT("\tResolution Quality: %d"), Quality.ResolutionQuality);
		OutputFile->Logf(TEXT("\tView Distance Quality: %d"), Quality.ViewDistanceQuality);
		OutputFile->Logf(TEXT("\tAnti-Aliasing Quality: %d"), Quality.AntiAliasingQuality);
		OutputFile->Logf(TEXT("\tShadow Quality: %d"), Quality.ShadowQuality);
		OutputFile->Logf(TEXT("\tPost-Process Quality: %d"), Quality.PostProcessQuality);
		OutputFile->Logf(TEXT("\tTexture Quality: %d"), Quality.TextureQuality);
		OutputFile->Logf(TEXT("\tEffects Quality: %d"), Quality.EffectsQuality);

		int32 NumFramesBelow30 = 0; // keep track of the number of frames below 30 FPS
		float PctTimeAbove30 = 0;	// Keep track of percentage of time at 30+ FPS.
		int32 NumFramesBelow60 = 0; // keep track of the number of frames below 60 FPS
		float PctTimeAbove60 = 0;	// Keep track of percentage of time at 60+ FPS.

		// Iterate over all buckets, dumping percentages.
		for( int32 BucketIndex=0; BucketIndex<ARRAY_COUNT(GFPSChart); BucketIndex++ )
		{
			// Figure out bucket time and frame percentage.
			const float BucketTimePercentage  = 100.f * GFPSChart[BucketIndex].CummulativeTime / TotalTime;
			const float BucketFramePercentage = 100.f * GFPSChart[BucketIndex].Count / NumFrames;

			int32 StartFPS = 0;
			int32 EndFPS = 0;
			CalcQuantisedFPSRange(BucketIndex, StartFPS, EndFPS);

			// Keep track of time spent at 30+ FPS.
			if (StartFPS >= 30)
			{
				PctTimeAbove30 += BucketTimePercentage;
			}
			else
			{
				NumFramesBelow30 += GFPSChart[BucketIndex].Count;
			}
			
			// Keep track of time spent at 60+ FPS.
			if (StartFPS >= 60)
			{
				PctTimeAbove60 += BucketTimePercentage;
			}
			else
			{
				NumFramesBelow60 += GFPSChart[BucketIndex].Count;
			}

			// Log bucket index, time and frame Percentage.
			OutputFile->Logf(TEXT("Bucket: %2i - %2i  Time: %5.2f  Frame: %5.2f"), StartFPS, EndFPS, BucketTimePercentage, BucketFramePercentage);
		}

		OutputFile->Logf(TEXT("%i frames collected over %4.2f seconds, disregarding %4.2f seconds for a %4.2f FPS average, %4.2f percent of time spent > 30 FPS, %4.2f percent of time spent > 60 FPS"), 
			NumFrames, 
			DeltaTime, 
			FMath::Max<float>( 0, DeltaTime - TotalTime ), 
			NumFrames / TotalTime,
			PctTimeAbove30, PctTimeAbove60 );
		OutputFile->Logf(TEXT("Average GPU frame time: %4.2f ms"), float((GTotalGPUTime / NumFrames)*1000.0));
		OutputFile->Logf(TEXT("BoundGameThreadPct: %4.2f  BoundRenderThreadPct: %4.2f  BoundGPUPct: %4.2f PercentFrames30+: %f   PercentFrames60+: %f   BoundGameTime: %f  BoundRenderTime: %f  BoundGPUTime: %f  PctTimeAbove30: %f  PctTimeAbove60: %f ")
			, (float(GNumFramesBound_GameThread)/float(NumFrames))*100.0f
			, (float(GNumFramesBound_RenderThread)/float(NumFrames))*100.0f
			, (float(GNumFramesBound_GPU)/float(NumFrames))*100.0f
			, float(NumFrames - NumFramesBelow30) / float(NumFrames)*100.0f
			, float(NumFrames - NumFramesBelow60) / float(NumFrames)*100.0f
			, (GTotalFramesBoundTime_GameThread / DeltaTime)*100.0f
			, ((GTotalFramesBoundTime_RenderThread)/DeltaTime)*100.0f
			, ((GTotalFramesBoundTime_GPU)/DeltaTime)*100.0f
			, PctTimeAbove30
			, PctTimeAbove60
			);

		// Dump hitch data
		{
			OutputFile->Logf( TEXT( "Hitch chart:" ) );

			int32 TotalHitchCount = 0;
			int32 TotalGameThreadBoundHitches = 0;
			int32 TotalRenderThreadBoundHitches = 0;
			int32 TotalGPUBoundHitches = 0;
			for( int32 BucketIndex = 0; BucketIndex < ARRAY_COUNT( GHitchChart ); ++BucketIndex )
			{
				const float HitchThresholdInSeconds = ( float )GHitchThresholds[ BucketIndex ] * 0.001f;

				FString RangeName;
				if( BucketIndex == 0 )
				{
					// First bucket's end threshold is infinitely large
					RangeName = FString::Printf( TEXT( "%0.2fs - inf" ), HitchThresholdInSeconds );
				}
				else
				{
					const float PrevHitchThresholdInSeconds = ( float )GHitchThresholds[ BucketIndex - 1 ] * 0.001f;

					// Set range from current bucket threshold to the last bucket's threshold
					RangeName = FString::Printf( TEXT( "%0.2fs - %0.2fs" ), HitchThresholdInSeconds, PrevHitchThresholdInSeconds );
				}

				OutputFile->Logf( TEXT( "Bucket: %s  Count: %i " ), *RangeName, GHitchChart[ BucketIndex ].HitchCount );


				// Count up the total number of hitches
				TotalHitchCount += GHitchChart[ BucketIndex ].HitchCount;
				TotalGameThreadBoundHitches += GHitchChart[ BucketIndex ].GameThreadBoundHitchCount;
				TotalRenderThreadBoundHitches += GHitchChart[ BucketIndex ].RenderThreadBoundHitchCount;
				TotalGPUBoundHitches += GHitchChart[ BucketIndex ].GPUBoundHitchCount;
			}

			const int32 HitchBucketCount = STAT_FPSChart_LastHitchBucketStat - STAT_FPSChart_FirstHitchStat;
			OutputFile->Logf( TEXT( "Total hitch count (at least %ims):  %i" ), GHitchThresholds[ HitchBucketCount - 1 ], TotalHitchCount );
			OutputFile->Logf( TEXT( "Hitch frames bound by game thread:  %i  (%0.1f%%)" ), TotalGameThreadBoundHitches, TotalHitchCount > 0 ? ( ( float )TotalGameThreadBoundHitches / ( float )TotalHitchCount * 100.0f ) : 0.0f );
			OutputFile->Logf( TEXT( "Hitch frames bound by render thread:  %i  (%0.1f%%)" ), TotalRenderThreadBoundHitches, TotalHitchCount > 0 ? ( ( float )TotalRenderThreadBoundHitches / ( float )TotalHitchCount * 0.0f ) : 0.0f  );
			OutputFile->Logf( TEXT( "Hitch frames bound by GPU:  %i  (%0.1f%%)" ), TotalGPUBoundHitches, TotalHitchCount > 0 ? ( ( float )TotalGPUBoundHitches / ( float )TotalHitchCount * 100.0f ) : 0.0f );
		}

		OutputFile->Logf( LINE_TERMINATOR LINE_TERMINATOR LINE_TERMINATOR );

		// Flush, close and delete.
		delete OutputFile;

		const FString AbsolutePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead( *ChartName );

		UE_LOG( LogProfilingDebugging, Warning, TEXT( "FPS Chart (logfile) saved to %s" ), *AbsolutePath );

#if	PLATFORM_DESKTOP
		FPlatformProcess::ExploreFolder( *AbsolutePath );
#endif // PLATFORM_DESKTOP
	}
#endif // ALLOW_DEBUG_FILES
}