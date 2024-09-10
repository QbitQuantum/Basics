int codeIndexP(QChar code)
{
    // we are a case insensitive search
    const char latin1Code = code.toUpper().toLatin1();
    for (int idx = 0; _3of9codes[idx].code != '\0'; idx++) {
        if (_3of9codes[idx].code == latin1Code) return idx;
    }
    return -1;  // couldn't find it
}