BOOL PyWinObject_AsKNOWNFOLDER_DEFINITION(PyObject *obdef, KNOWNFOLDER_DEFINITION& def)
{
	static char *keywords[] = {"Category", "Name", "Description", "Parent",
		"RelativePath", "ParsingName", "Tooltip", "LocalizedName", "Icon",
		"Security", "Attributes", "Flags", "Type", NULL};
	ZeroMemory(&def, sizeof(def));
	if (!PyDict_Check(obdef)){
		PyErr_SetString(PyExc_TypeError, "KNOWNFOLDER_DEFINITION requires a dict");
		return FALSE;
		}
	TmpPyObject obdummy = PyTuple_New(0);
	if (obdummy == NULL)
		return FALSE;
	PyObject *obName, *obDescription, *obRelativePath,
		*obParsingName, *obTooltip, *obLocalizedName, *obIcon, *obSecurity;
	if (!PyArg_ParseTupleAndKeywords(obdummy, obdef, "iOOO&OOOOOOkiO&", keywords,
		&def.category,
		&obName,
		&obDescription,
		PyWinObject_AsIID, &def.fidParent,
		&obRelativePath, &obParsingName, &obTooltip,
		&obLocalizedName, &obIcon, &obSecurity,
		&def.dwAttributes, &def.kfdFlags,
		PyWinObject_AsIID, &def.ftidType))
		return FALSE;
	BOOL ret = PyWinObject_AsTaskAllocatedWCHAR(obName, &def.pszName, FALSE)
			&& PyWinObject_AsTaskAllocatedWCHAR(obDescription, &def.pszDescription, FALSE)
			&& PyWinObject_AsTaskAllocatedWCHAR(obRelativePath, &def.pszRelativePath, TRUE)
			&& PyWinObject_AsTaskAllocatedWCHAR(obParsingName, &def.pszParsingName, TRUE)
			&& PyWinObject_AsTaskAllocatedWCHAR(obTooltip, &def.pszTooltip, TRUE)
			&& PyWinObject_AsTaskAllocatedWCHAR(obLocalizedName, &def.pszLocalizedName, TRUE)
			&& PyWinObject_AsTaskAllocatedWCHAR(obIcon, &def.pszIcon, TRUE)
			&& PyWinObject_AsTaskAllocatedWCHAR(obSecurity, &def.pszSecurity, TRUE);
	if (!ret)
		FreeKnownFolderDefinitionFields(&def);
	return ret;
}