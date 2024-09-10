static HRESULT STDMETHODCALLTYPE
CDevSettings_EnumFormatEtc(IDataObject* iface,
                           DWORD dwDirection,
                           IEnumFORMATETC** ppenumFormatEtc)
{
    HRESULT hr;
    FORMATETC fetc[9];
    PCDevSettings This = impl_from_IDataObject(iface);

    *ppenumFormatEtc = NULL;

    if (dwDirection == DATADIR_GET)
    {
        pCDevSettings_FillFormatEtc(&fetc[0],
                                    This->cfExtInterface);
        pCDevSettings_FillFormatEtc(&fetc[1],
                                    This->cfDisplayDevice);
        pCDevSettings_FillFormatEtc(&fetc[2],
                                    This->cfDisplayName);
        pCDevSettings_FillFormatEtc(&fetc[3],
                                    This->cfDisplayId);
        pCDevSettings_FillFormatEtc(&fetc[4],
                                    This->cfDisplayKey);
        pCDevSettings_FillFormatEtc(&fetc[5],
                                    This->cfDisplayStateFlags);
        pCDevSettings_FillFormatEtc(&fetc[6],
                                    This->cfMonitorName);
        pCDevSettings_FillFormatEtc(&fetc[7],
                                    This->cfMonitorDevice);
        pCDevSettings_FillFormatEtc(&fetc[8],
                                    This->cfPruningMode);

        hr = SHCreateStdEnumFmtEtc(sizeof(fetc) / sizeof(fetc[0]),
                                   fetc,
                                   ppenumFormatEtc);
    }
    else
        hr = E_NOTIMPL;

    return hr;
}