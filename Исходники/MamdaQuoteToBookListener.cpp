 void onUpdate (MamdaQuoteToBookListenerImpl&  impl,
                const MamaMsgField&            field)
 {
     if (field.getType () == MAMA_FIELD_TYPE_STRING)
     {
         impl.mQuoteCache.mQuoteQualNative = field.getString();
     }
     else if (field.getType () == MAMA_FIELD_TYPE_CHAR)
     {
         impl.mQuoteCache.mQuoteQualNative = field.getChar();
     }
 }