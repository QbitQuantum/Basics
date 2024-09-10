   void tearDown()
      {
         // Clean up to prevent use of the queue after it goes out of scope.
         notifierUserAgentp->removeMessageObserver(incomingClientMsgQueue);
         notifierUserAgentp->removeMessageObserver(incomingClientMsgQueue);

         OsTask::delay(1000);

         notifierUserAgentp->shutdown(TRUE);
         delete notifierUserAgentp;

         subscriberUserAgentp->shutdown(TRUE);
         delete subscriberUserAgentp;

         delete subServerp;
      }