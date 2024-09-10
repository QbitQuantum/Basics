    ZString FormatKey(const ZString& strSource)
    {
        ZString strResult = strSource.ToUpper(); 

        // remove all spaces
        strResult.RemoveAll(' ');

        return strResult;
    }