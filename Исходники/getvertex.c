static int ArrayGetInt_(lua_State *L, GLuint array, GLenum pname, int boolean)
#define ArrayGetInt(L, array, pname) ArrayGetInt_((L), (array), (pname), 0)
#define ArrayGetBoolean(L, array, pname) ArrayGetInt_((L), (array), (pname), 1)
    {
    GLint param;
    GLuint index = luaL_checkinteger(L, 3);
    glGetVertexArrayIndexediv(array, index, pname, &param);
    CheckError(L);
    if(boolean)
        lua_pushboolean(L, param);
    else
        lua_pushinteger(L, param);
    return 1;
    }