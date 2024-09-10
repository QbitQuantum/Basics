HRESULT FacadeDocumentProviderImpl::GetSaveInfo(HWND hWnd, const std::wstring& formatString, long lFlags, long& lFormatIndex, WSDocNonCom& wsDoc)
{
	//-- ArtifactImpl
	//TODO: Replace Existing Version
	//TODO: Create a relation

	//-- Connector
	// Create new artifact (Add Files)
	UNREFERENCED_PARAMETER(lFormatIndex);
	if(DF_NEW_DOCUMENT & lFlags)
	{
		std::wstring newFileName = wsDoc.GetDescription();
		Artifact artifact = GetConnector().CreateArtifact(hWnd, formatString, newFileName);
		if (artifact.IsNull())
			return E_DOCUMENT_NOT_FOUND;
		PopulateWSDocMembersFromArtifact(artifact, wsDoc);
		wsDoc.SetFlags(DOCUMENT_LOCKED_BY_US);
		lFormatIndex = CalculateFormatIndex(formatString, artifact.GetFileExtension());
		artifact.Lock();
	}
	// Create a relation
	else if(DF_ATTACH & lFlags)
	{
		Artifact existing = GetArtifactByWorkshareId(wsDoc.GetDocId());	

		if (existing.IsNull())
			return E_DOCUMENT_NOT_FOUND;

		CStdString sDummyFile = CTempFileManager::GetTempFileName();;
		CStdString sExt; 
		DocUtilities::GetExtensionFromFileName(sDummyFile,sExt);

		Artifact related = existing.CreateRelatedItem(CStdStringW(sDummyFile),GetDefaultSaveExtensionFromFormatString(formatString, lFormatIndex), formatString, true);

		if (related.IsNull())
			return E_DOCUMENT_NOT_FOUND;

		related.Lock();

		PopulateWSDocMembersFromArtifact(related, wsDoc);
		lFormatIndex = CalculateFormatIndex(formatString, related.GetFileExtension());

		wsDoc.SetFlags(DOCUMENT_LOCKED_BY_US);
	}
	// Create a new version
	else if(DF_VERSION & lFlags)
	{
		std::wstring repositoryId;
		std::wstring artifactId;
		std::wstring versionLabel;
		DecodeWorkshareId(wsDoc.GetDocId().c_str(), artifactId, versionLabel, repositoryId);
		Repository repository = GetConnector().GetRepositoryById(repositoryId.c_str());
		Artifact artifact = repository.GetArtifactById(artifactId.c_str(), versionLabel.c_str());
		Artifact artifactVersion = artifact.CreateNewVersion(L"", formatString);
		PopulateWSDocMembersFromArtifact(artifactVersion, wsDoc);
		artifactVersion.Lock(); 
		wsDoc.SetFlags(DOCUMENT_LOCKED_BY_US);
		lFormatIndex = CalculateFormatIndex(formatString, artifactVersion.GetFileExtension());

	}
	return S_OK;
}