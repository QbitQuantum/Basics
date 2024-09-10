wxCharBuffer MIME::EncodeHeader(const String& in, wxFontEncoding enc)
{
   if ( !NeedsEncoding(in) )
      return in.ToAscii();

   // decide about the encoding to use if none specified
   if ( enc == wxFONTENCODING_SYSTEM )
   {
      // try to use the user current encoding first
      enc = wxLocale::GetSystemEncoding();
   }

   if ( wxCSConv(enc).FromWChar(NULL, 0, in.wc_str(wxConvLibc)) == wxCONV_FAILED )
   {
      // but if we can't encode with it, fall back to UTF-8 as it never fails
      enc = wxFONTENCODING_UTF8;
   }

   // get the encoding in RFC 2047 sense
   MIME::Encoding enc2047 = MIME::GetEncodingForFontEncoding(enc);

   if ( enc2047 == MIME::Encoding_Unknown )
   {
      FAIL_MSG( _T("should have valid MIME encoding") );

      enc2047 = MIME::Encoding_QuotedPrintable;
   }

   // get the name of the charset to use
   String csName = MIME::GetCharsetForFontEncoding(enc);
   if ( csName.empty() )
   {
      FAIL_MSG( _T("should have a valid charset name!") );

      csName = _T("UNKNOWN");
   }


   String headerEnc;
   headerEnc.reserve(2*in.length());

   // for QP we encode each header word separately as some might not need being
   // encoded at all and the header remains more readable if we don't encode
   // them unnecessarily, but for Base64 it's useless to do this as it's
   // unreadable anyhow so we just encode everything at once
   if ( enc2047 == MIME::Encoding_QuotedPrintable )
   {
      // encode each word of the header if necessary, taking into account one
      // added complication: white space between 2 consecutive encoded words is
      // ignored during decoding, so we must encode 2 consecutive words both of
      // which need encoding as one single encoded word or the space between
      // them would be lost
      bool lastWordEncoded = false;
      const wxArrayString words(wxStringTokenize(in));
      const size_t count = words.size();
      for ( size_t n = 0; n < count; ++n )
      {
         const wxString& word = words[n];
         if ( NeedsEncoding(word) )
         {
            const String wordEnc = EncodeText(word, enc, enc2047, csName);

            if ( lastWordEncoded )
            {
               // we need to merge the 2 consecutive encoded words together: we
               // do it by removing "?=" suffix from the previous word, adding
               // a space and remove the "=?charset?Q?" prefix from this word
               ASSERT_MSG( headerEnc.length() > 7, "bad QP-encoded last word" );
               headerEnc.RemoveLast(2); // "?="

               headerEnc += '_'; // space can be represented like this in QP

               const size_t posText = wordEnc.find("?Q?");
               ASSERT_MSG( posText != String::npos, "bad QP-encoded word" );
               headerEnc += wordEnc.substr(posText + 3);
            }
            else // last word not encoded, just append this one
            {
               if ( !headerEnc.empty() )
                  headerEnc += ' ';

               headerEnc += wordEnc;
            }

            lastWordEncoded = true;
         }
         else // this word doesn't need to be encoded, simply append it
         {
            if ( !headerEnc.empty() )
               headerEnc += ' ';

            headerEnc += word;

            lastWordEncoded = false;
         }
      }
   }
   else // MIME::Encoding_Base64
   {
      headerEnc = EncodeText(in, enc, enc2047, csName);
   }

   return headerEnc.ToAscii();
}