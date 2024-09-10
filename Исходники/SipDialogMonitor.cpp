void SipDialogMonitor::publishContent(UtlString& contact, SipDialogEvent* dialogEvent)
{
   bool contentChanged;
   
   // Loop through all the resource lists
   UtlHashMapIterator iterator(mMonitoredLists);
   UtlString* listUri;
   SipResourceList* list;
   Resource* resource;
   UtlString id, state;
   while (listUri = dynamic_cast <UtlString *> (iterator()))
   {
      contentChanged = false;
      
      list = dynamic_cast <SipResourceList *> (mMonitoredLists.findValue(listUri));
      OsSysLog::add(FAC_SIP, PRI_DEBUG, "SipDialogMonitor::publishContent listUri %s list %p",
                    listUri->data(), list); 

      // Search for the contact in this list
      resource = list->getResource(contact);
      if (resource)
      {
         resource->getInstance(id, state);
         
         if (dialogEvent->isEmpty())
         {
            resource->setInstance(id, STATE_TERMINATED);
         }
         else
         {
            Dialog* dialog = dialogEvent->getFirstDialog();
            
            UtlString state, event, code;
            dialog->getState(state, event, code);
            
            if (state.compareTo(STATE_TERMINATED) == 0)
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
         int numOldContents;
         HttpBody* oldContent[1];           
   
         // Publish the content to the subscribe server
         if (!mSipPublishContentMgr.publish(listUri->data(), DIALOG_EVENT_TYPE, DIALOG_EVENT_TYPE, 1, (HttpBody**)&list, 1, numOldContents, oldContent))
         {
            UtlString dialogContent;
            int length;
            
            list->getBytes(&dialogContent, &length);
            OsSysLog::add(FAC_SIP, PRI_ERR, "SipDialogMonitor::publishContent DialogEvent %s\n was not successfully published to the subscribe server",
                          dialogContent.data());
         }
      }
   }
}