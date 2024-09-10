	/*** XmlForLua ***/
	int XmlForLua::_Encode(lua_State* L){
		// prepare name
		if((lua_gettop(L)<1) || (!lua_istable(L, 1))){
			lua_pushnil(L);
			lua_pushstring(L, "invalid arg");
			return 2;
		}
		// parse
		TiXmlPrinter printer;
		printer.SetIndent("\t");
		TiXmlElement* ele =lua_to_xml(L, "root");
		if(ele->Accept(&printer) && printer.CStr()){
			lua_pushstring(L, printer.CStr());
			delete ele;
			return 1;
		}
		else{
			lua_pushnil(L);
			lua_pushstring(L, "tinyxml unknown error");
			delete ele;
			return 2;
		}
	}