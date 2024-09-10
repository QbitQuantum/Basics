RArray<TFileName> ListImages::searchJPGL(TFileName tot, RFs fs,
        TFileName current)
{
    RArray<TFileName> result;
    TInt i;
    TBuf<50> totalPath;
    TBuf<30> fileName;
    CDir* dirList;

    totalPath = tot;
    CleanupStack::PushL(dirList);
    if ((current.Length()) > 0)
        totalPath.Append(current);
    //CleanupClosePushL(result);
    TRAPD(err,fs.GetDir(totalPath, KEntryAttMaskSupported,
                        ESortByDate, dirList));
    CleanupStack::Pop(1);
    if (!dirList)
        return result;

    for (i = 0; i < dirList->Count(); i++)
    {
        if ((*dirList)[i].IsDir())
        {
            TFileName tmp;
            tmp.Append((*dirList)[i].iName);
            tmp.Append(_L("\\"));
            RArray<TFileName> res = searchJPGL(totalPath, fs, tmp);
            for (int j = 0; j < res.Count(); j++)
                result.Append(res[j]);
            res.Reset();

        }
        else
        {
            fileName = (*dirList)[i].iName;
            if (fileName.Find(_L(".jpg")) != KErrNotFound)
            {
                TBuf<50> tmp;
                tmp = totalPath;
                tmp.Append(fileName);
                result.Append(tmp);
                tmp.Delete(0, tmp.Length() - 1);
            }
        }
    }
    delete dirList;
    return result;
}