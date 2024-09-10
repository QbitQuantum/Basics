static int AddReg(lua_State * L) {
	if(lua_gettop(L) == 3) {
        if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TNUMBER) {
            luaL_checktype(L, 1, LUA_TSTRING);
            luaL_checktype(L, 2, LUA_TSTRING);
            luaL_checktype(L, 3, LUA_TNUMBER);
            lua_settop(L, 0);
            lua_pushnil(L);
            return 1;
        }

        size_t szNickLen, szPassLen;
        char *sNick = (char *)lua_tolstring(L, 1, &szNickLen);
        char *sPass = (char *)lua_tolstring(L, 2, &szPassLen);

#if LUA_VERSION_NUM < 503
		uint16_t i16Profile = (uint16_t)lua_tonumber(L, 3);
#else
        uint16_t i16Profile = (uint16_t)lua_tounsigned(L, 3);
#endif

        if(i16Profile > clsProfileManager::mPtr->iProfileCount-1 || szNickLen == 0 || szNickLen > 64 || szPassLen == 0 || szPassLen > 64 || strpbrk(sNick, " $|") != NULL || strchr(sPass, '|') != NULL) {
            lua_settop(L, 0);
            lua_pushnil(L);
            return 1;
        }

        bool bAdded = clsRegManager::mPtr->AddNew(sNick, sPass, i16Profile);

        lua_settop(L, 0);

        if(bAdded == false) {
            lua_pushnil(L);
            return 1;
        }

        lua_pushboolean(L, 1);
        return 1;
    } else if(lua_gettop(L) == 2) {
        if(lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TNUMBER) {
            luaL_checktype(L, 1, LUA_TSTRING);
            luaL_checktype(L, 2, LUA_TNUMBER);
            lua_settop(L, 0);
            lua_pushnil(L);
            return 1;
        }

        size_t szNickLen;
        char *sNick = (char *)lua_tolstring(L, 1, &szNickLen);

#if LUA_VERSION_NUM < 503
		uint16_t ui16Profile = (uint16_t)lua_tonumber(L, 2);
#else
        uint16_t ui16Profile = (uint16_t)lua_tounsigned(L, 2);
#endif

        if(ui16Profile > clsProfileManager::mPtr->iProfileCount-1 || szNickLen == 0 || szNickLen > 64 || strpbrk(sNick, " $|") != NULL) {
            lua_settop(L, 0);
            lua_pushnil(L);
            return 1;
        }

        // check if user is registered
        if(clsRegManager::mPtr->Find(sNick, szNickLen) != NULL) {
            lua_settop(L, 0);
            lua_pushnil(L);
            return 1;
        }

        User * pUser = clsHashManager::mPtr->FindUser(sNick, szNickLen);
        if(pUser == NULL) {
            lua_settop(L, 0);
            lua_pushnil(L);
            return 1;
        }

        if(pUser->uLogInOut == NULL) {
            pUser->uLogInOut = new LoginLogout();
            if(pUser->uLogInOut == NULL) {
                pUser->ui32BoolBits |= User::BIT_ERROR;
                pUser->Close();

                AppendDebugLog("%s - [MEM] Cannot allocate new pUser->uLogInOut in RegMan.AddReg\n", 0);
                lua_settop(L, 0);
                lua_pushnil(L);
                return 1;
            }
        }

        pUser->SetBuffer(clsProfileManager::mPtr->ProfilesTable[ui16Profile]->sName);
        pUser->ui32BoolBits |= User::BIT_WAITING_FOR_PASS;

        int iMsgLen = sprintf(clsServerManager::sGlobalBuffer, "<%s> %s.|$GetPass|", clsSettingManager::mPtr->sPreTexts[clsSettingManager::SETPRETXT_HUB_SEC], clsLanguageManager::mPtr->sTexts[LAN_YOU_WERE_REGISTERED_PLEASE_ENTER_YOUR_PASSWORD]);
        if(CheckSprintf(iMsgLen, clsServerManager::szGlobalBufferSize, "RegMan.AddReg1") == true) {
            pUser->SendCharDelayed(clsServerManager::sGlobalBuffer, iMsgLen);
        }

        lua_settop(L, 0);
        lua_pushboolean(L, 1);
        return 1;
    } else {
        luaL_error(L, "bad argument count to 'RegMan.AddReg' (2 or 3 expected, got %d)", lua_gettop(L));
        lua_settop(L, 0);
        lua_pushnil(L);
        return 1;
    }
}