void Parse_MTP::mtp_get_metadata(PCWSTR object_id, IPortableDeviceContent *pdc, bool clear)
{
    IPortableDeviceValues *pdv;
    IPortableDeviceKeyCollection *pdkc;
    IPortableDeviceProperties *pdp = NULL;
    HRESULT hr;
    scrob_entry new_entry;
    LPWSTR album = NULL;
    LPWSTR artist = NULL;
    LPWSTR name = NULL;
    ULONG usecount;
    ULONG skipcount;
    ULONG tracknum;
    ULONGLONG duration;
    PROPVARIANT date;

    new_entry.length = 0;

    hr = CoCreateInstance(CLSID_PortableDeviceValues, NULL, CLSCTX_INPROC_SERVER,
                          IID_IPortableDeviceValues, (VOID**)&pdv);
    if (FAILED(hr))
    {
        emit add_log(LOG_ERROR, QString("mtp_get_metadata: Failed to create IPortableDeviceValues: %1")
                .arg(hr, 0, 16));
        return;
    }

    hr = CoCreateInstance(CLSID_PortableDeviceKeyCollection, NULL, CLSCTX_INPROC_SERVER,
                          IID_IPortableDeviceKeyCollection, (VOID**)&pdkc);
    if (FAILED(hr))
    {
        emit add_log(LOG_ERROR, QString("mtp_get_metadata: Failed to create IPortableDeviceKeyCollection: %1")
                .arg(hr, 0, 16));
        return;
    }

    hr = pdc->Properties(&pdp);
    if (FAILED(hr))
    {
        emit add_log(LOG_ERROR, QString("mtp_get_metadata: Failed to get properties from IPortableDeviceContent: %1")
                .arg(hr, 0, 16));
        goto mtp_get_metadata_cleanup;
    }

    hr = pdkc->Add(WPD_MEDIA_USE_COUNT);          //VT_UI4
    hr = pdkc->Add(WPD_MEDIA_SKIP_COUNT);         //VT_UI4
    hr = pdkc->Add(WPD_MEDIA_LAST_ACCESSED_TIME); //VT_DATE
    hr = pdkc->Add(WPD_MUSIC_ALBUM);              //VT_LPWSTR
    hr = pdkc->Add(WPD_MUSIC_TRACK);              //VT_UI4
    hr = pdkc->Add(WPD_MEDIA_DURATION);           //VT_UI8, in milliseconds
    hr = pdkc->Add(WPD_OBJECT_NAME);              //VT_LPWSTR
    hr = pdkc->Add(WPD_MEDIA_ARTIST);             //VT_LPWSTR
    if (FAILED(hr))
    {
        emit add_log(LOG_ERROR, QString("mtp_get_metadata: Failed to add to IPortableDeviceKeyCollection: %1")
                .arg(hr, 0, 16));
        goto mtp_get_metadata_cleanup;
    }

    hr = pdp->GetValues(object_id, pdkc, &pdv);
    if (FAILED(hr))
    {
        emit add_log(LOG_ERROR, QString("mtp_get_metadata: Failed to get values from IPortableDeviceProperties: %1")
                .arg(hr, 0, 16));
        goto mtp_get_metadata_cleanup;
    }

    hr = pdv->GetStringValue(WPD_MUSIC_ALBUM, &album);
    if (SUCCEEDED(hr))
        new_entry.album = QString::fromStdWString(album);

    hr = pdv->GetStringValue(WPD_MEDIA_ARTIST, &artist);
    if (SUCCEEDED(hr))
        new_entry.artist = QString::fromStdWString(artist);

    hr = pdv->GetStringValue(WPD_OBJECT_NAME, &name);
    if (SUCCEEDED(hr))
        new_entry.title = QString::fromStdWString(name);

    hr = pdv->GetUnsignedIntegerValue(WPD_MEDIA_USE_COUNT, &usecount);
    hr = pdv->GetUnsignedIntegerValue(WPD_MEDIA_SKIP_COUNT, &skipcount);

    hr = pdv->GetUnsignedIntegerValue(WPD_MUSIC_TRACK, &tracknum);
    if (SUCCEEDED(hr))
        new_entry.tracknum = tracknum;

    hr = pdv->GetUnsignedLargeIntegerValue(WPD_MEDIA_DURATION, &duration);
    if (SUCCEEDED(hr))
        new_entry.length = duration/1000;

    hr = pdv->GetValue(WPD_MEDIA_LAST_ACCESSED_TIME, &date);
    if (SUCCEEDED(hr))
    {
        SYSTEMTIME st;
        VariantTimeToSystemTime(date.date, &st);
        PropVariantClear(&date);
        QDate d = QDate(st.wYear, st.wMonth, st.wDay);
        QTime t = QTime(st.wHour, st.wMinute, st.wSecond);
        new_entry.when = QDateTime(d, t).toTime_t() - tz_offset;

        // Not all MTP devices provide a valid result for
        // WPD_MEDIA_LAST_ACCESSED_TIME, so sanity check it

        // are we within (+/-) 30 days?
        long offset = new_entry.when - QDateTime::currentDateTime().toTime_t();
        if (abs(offset) > 2592000)
            new_entry.when = 0;
    }

    emit add_log(LOG_TRACE, 
        QString("%1 : %2 : %3 : %4 : %5 : %6 : %7")
        .arg(new_entry.artist)
        .arg(new_entry.title)
        .arg(new_entry.album)
        .arg(new_entry.tracknum)
        .arg(new_entry.length)
        .arg(usecount)
        .arg(skipcount)
        );

    tracks++;

    if (usecount > 0 
        && new_entry.artist.length() 
        && new_entry.title.length())
    {
        if (clear)
        {
            IPortableDeviceValues *pdv_clear = NULL;
            hr = pdv->Clear();
            hr = pdv->SetUnsignedIntegerValue(WPD_MEDIA_USE_COUNT, 0);
            hr = pdp->SetValues(object_id, pdv, &pdv_clear);
            if (SUCCEEDED(hr))
            {
                if (pdv_clear != NULL)
                    pdv_clear->Clear();
                    pdv_clear = NULL;
            }
        }
        else
        {
            playcounts++;
            new_entry.played = 'L';

            for (ULONG i = 0; i < usecount; i++)
            {
                entries++;

                // Only use the last playcount for one instance
                // we'll recalc the rest afterwards
                // via Scrobble::check_timestamps()
                if (i > 1)
                    new_entry.when = 0;
                
                emit entry(new_entry);
            }
        }
    }

mtp_get_metadata_cleanup:
    if (album)
        CoTaskMemFree(album);
    if (artist)
        CoTaskMemFree(artist);
    if (name)
        CoTaskMemFree(name);
    if (pdp)
    {
        pdp->Release();
        pdp = NULL;
    }
    if (pdv)
    {
        pdv->Release();
        pdv = NULL;
    }
}