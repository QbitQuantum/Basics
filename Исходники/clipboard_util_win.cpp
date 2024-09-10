    bool ClipboardUtil::GetUrl(IDataObject* data_object, std::wstring* url,
        std::wstring* title, bool convert_filenames)
    {
        DCHECK(data_object && url && title);
        if(!HasUrl(data_object))
        {
            return false;
        }

        // 尝试从|data_object|的多种格式中提取URL.
        STGMEDIUM store;
        if(GetUrlFromHDrop(data_object, url, title))
        {
            return true;
        }

        if(SUCCEEDED(data_object->GetData(GetMozUrlFormat(), &store)) ||
            SUCCEEDED(data_object->GetData(GetUrlWFormat(), &store)))
        {
            {
                // Mozilla URL格式或者unicode URL.
                base::win::ScopedHGlobal<wchar_t> data(store.hGlobal);
                SplitUrlAndTitle(data.get(), url, title);
            }
            ReleaseStgMedium(&store);
            return true;
        }

        if(SUCCEEDED(data_object->GetData(GetUrlFormat(), &store)))
        {
            {
                // URL使用ascii.
                base::win::ScopedHGlobal<char> data(store.hGlobal);
                SplitUrlAndTitle(UTF8ToWide(data.get()), url, title);
            }
            ReleaseStgMedium(&store);
            return true;
        }

        if(convert_filenames)
        {
            return GetFileUrl(data_object, url, title);
        }
        else
        {
            return false;
        }
    }