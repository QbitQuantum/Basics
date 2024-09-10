UtlBoolean EmailSendTask::handleMessage( OsMsg& rMsg )
{
   UtlBoolean handled = FALSE;
   AsynchEmailMsg* pEmailMsg = dynamic_cast <AsynchEmailMsg*> ( &rMsg );

   MailMessage msg       = pEmailMsg->getMessage();

   switch ( rMsg.getMsgType() )
   {
   case OsMsg::OS_EVENT:
   {
      UtlString response = msg.Send();
      if (!response.isNull())
      {
         if (response.length() > 0)
         {
            OsSysLog::add(FAC_ALARM, PRI_ERR, "EmailSendTask: "
                  " Error sending e-mail: response %s", response.data());
         }
      }
      handled = TRUE;
      break;
   }

   default:
      OsSysLog::add(FAC_ALARM, PRI_CRIT,
                    "EmailSendTask::handleMessage: '%s' unhandled message type %d.%d",
                    mName.data(), rMsg.getMsgType(), rMsg.getMsgSubType());
      break;
   }

   return handled;
}