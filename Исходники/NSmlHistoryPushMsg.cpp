// ---------------------------------------------------------
// CSyncMLHistoryPushMsg::AddAlertsL(RPointerArray<CSmlAlertInfo>& aAlertInfoArray)
// Adds alerts to entry
// Ownership of CSmlAlertInfo objects is transferred.
// ---------------------------------------------------------
EXPORT_C void CSyncMLHistoryPushMsg::AddAlertsL(RPointerArray<CSmlAlertInfo>& aAlertInfoArray)
{
    ResetAlerts();

    while ( aAlertInfoArray.Count() )
    {
        CSmlAlertInfo* temp = aAlertInfoArray[0];
        iAlerts.AppendL( temp );
        aAlertInfoArray.Remove(0);
    }

}