void CDiskWriteSlaveActivityBase::removeFiles()
{
    if (!fName.length())
        return;
    Owned<IFile> primary = createIFile(fName);
    try { primary->remove(); }
    catch (IException *e) { ActPrintLogEx(&queryContainer(), e, thorlog_null, MCwarning, "Failed to remove file: %s", fName.get()); }
    catch (CATCHALL) { ActPrintLogEx(&queryContainer(), thorlog_null, MCwarning, "Failed to remove: %s", fName.get()); }
}