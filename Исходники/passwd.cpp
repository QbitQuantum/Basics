bool PasswdProcess::isPrompt(QCString line, const char *word)
{
    unsigned i, j, colon;
    unsigned int lineLength(line.length());
    for(i = 0, j = 0, colon = 0; i < lineLength; i++)
    {
        if(line[i] == ':')
        {
            j = i;
            colon++;
            continue;
        }
        if(!isspace(line[i]))
            j++;
    }

    if((colon != 1) || (line[j] != ':'))
        return false;
    if(word == 0L)
        return true;
    return line.contains(word, false);
}