int voice_getVoices(lua_State *L)
{
    if (!pVoice || !pTokens)
        return error_voice(L);
    if (lua_gettop(L) == 0) 
    {
        ULONG count = 0;
        HRESULT hr = pTokens->GetCount(&count);
        if (FAILED(hr))
        {
            lua_pushnil(L);
            return 1;    
        }
        lua_newtable(L);
        WCHAR *buffer = NULL;
        ISpObjectToken *token = NULL;
        for (ULONG i=0; i<count; ++i)
        {
            pTokens->Item(i, &token);
            LANGID lang = 0;
            hr = SpGetLanguageFromToken(token, &lang);
            if (SUCCEEDED(hr))
                hr = SpGetDescription(token, &buffer, lang);
            token->Release();
            token=NULL;
            if (SUCCEEDED(hr)) {
            lua_pushinteger(L, i+1);
            lua_pushwstring(L, buffer);
            lua_settable(L, -3);        
            CoTaskMemFree(buffer);
            buffer = NULL;
            } 
        }
        return 1;
    }
    return error_invargs(L, L"getVoices");
}