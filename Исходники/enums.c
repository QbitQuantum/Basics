int pushtexturetype(lua_State *L, unsigned int value)
    {
    switch(value)
        {
#define CASE(CODE,str) case CODE: lua_pushstring(L, str); break
    CASE(aiTextureType_NONE, "none");
    CASE(aiTextureType_DIFFUSE, "diffuse");
    CASE(aiTextureType_SPECULAR, "specular");
    CASE(aiTextureType_AMBIENT, "ambient");
    CASE(aiTextureType_EMISSIVE, "emissive");
    CASE(aiTextureType_HEIGHT, "height");
    CASE(aiTextureType_NORMALS, "normals");
    CASE(aiTextureType_SHININESS, "shininess");
    CASE(aiTextureType_OPACITY, "opacity");
    CASE(aiTextureType_DISPLACEMENT, "displacement");
    CASE(aiTextureType_LIGHTMAP, "lightmap");
    CASE(aiTextureType_REFLECTION, "reflection");
    CASE(aiTextureType_UNKNOWN, "unknown");
#undef CASE
        default:
            return unexpected(L);
        }
    return 1;
    }