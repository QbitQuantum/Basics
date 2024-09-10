JBoolean
CBNewProjectSaveFileDialog::OKToDeactivate()
{
	if (!JXSaveFileDialog::OKToDeactivate())
		{
		return kJFalse;
		}
	else if (Cancelled())
		{
		return kJTrue;
		}

	const CBBuildManager::MakefileMethod method = GetMakefileMethod();
	if (method == CBBuildManager::kManual)
		{
		return kJTrue;
		}

	// ask if OK to replace Make.files

	if (method == CBBuildManager::kMakemake)
		{
		const JString makeFilesName = CBBuildManager::GetMakeFilesName(GetPath());
		if (JFileExists(makeFilesName) &&
			!OKToReplaceFile(makeFilesName, JGetString("CBName")))
			{
			return kJFalse;
			}
		}

	// ask if OK to replace CMakeLists.txt

	if (method == CBBuildManager::kCMake)
		{
		JString projFileName, projRoot, projSuffix;
		GetFileName(&projFileName);
		JSplitRootAndSuffix(projFileName, &projRoot, &projSuffix);

		const JString cmakeInputName = CBBuildManager::GetCMakeInputName(GetPath(), projRoot);
		if (JFileExists(cmakeInputName) &&
			!OKToReplaceFile(cmakeInputName, JGetString("CBName")))
			{
			return kJFalse;
			}
		}

	// ask if OK to replace .pro

	if (method == CBBuildManager::kQMake)
		{
		JString projFileName, projRoot, projSuffix;
		GetFileName(&projFileName);
		JSplitRootAndSuffix(projFileName, &projRoot, &projSuffix);

		const JString qmakeInputName = CBBuildManager::GetQMakeInputName(GetPath(), projRoot);
		if (JFileExists(qmakeInputName) &&
			!OKToReplaceFile(qmakeInputName, JGetString("CBName")))
			{
			return kJFalse;
			}
		}

	// ask if OK to replace existing Makefile

	JPtrArray<JString> makefileList(JPtrArrayT::kDeleteAll);
	CBBuildManager::GetMakefileNames(GetPath(), &makefileList);

	const JSize count = makefileList.GetElementCount();
	for (JIndex i=1; i<=count; i++)
		{
		const JString* fullName = makefileList.NthElement(i);
		if (JFileExists(*fullName) &&
			!OKToReplaceFile(*fullName, CBBuildManager::GetMakefileMethodName(GetMakefileMethod())))
			{
			return kJFalse;
			}
		}

	return kJTrue;
}