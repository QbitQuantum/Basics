/* Get the validated names for the connection peer.
 *
 * Usually, the names in the altNames will be easier to parse and use than commonName
 * Returns
 * - true if the connection peer is validated by a trusted authority
 * - false if not, in which case no names are returned.
 */
bool OsSSL::peerIdentity( SSL*       connection ///< SSL connection to be described
                         ,UtlSList*  altNames   /**< UtlStrings for verfied subjectAltNames
                                                 *   are added to this - caller must free them.
                                                 */
                         ,UtlString* commonName ///< the Subject name is returned here
                         )
{
   bool peerCertTrusted = false;

#  ifdef TEST_DEBUG
   UtlString debugMsg;
#  endif

   if (altNames)
   {
      altNames->destroyAll();
   }
   if (commonName)
   {
      commonName->remove(0);
   }

   if (connection)
   {
      // Extract the subject and issuer information about the peer
      // and the certificate validation result.  Neither of these
      // are meaningful without the other.
      //    (note various dynamically allocated items - freed below)
      X509* peer_cert = SSL_get_peer_certificate(connection);
      if (peer_cert)
      {
         if (X509_V_OK == SSL_get_verify_result(connection))
         {
            peerCertTrusted = true;

            char* subjectStr = X509_NAME_oneline(X509_get_subject_name(peer_cert),NULL,0);

            // @TODO this should also enforce any extendedKeyUsage limitations

#           ifdef TEST_DEBUG
            debugMsg.append("OsSSL::peerIdentity verified");
#           endif
            if (subjectStr)
            {
               // this should always be true, I think...
               if (commonName)
               {
                  commonName->append(subjectStr);
               }

#              ifdef TEST_DEBUG
               debugMsg.append(" '");
               debugMsg.append(subjectStr);
               debugMsg.append("'");
#              endif
               OPENSSL_free(subjectStr);
            }

            if (altNames)
            {
               // Look for the subjectAltName attributes
               GENERAL_NAMES* names;
               names = (GENERAL_NAMES*)X509_get_ext_d2i(peer_cert, NID_subject_alt_name, NULL, NULL);

               for(int i = 0; i < sk_GENERAL_NAME_num(names); i++)
               {
                  GENERAL_NAME*   name = sk_GENERAL_NAME_value(names, i);
                  ASN1_IA5STRING* nameValue;
                  UtlString*      normalizedName;

                  switch (name->type)
                  {
                  case GEN_DNS:
                  case GEN_URI:
                     nameValue = name->d.uniformResourceIdentifier;
                     normalizedName
                        = new UtlString((const char*)(nameValue->data),nameValue->length);
                     // @TODO: We should parse this value before adjusting the case,
                     //        but that requires doing it at a higher level in the stack
                     //        where we can parse a URL, and we don't yet have selection
                     //        based on type anyway.
                     normalizedName->toLower();
#                    ifdef TEST_DEBUG
                     debugMsg.append(" '");
                     debugMsg.append(*normalizedName);
                     debugMsg.append("'");
#                    endif
                     altNames->append(normalizedName);
                     break;

                  default:
                     // don't care about any other values
                     break;
                  }
               }
               sk_GENERAL_NAME_pop_free(names, GENERAL_NAME_free);
            }
#           ifdef TEST_DEBUG
            OsSysLog::add(FAC_KERNEL, PRI_DEBUG, "%s", debugMsg.data());
#           endif
         }
         else
         {
            OsSysLog::add(FAC_KERNEL, PRI_ERR, "OsSSL::peerIdentity peer not validated");
         }

         X509_free(peer_cert);
      }
      else
      {
         OsSysLog::add(FAC_KERNEL, PRI_WARNING, "OsSSL::peerIdentity no peer certificate");
      }
   }
   else
   {
      OsSysLog::add(FAC_KERNEL, PRI_CRIT, "OsSSL::peerIdentity called with NULL connection");
   }

   return peerCertTrusted;
}