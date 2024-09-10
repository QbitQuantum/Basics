int LuaObjectRenderingImpl::SetMaterialLastLOD(lua_State* L)
{
	// args=<objID, matName, lodMatNum>
	CSolidObject* obj = ParseSolidObject(L, __FUNCTION__, 1, GetObjectType());

	if (obj == nullptr)
		return 0;

	LuaObjectMaterial* objMat = GetObjectMaterial(obj, luaL_checkstring(L, 2));

	if (objMat == nullptr)
		return 0;

	objMat->SetLastLOD(luaL_checknumber(L, 3) - 1);
	return 0;
}