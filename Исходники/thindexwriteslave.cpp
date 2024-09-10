 void removeFiles(IPartDescriptor &partDesc)
 {
     StringBuffer partFname;
     getPartFilename(partDesc, 0, partFname);
     Owned<IFile> primary = createIFile(partFname.str());
     try { primary->remove(); }
     catch (IException *e) { ActPrintLog(e, "Failed to remove file: %s", partFname.str()); e->Release(); }
     catch (CATCHALL) { ActPrintLog("Failed to remove: %s", partFname.str()); }
 }