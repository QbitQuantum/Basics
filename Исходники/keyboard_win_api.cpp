Keyboard::Press KeyboardWinAPI::getPress (WPARAM wParam, LPARAM scan_code)
{
        Keyboard::Press r;
        BYTE state[256] = {0};

        WCHAR buf[1024] = {0};
        int ret = ToUnicodeEx(wParam, scan_code, state,
                              buf, sizeof(buf)/sizeof(*buf),
                              0, GetKeyboardLayout(0));

        bool dead = false;
        if (ret==-1) {
                /* The specified virtual key is a dead-key character (accent or diacritic).
                 * This value is returned regardless of the keyboard layout, even if several
                 * characters have been typed and are stored in the keyboard state. If possible,
                 * even with Unicode keyboard layouts, the function has written a spacing
                 * version of the dead-key character to the buffer specified by pwszBuff.
                 * For example, the function writes the character SPACING ACUTE (0x00B4),
                 * rather than the character NON_SPACING ACUTE (0x0301). */

                // We still want to allow this key to be bound to things, so provide the spacing char as the key.
                ret = 1;
                dead = true; // for debug output
        }
        if (ret<0 || ret>=sizeof(buf)/sizeof(*buf)) {
                CERR << "ToUnicodeEx returned out of range: " << ret << std::endl;
                ret = 0;
        }
        if (ret>1) {
                /* Two or more characters were written to the buffer specified by pwszBuff. The
                 * most common cause for this is that a dead-key character (accent or diacritic)
                 * stored in the keyboard layout could not be combined with the specified virtual
                 * key to form a single character. */
                // No idea what this means but I think I should ignore anything from the 'previous' key
                // HACK: this may break if buf contains surrogate pairs!
                buf[0] = buf[ret-1];
                ret = 1;
        }

        buf[ret] = 0;
        if (verbose) {
                std::stringstream ss;
                ss << "[";
                for (int i=0 ; i<ret ; ++i) {
                        ss << (i==0 ? " " : ", ") << std::hex << "0x" << ((int)buf[i]) << std::dec;
                }
                ss << " ]";
                if (dead) ss << "!";
                CLOG << ss.str() << std::endl;
        }

        return utf16_to_utf8(buf);
}