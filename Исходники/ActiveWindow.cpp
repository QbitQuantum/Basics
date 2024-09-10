void
ActiveWindow::SetText(const Text& t)
{
    if (t && text != t) {
        int len = t.length();

        if (len > 0 && t.contains('\\')) {
            char* buf = new(__FILE__,__LINE__) char[2*len];

            if (buf != 0) {
                const char* src = t;
                char* dst = buf;

                while (*src) {
                    if (*src != '\\') {
                        *dst++ = *src++;
                    }
                    else {
                        src++;

                        switch (*src) {
                        case 'n': *dst++ = '\n';   break;
                        case 't': *dst++ = '\t';   break;
                        default:  *dst++ = *src;   break;
                        }

                        src++;
                    }
                }

                *dst = 0;

                if (text != buf) {
                    text = buf;
                }

                delete [] buf;
            }
        }
        else {
            text = t;
        }
    }
}