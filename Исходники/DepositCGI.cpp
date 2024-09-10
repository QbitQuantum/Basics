OsStatus
DepositCGI::execute(UtlString* out)
{
   // Contains the dynamically generated VXML script.
   UtlString dynamicVxml = getVXMLHeader() + "<form> ";

   // Get the base URL of the mediaserver - "http://*****:*****@' ) != UTL_NOT_FOUND )
            {
               useridOrExtension =
                  useridOrExtension(0, useridOrExtension.first( '@' ));
            }
         }
         useridOrExtension.toLower();
         dynamicVxml +=
            "<var name=\"msgurl\" expr=\"'" + useridOrExtension + "'\" />\n" \
            "<var name=\"msgurltype\" expr=\"'alphanumeric'\"/>\n";
      }

      // If mailboxpath/savemessage.vxml exists, use it, otherwise use the 
      // generic version
      UtlString src ;
      UtlString vxmlScript ;
      pMailboxManager->getMailboxPath(m_mailboxIdentity, vxmlScript);
      vxmlScript += OsPath::separator + "savemessage.vxml" ;
      if (OsFileSystem::exists(vxmlScript))
      {
         // use the user specific one 
         pMailboxManager->getMailboxURL(m_mailboxIdentity, src, false);
         src += "/savemessage.vxml" ;
         OsSysLog::add(FAC_MEDIASERVER_CGI, PRI_DEBUG,
                 "DepositCGI::execute: using user specific vxml script %s",
                 src.data()) ;
      }
      else
      {
         // use the generic one
         src =  mediaserverUrl + "/vm_vxml/savemessage.vxml" ;
         OsSysLog::add(FAC_MEDIASERVER_CGI, PRI_DEBUG,
                 "DepositCGI::execute: using generic vxml script %s",
                 src.data()) ;
      }

      // Be careful here as the the vxmlFriendlyFrom will be sent back to us again
      UtlString vxmlFriendlyFrom = m_from.toString();
      MailboxManager::convertUrlStringToXML( vxmlFriendlyFrom );
      // HttpMessage::escape( vxmlFriendlyFrom );

      dynamicVxml +=
         "<subdialog name=\"send_msg\" src=\"" + src + "\">\n" +
         "<param name=\"called_by\" value=\"incoming\"/>\n" \
         "<param name=\"mailbox\" value=\"" + m_mailboxIdentity + "\"/>\n" \
         "<param name=\"from\" value=\"" + vxmlFriendlyFrom + "\"/>\n" \
         "<param name=\"msgurl\" expr=\"msgurl\" />\n" \
         "<param name=\"msgurltype\" expr=\"msgurltype\" />\n" \
         "<param name=\"mediaserverurl\" expr=\"'" + ivrPromptUrl + "'\"/>\n" \
         "<param name=\"securemediaserverurl\" expr=\"'" + secureMediaserverUrl + "'\"/>\n" \
         "</subdialog>";
   } else
   {
      dynamicVxml +=    "<subdialog src=\"" + mediaserverUrl + "/vm_vxml/error_handler.vxml\" >\n" \
         "<param name=\"errortype\" expr=\"'invalidextn'\" />\n" \
         "<param name=\"mediaserverurl\" expr=\"'" + ivrPromptUrl + "'\" />\n" \
         "<param name=\"securemediaserverurl\" expr=\"'" + secureMediaserverUrl + "'\"/>\n" \
         "</subdialog>\n";
   }

   dynamicVxml += "</form>" + UtlString( VXML_END );

   // Write out the dynamic VXML script to be processed by OpenVXI
   if (out)
   {
      out->remove(0);
      UtlString responseHeaders;
      MailboxManager::getResponseHeaders(dynamicVxml.length(), responseHeaders);

      out->append(responseHeaders.data());
      out->append(dynamicVxml.data());
   }

   return OS_SUCCESS;
}