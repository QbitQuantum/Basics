/*! Bind a shader
	@LuaMethod METHOD
	@name M:bind
*/
int lua_shader_bind(lua_State *L) {
	Shader *s = Glue<Shader>::checkto(L, 1);
	if(s) {
		s->bind();
	}
	else {
		luaL_error(L, "Shader.bind: invalid arguments");
	}
	return 0;
}