 void deleteForward()
 {
     if (selectionStart != caretPos) {
         unsigned min = std::min(caretPos, selectionStart);
         unsigned max = std::max(caretPos, selectionStart);
         text.erase(text.begin() + min, text.begin() + max);
         selectionStart = caretPos = min;
     }
     else if (caretPos < text.length()) {
         unsigned oldCaret = caretPos;
         caretPos += 1;
         text.erase(text.begin() + oldCaret, text.begin() + caretPos);
         selectionStart = caretPos = oldCaret;
     }
     
 }