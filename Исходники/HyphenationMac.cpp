 size_t lastHyphenLocation(const StringView& text,
                           size_t beforeIndex) const override {
   CFIndex result = CFStringGetHyphenationLocationBeforeIndex(
       text.toString().impl()->createCFString().get(), beforeIndex,
       CFRangeMake(0, text.length()), 0, m_localeCF.get(), 0);
   return result == kCFNotFound ? 0 : result;
 }