 void TrackingStream::next_line()
 {
     if (std::getline(*in, text))
         text += '\n';
     else
         text.clear();
     // hereafter empty text means error
     line++;
     col = 0;
     if (text.empty() and !eof_message.empty())
         throw Unexpected(position(), eof_message);
     for (unsigned char c : text)
         if (c < ' ' and c != '\n')
         {
             if (c == '\t')
                 throw Unexpected(position(), "tab (try the 'expand' program)");
             if (c == '\r')
                 throw Unexpected(position(), "carriage return (try the 'dos2unix' program)");
             throw Unexpected(position(), "C0 control character");
         }
 }