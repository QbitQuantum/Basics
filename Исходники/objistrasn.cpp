void CObjectIStreamAsn::ReadAnyContent(string& value)
{
    char buf[128];
    size_t pos=0;
    const size_t maxpos=128;

    char to = GetChar(true);
    buf[pos++] = to;
    if (to == '{') {
        to = '}';
    } else if (to == '\"') {
    } else {
        to = '\0';
    }

    bool space = false;
    for (char c = m_Input.PeekChar(); ; c = m_Input.PeekChar()) {
        if (to != '\"') {
            if (to != '}' && c == '\n') {
                value.append(buf,pos);
                return;
            }
            if (isspace((unsigned char) c)) {
                if (space) {
                    m_Input.SkipChar();
                    continue;
                }
                c = ' ';
                space = true;
            } else {
                space = false;;
            }
            if (to != '}' && (c == ',' || c == '}')) {
                value.append(buf,pos);
                return;
            } else if (c == '\"' || c == '{') {
                value.append(buf,pos);
                ReadAnyContent(value);
                pos = 0;
                continue;
            }
        }
        if (c == to) {
            if (pos >= maxpos) {
                value.append(buf,pos);
                pos = 0;
            }
            buf[pos++] = c;
            value.append(buf,pos);
            m_Input.SkipChar();
            return;
        }
        if (c == '\"' || c == '{') {
            value.append(buf,pos);
            ReadAnyContent(value);
            pos = 0;
            continue;
        }
        if (pos >= maxpos) {
            value.append(buf,pos);
            pos = 0;
        }
        buf[pos++] = c;
        m_Input.SkipChar();
    }
}