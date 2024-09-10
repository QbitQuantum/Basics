void restoreDirectory (GmZipFileReader * pSetReader
							, const wxString & szDestPath
							, GmWriter * pWriter
							, GmRestOp option
							, GmExecUnitBase * pExecUnit
							, GmTempEvent * pEvent
							, GmUifSourceEntry * pEntry
							, GmDirectoryNode<GmLeafNode> * pDirectory
							, ubyte4 uiTotalSets
							, const wxString & prefixPath)
{
	if ((option & GRP_NEW_PLACE) == GRP_NEW_PLACE) {
		assert (pWriter);
		wxString path = getSourcePath (pWriter, pEntry, szDestPath);
		pWriter->SetDestPath (path);

		pSetReader->restoreFile (pWriter, pDirectory, prefixPath, uiTotalSets, pEvent);
	}
	else {  // !GRP_NEW_PLACE
		assert (pWriter == 0);
		GmWriter * pWriter2 = createWriter (pSetReader, pEntry, option, pExecUnit, 0);

		if (pWriter2 == 0) {
			wxString msg;
			throw GmException (msg);
		}

		pSetReader->restoreFile (pWriter2, pDirectory, prefixPath, uiTotalSets, 0);
		delete pWriter2;
	}

	return;
}