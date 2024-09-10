Length* StringImpl::toCoordsArray(int& len)
{
    StringBuffer spacified(m_length);
    for (unsigned i = 0; i < m_length; i++) {
        UChar cc = m_data[i];
        if (cc > '9' || (cc < '0' && cc != '-' && cc != '*' && cc != '.'))
            spacified[i] = ' ';
        else
            spacified[i] = cc;
    }
    RefPtr<StringImpl> str = adopt(spacified);

    str = str->simplifyWhiteSpace();

    len = countCharacter(str.get(), ' ') + 1;
    Length* r = new Length[len];

    int i = 0;
    int pos = 0;
    int pos2;

    while ((pos2 = str->find(' ', pos)) != -1) {
        r[i++] = parseLength(str->characters() + pos, pos2 - pos);
        pos = pos2+1;
    }
    r[i] = parseLength(str->characters() + pos, str->length() - pos);

    ASSERT(i == len - 1);

    return r;
}