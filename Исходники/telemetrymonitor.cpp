/**
 * Initiate object retrieval, initialize queue with objects to be retrieved.
 */
void TelemetryMonitor::startRetrievingObjects()
{
    // Clear object queue
    queue.clear();
    // Get all objects, add metaobjects, settings and data objects with OnChange update mode to the queue
    QList< QList<UAVObject*> > objs = objMngr->getObjects();
    for (int n = 0; n < objs.length(); ++n)
    {
        UAVObject* obj = objs[n][0];
        UAVMetaObject* mobj = dynamic_cast<UAVMetaObject*>(obj);
        UAVDataObject* dobj = dynamic_cast<UAVDataObject*>(obj);
        UAVObject::Metadata mdata = obj->getMetadata();
        if ( mobj != NULL )
        {
            queue.enqueue(obj);
        }
        else if ( dobj != NULL )
        {
            if ( dobj->isSettings() )
            {
                queue.enqueue(obj);
            }
            else
            {
                if ( UAVObject::GetFlightTelemetryUpdateMode(mdata) == UAVObject::UPDATEMODE_ONCHANGE )
                {
                    queue.enqueue(obj);
                }
            }
        }
    }
    // Start retrieving
    qxtLog->debug(tr("Starting to retrieve meta and settings objects from the autopilot (%1 objects)")
                  .arg( queue.length()) );
    retrieveNextObject();
}