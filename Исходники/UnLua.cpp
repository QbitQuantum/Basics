static int
luaCallFunction(lua_State *L)
{
	int numparams = lua_gettop(L);
	lua_getglobal(L, "__unlua");
	AActor* unlua = (AActor*) lua_topointer(L, -1);
	lua_remove(L, -1);

	AActor* actor = (AActor*) lua_topointer(L, lua_upvalueindex(1));
	UFunction* func = (UFunction*) lua_topointer(L, lua_upvalueindex(2));
	const char* funcName_s = lua_tostring(L, lua_upvalueindex(3));
	

	if (func->NumParms == 0) {
		actor->ProcessEvent(func, NULL, NULL);
		return 0;
	}

	TFieldIterator<UProperty> It (func);
	char params[1024];
	memset(params, 0, sizeof(params));
	char* parptr = params;
	TArray<FString*> allocatedStrings;
	for (int i = 0; i < func->NumParms; ++i) {
		if (i >= numparams) {
			if (It->PropertyFlags & CPF_OptionalParm) {
				break;
			} else {
				lua_pushfstring(L, "Too few parameters for call to %s", funcName_s);
				lua_error(L);
			}
		}
		if (It->IsA(UIntProperty::StaticClass())) {
			int anint = lua_tointeger(L, i + 1);
			memcpy(parptr, &anint, It->ElementSize);
		} else if (It->IsA(UStrProperty::StaticClass())) {
			FString* astr = new FString(lua_tostring(L, i + 1));
			allocatedStrings.AddItem(astr);
			memcpy(parptr, astr, It->ElementSize);
		} else if (It->IsA(UNameProperty::StaticClass())) {
			FString astr(lua_tostring(L, i + 1));
			FName aname(*astr, FNAME_Add);
			memcpy(parptr, &aname, It->ElementSize);
		} else if (It->IsA(UByteProperty::StaticClass())) {
			*parptr = (char) lua_tointeger(L, i + 1);
		} else if (It->IsA(UBoolProperty::StaticClass())) {
			int bval = lua_toboolean(L, i + 1);
			memcpy(parptr, &bval, It->ElementSize);
		} else if (It->IsA(UFloatProperty::StaticClass())) {
			float fval = (float)lua_tonumber(L, i + 1);
			memcpy(parptr, &fval, It->ElementSize);
		} else if (It->IsA(UObjectProperty::StaticClass())) {
			UObjectProperty *uop = (UObjectProperty*) *It;
			struct UnLuaActor* ula  = (struct UnLuaActor*)
				luaL_testudata(L, i + 1, "UnrealActor");
			struct UnrealClass* ulc = (struct UnrealClass*)
				luaL_testudata(L, i + 1, "UnrealClass");
			UObject** uobj = (UObject**) parptr;
			if ((ula == NULL) && (ulc == NULL))
				*uobj = NULL;
			else {
				if (uop->PropertyClass == UClass::StaticClass()) {
					if (ulc == NULL) {
						lua_pushfstring(L, "Invalid type for parameter %d", i+1);
						lua_error(L);
					}
					*uobj = ulc->uclass;
				} else {
					if (ula->actor->IsA(uop->PropertyClass)) {
						//memcpy(parptr, ula->actor, It->ElementSize);
						*uobj = ula->actor;
					} else {
						lua_pushfstring(L, "Invalid type for parameter %d", i+1);
						lua_error(L);
					}
				}
			}
		} else {
			lua_pushfstring(L, "luaCallFunction: Unreal function %s requires "
				"parameter type not yet supported by UnLua", funcName_s);
			lua_error(L);
		}
		parptr += It->ElementSize;
		++It;
	}
	actor->ProcessEvent(func, params, NULL);
	free(params);
	while(allocatedStrings.Num())
		delete allocatedStrings.Pop();

	return 0;
}