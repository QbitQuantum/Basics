bool FBuildPatchVerificationImpl::VerifyAgainstDirectory(TArray<FString>& OutDatedFiles, double& TimeSpentPaused)
{
	bool bAllCorrect = true;
	OutDatedFiles.Empty();
	TimeSpentPaused = 0;

	// Setup progress tracking
	double TotalBuildSizeDouble = Manifest->GetBuildSize();
	double ProcessedBytes = 0;
	CurrentBuildPercentage = 0;

	// For all files in the manifest, check that they produce the correct SHA1 hash, adding any that don't to the list
	TArray<FString> BuildFiles;
	Manifest->GetFileList(BuildFiles);
	for (const FString& BuildFile : BuildFiles)
	{
		// Get file details
		int64 BuildFileSize = Manifest->GetFileSize(BuildFile);
		FSHAHashData BuildFileHash;
		bool bFoundHash = Manifest->GetFileHash(BuildFile, BuildFileHash);
		check(bFoundHash);

		// Chose the file to check
		FString FullFilename = SelectFullFilePath(BuildFile);

		// Verify the file
		CurrentFileWeight = BuildFileSize / TotalBuildSizeDouble;
		if (FBuildPatchUtils::VerifyFile(FullFilename, BuildFileHash, BuildFileHash, FBuildPatchFloatDelegate::CreateRaw(this, &FBuildPatchVerificationImpl::PerFileProgress), ShouldPauseDelegate, TimeSpentPaused) == 0)
		{
			bAllCorrect = false;
			OutDatedFiles.Add(BuildFile);
		}
		ProcessedBytes += BuildFileSize;
		CurrentBuildPercentage = ProcessedBytes / TotalBuildSizeDouble;
	}

	return bAllCorrect && !FBuildPatchInstallError::HasFatalError();
}