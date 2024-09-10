/*----------------------------------------------------------------------------------------------
	Insert material as appropriate to display the specified object.
	This method has not yet been tested...maybe not even compiled?
----------------------------------------------------------------------------------------------*/
STDMETHODIMP VwBaseVc::DisplayEmbeddedObject(IVwEnv * pvwenv, HVO hvo)
{
	BEGIN_COM_METHOD;
	ChkComArgPtr(pvwenv);
	// See if it is a CmPicture.
	ISilDataAccessPtr qsda;
	CheckHr(pvwenv->get_DataAccess(&qsda));
	int clsid;
	CheckHr(qsda->get_IntProp(hvo, kflidCmObject_Class, &clsid));
	if (clsid != kclidCmPicture)
		return S_OK; // don't know how to deal with it.
	StrUni stuRootDir = DirectoryFinder::FwRootDataDir();
	HVO hvoFile;
	CheckHr(qsda->get_ObjectProp(hvo, kflidCmPicture_PictureFile, &hvoFile));
	if (hvoFile == 0)
		return S_OK;
	SmartBstr sbstrFileName;
	CheckHr(qsda->get_UnicodeProp(hvoFile, kflidCmFile_InternalPath, &sbstrFileName));
	if (sbstrFileName.Length() == 0)
		return S_OK;
	StrUni stuPath;
	stuPath.Format(L"%s,%s,%s", stuRootDir.Chars(), L"\\", sbstrFileName.Chars());
	IPicturePtr qpic;
	try
	{
		IStreamPtr qstrm;
		FileStream::Create(stuPath, STGM_READ, &qstrm);
		STATSTG stg;
		CheckHr(qstrm->Stat(&stg, STATFLAG_NONAME));
		LONG cbdata = (LONG)stg.cbSize.QuadPart;
		CheckHr(::OleLoadPicture(qstrm, cbdata, FALSE, IID_IPicture, (LPVOID *)&qpic));
		CheckHr(pvwenv->AddPicture(qpic, ktagNotAnAttr, 0, 0));
	}
	catch (...)
	{
		return S_OK; // if anything goes wrong (e.g., file not found), just give up for now.
		// Todo: insert a 'file XXX not found string.
	}
	// Todo: also add the caption.

	END_COM_METHOD(g_fact, IID_IVwViewConstructor);
}