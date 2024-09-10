/** int startEL(char *app, os_el *el)
 * Starts the event logging for each el
 */
int startEL(char *app, os_el *el)
{
    /* Opening the event log */
    el->h = OpenEventLog(NULL, app);
    if(!el->h)
    {
        return(0);	
    }

    el->name = app;
    GetOldestEventLogRecord(el->h, &el->record);

    return(1);
}