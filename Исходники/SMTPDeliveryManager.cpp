   void
   SMTPDeliveryManager::DoWork()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Responsible for creating threads to deliver messages.
   //---------------------------------------------------------------------------()
   {
      LOG_DEBUG("SMTPDeliveryManager::Start()");

      // Unlock all messages
      PersistentMessage::UnlockAll();

      shared_ptr<WorkQueue> pQueue = WorkQueueManager::Instance()->GetQueue(GetQueueName());

      while (1)
      {
         // Deliver all pending messages
         shared_ptr<Message> pMessage;
         while (pMessage = _GetNextMessage())
         {
            // Lock this message
            if (!PersistentMessage::LockObject(pMessage))
            {
               // Failed to lock the message.
               ErrorManager::Instance()->ReportError(ErrorManager::Critical, 4216, "SMTPDeliveryManager::DoWork", "Failed to lock message.");
               continue;
            }

            shared_ptr<DeliveryTask> pDeliveryTask = shared_ptr<DeliveryTask>(new DeliveryTask(pMessage));
            WorkQueueManager::Instance()->AddTask(m_iQueueID, pDeliveryTask);
            
            m_lCurNumberOfSent++;

            _SendStatistics();

            ServerStatus::Instance()->OnMessageProcessed();
         }

         _StartTimer();

         const int iSize = 3;
         HANDLE handles[iSize];

         handles[0] = m_hStopRequest.GetHandle();
         handles[1] = m_evtDeliverMessage.GetHandle();
         handles[2] = m_evtTimer;
      
         DWORD dwWaitResult = WaitForMultipleObjects(iSize, handles, FALSE, INFINITE);

         int iEvent = dwWaitResult - WAIT_OBJECT_0;

         // Temp test to see if cause of IOCP errors

         if (iEvent < 0)
         {

            ErrorManager::Instance()->ReportError(ErrorManager::Critical, 9999, "SMTPDeliveryManager::DoWork", "WARNING iEvent less than 0!");
            m_evtDeliverMessage.Reset();
            return;
         }
         else
         {
         switch (iEvent)
         {
         case 0:
            // We should stop now
            _SendStatistics(true);
            return;
         case 1:
            // --- Reset the event to give someone else the chance to 
            //     sending emails.
            m_evtDeliverMessage.Reset();
            break;
         }
}
      }

      _SendStatistics(true);
      
      
      return;
   }