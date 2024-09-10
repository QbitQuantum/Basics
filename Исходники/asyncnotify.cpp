VOID
SendAsyncNotification(
    _In_ LPWSTR     pPrinterName,
    EOEMDataSchema  action
)
{
    IPrintAsyncNotifyChannel *pIAsynchNotification = NULL;

    CPrintOEMAsyncNotifyCallback *pIAsynchCallback = new CPrintOEMAsyncNotifyCallback;

    if (pIAsynchCallback)
    {
        RouterCreatePrintAsyncNotificationChannel(pPrinterName,
                const_cast<GUID*>(&SAMPLE_NOTIFICATION_UI),
                kPerUser,
                kBiDirectional,
                pIAsynchCallback,
                &pIAsynchNotification);

        pIAsynchCallback->Release();
    }

    if (pIAsynchNotification)
    {
        BYTE data[4] = { 0 };
        MarshalSchema(action, data);
        CPrintOEMAsyncNotifyDataObject *pClientNotification = new CPrintOEMAsyncNotifyDataObject(data,
                sizeof(data),
                const_cast<GUID*>(&SAMPLE_NOTIFICATION_UI));

        if (pClientNotification)
        {
            pIAsynchNotification->SendNotification(pClientNotification);

            pClientNotification->Release();
        }

        pIAsynchNotification->Release();
    }
}