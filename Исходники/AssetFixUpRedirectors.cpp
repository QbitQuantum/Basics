bool FAssetFixUpRedirectors::CheckOutReferencingPackages(TArray<FRedirectorRefs>& RedirectorsToFix, TArray<UPackage*>& InOutReferencingPackagesToSave) const
{
	// Prompt to check out all successfully loaded packages
	bool bUserAcceptedCheckout = true;

	if ( InOutReferencingPackagesToSave.Num() > 0 )
	{
		if ( ISourceControlModule::Get().IsEnabled() )
		{
			TArray<UPackage*> PackagesCheckedOutOrMadeWritable;
			TArray<UPackage*> PackagesNotNeedingCheckout;
			bUserAcceptedCheckout = FEditorFileUtils::PromptToCheckoutPackages( false, InOutReferencingPackagesToSave, &PackagesCheckedOutOrMadeWritable, &PackagesNotNeedingCheckout );
			if ( bUserAcceptedCheckout )
			{
				TArray<UPackage*> PackagesThatCouldNotBeCheckedOut = InOutReferencingPackagesToSave;

				for ( auto PackageIt = PackagesCheckedOutOrMadeWritable.CreateConstIterator(); PackageIt; ++PackageIt )
				{
					PackagesThatCouldNotBeCheckedOut.Remove(*PackageIt);
				}

				for ( auto PackageIt = PackagesNotNeedingCheckout.CreateConstIterator(); PackageIt; ++PackageIt )
				{
					PackagesThatCouldNotBeCheckedOut.Remove(*PackageIt);
				}

				for ( auto PackageIt = PackagesThatCouldNotBeCheckedOut.CreateConstIterator(); PackageIt; ++PackageIt )
				{
					const FName NonCheckedOutPackageName = (*PackageIt)->GetFName();

					for ( auto RedirectorRefsIt = RedirectorsToFix.CreateIterator(); RedirectorRefsIt; ++RedirectorRefsIt )
					{
						FRedirectorRefs& RedirectorRefs = *RedirectorRefsIt;
						if ( RedirectorRefs.ReferencingPackageNames.Contains(NonCheckedOutPackageName) )
						{
							// We did not check out at least one of the packages we needed to. This redirector can not be fixed up.
							RedirectorRefs.FailureReason = FText::Format(LOCTEXT("RedirectorFixupFailed_NotCheckedOut", "Referencing package {0} was not checked out"), FText::FromName(NonCheckedOutPackageName));
							RedirectorRefs.bRedirectorValidForFixup = false;
						}
					}

					InOutReferencingPackagesToSave.Remove(*PackageIt);
				}
			}
		}
	}

	return bUserAcceptedCheckout;
}