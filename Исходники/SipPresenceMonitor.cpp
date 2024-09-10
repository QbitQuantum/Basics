void SipPresenceMonitor::publishContent(UtlString& contact, SipPresenceEvent* presenceEvent)
{
#ifdef SUPPORT_RESOURCE_LIST
   // Loop through all the resource lists
   UtlHashMapIterator iterator(mMonitoredLists);
   UtlString* listUri;
   SipResourceList* list;
   Resource* resource;
   UtlString id, state;
   while (listUri = dynamic_cast <UtlString *> (iterator()))
   {
      bool contentChanged = false;

      list = dynamic_cast <SipResourceList *> (mMonitoredLists.findValue(listUri));
      OsSysLog::add(FAC_SIP, PRI_DEBUG, "SipPresenceMonitor::publishContent listUri %s list %p",
                    listUri->data(), list);

      // Search for the contact in this list
      resource = list->getResource(contact);
      if (resource)
      {
         resource->getInstance(id, state);

         if (presenceEvent->isEmpty())
         {
            resource->setInstance(id, STATE_TERMINATED);
         }
         else
         {
            UtlString id;
            makeId(id, contact);
            Tuple* tuple = presenceEvent->getTuple(id);

            UtlString status;
            tuple->getStatus(status);

            if (status.compareTo(STATUS_CLOSED) == 0)
            {
               resource->setInstance(id, STATE_TERMINATED);
            }
            else
            {
               resource->setInstance(id, STATE_ACTIVE);
            }
         }

         list->buildBody();
         contentChanged = true;
      }

      if (contentChanged)
      {
         // Publish the content to the subscribe server
         // Make a copy, because mpSipPublishContentMgr will own it.
         HttpBody* pHttpBody = new HttpBody(*(HttpBody*)list);
         mSipPublishContentMgr.publish(listUri->data(),
                                       PRESENCE_EVENT_TYPE, PRESENCE_EVENT_TYPE,
                                       1, &pHttpBody);
      }
   }
#endif

   // Publish the content to the subscribe server
   // Make a copy, because mpSipPublishContentMgr will own it.
   HttpBody* pHttpBody = new HttpBody(*(HttpBody*)presenceEvent);
   mSipPublishContentMgr.publish(contact.data(),
                                 PRESENCE_EVENT_TYPE, PRESENCE_EVENT_TYPE,
                                 1, &pHttpBody);
}