void renameDfuTempToFinal(const RemoteFilename & realname)
{
    RemoteFilename tempFilename;
    StringBuffer newTailname;
    getDfuTempName(tempFilename, realname);
    realname.getTail(newTailname);

    OwnedIFile output = createIFile(tempFilename);
    try
    {
        output->rename(newTailname);
    }
    catch (IException * e)
    {
        EXCLOG(e, "Failed to rename target file");
        StringBuffer oldName;
        realname.getPath(oldName);
        LOG(MCdebugInfoDetail, unknownJob, "Error: Rename %s->%s failed - tring to delete target and rename again", oldName.str(), newTailname.str());
        e->Release();
        OwnedIFile old = createIFile(realname);
        old->remove();
        output->rename(newTailname);
    }
}