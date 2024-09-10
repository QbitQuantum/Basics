Token* nextToken()
{
    if (token)
        freeToken(&token);

    return scannerGetToken();
}