Token* scannerGetToken() // FUNCTION, WHICH RETURNS POINTER ON TOKEN STRUCTURE
{
    Token *token = newToken();

    scannerFillToken(token);
    if (getError()) {
        freeToken(&token);
        fclose(source);
        source = NULL;
        return NULL;
    }

    if (token->type == STT_EOF) {
        fclose(source);
        source = NULL;
    }

    return token;
}