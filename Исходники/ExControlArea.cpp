void ExControlArea::addControl(ControlQueryType type, 
			       Int32 reset,
			       const char * sqlText, Int32 lenX,
			       const char * value1,  Int32 len1,
			       const char * value2,  Int32 len2,
			       const char * value3,  Int32 len3,
                               Int16 actionType,
                               ExControlEntry::ResendType resendType,
                               NABoolean isNonResettable)
{
   NABoolean addToList = TRUE;
   Queue *q = controlList_;
   ExControlEntry *e;

   if (reset == -1)
   {
   // CQD * RESET
   // postiion back to earlier CQD * RESET RESET
   // and remove all entries below it
      addToList = FALSE;
      // overloading the resetAllQueueEntry_ to denote that CQD * RESET was
      // issued 
      resetAllQueueEntry_ = (void *)1L;
      if (sysDefResetQueueEntry_ == NULL)
         q->position();
      else
      {
         q->position(sysDefResetQueueEntry_);
         q->getNext(); // Leave CQD * RESET RESET entry
      }
      while ((e = (ExControlEntry *)q->getNext()) != NULL)
      { 
         if  (e->type() == DEFAULT_)
         {
             if (! e->isNonResettable())
             {
                q->remove(NULL);
                NADELETE(e, ExControlEntry, heap_);
             }
         }
      }
   }
   else
   if (reset == -2)
   {
      if (sysDefResetQueueEntry_ != NULL)
      { 
         // Remove the CQD * RESET RESET entry
         q->position(sysDefResetQueueEntry_);
         e = (ExControlEntry *)q->getNext();
         q->remove(NULL);
         NADELETE(e, ExControlEntry, heap_);
      }
   }
   else
   if (reset == 1)
   {
      // Remove a CQD entry where attributes match
      // Loop to remove all matching entries for all types
      addToList = FALSE;
      if (type ==  DEFAULT_ && sysDefResetQueueEntry_ != NULL)
      {
         q->position(sysDefResetQueueEntry_);
         q->getNext();
      }
      else
         q->position();
      while ((e = (ExControlEntry *)q->getNext()) != NULL)
      {
        if (e->getActionType() != ComTdbControl::HOLD_ 
              && e->match(type, value1, value2))
        {
           if (! e->isNonResettable())
           {
              q->remove(NULL);
              NADELETE(e, ExControlEntry, heap_);
           }
           // Exactly one match for these, so stop iterating now:
           //   CQD attr RESET;
           //   CQT tbl attr RESET;
           if (len1)
              if (type != TABLE_ || len2)
                 break;
        }
      }         
   }
   else
   if ( actionType == ComTdbControl::RESTORE_)
   {
      // Remove the matching hold CQD
      addToList = FALSE;
      if (sysDefResetQueueEntry_ != NULL)
      {
         q->position(sysDefResetQueueEntry_);
         q->getNext();
      }
      else
         q->position();
      while ((e = (ExControlEntry *)q->getNext()) != NULL)
      {
        if (e->getActionType() == ComTdbControl::HOLD_ 
              && e->match(type, value1, value2))
        {
           q->remove(NULL);
           NADELETE(e, ExControlEntry, heap_);
           break;
        }
      }         
   }
   else
   if ( actionType == ComTdbControl::HOLD_)
      addToList = TRUE;
   else
   {
      addToList = TRUE;
      // If CQD * RESET RESET is already issued afer CQD * RESET is issued
      // we need to go from the system defaults
      // Otherwise go from begining and eliminate duplicates while establishing the ODBC conection
      if (type == DEFAULT_  && sysDefResetQueueEntry_ != NULL && 
                 resetAllQueueEntry_ == NULL)
      {
         q->position(sysDefResetQueueEntry_);
         q->getNext();
      }
      else
         q->position();
      while ((e = (ExControlEntry *)q->getNext()) != NULL)
      {
         if (e->getActionType() != ComTdbControl::HOLD_
                && e->match(type, value1, value2))
         {
            q->remove(NULL);
            NADELETE(e, ExControlEntry, heap_);
            break;
         }
      }
   }
   if (addToList)
   {
      char * sX = NULL;
      char * v1 = NULL;
      char * v2 = NULL;
      char * v3 = NULL;
        
      if (sqlText && lenX)
      {
         sX = new(heap_) char[lenX + 1];
         str_cpy_all(sX, (char *)sqlText, lenX);
         sX[lenX] = 0;
      }
      if (value1 && len1)
      {
          v1 = new(heap_) char[len1 + 1];
          str_cpy_all(v1, (char *)value1, len1);
          v1[len1] = 0;
      }
      if (value2 && len2)
      {
         v2 = new(heap_) char[len2 + 1];
         str_cpy_all(v2, (char *)value2, len2);
         v2[len2] = 0;
      }
      if (value3 && len3)
      {
         v3 = new(heap_) char[len3 + 1];
         str_cpy_all(v3, (char *)value3, len3);
         v3[len3] = 0;
      }
        
      e = new(heap_)
           ExControlEntry(heap_, type, reset, sX, lenX,
                   SQLCHARSETCODE_UTF8
                   , v1, len1, v2, len2, v3, len3, 
                   actionType, resendType, isNonResettable);
      if (reset == -2)
      {
         controlList_->insert(e, 0, &sysDefResetQueueEntry_);
         resetAllQueueEntry_ = NULL;
      }
      else
         controlList_->insert(e);
  }   
}