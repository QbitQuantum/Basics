static void AddEnvironmentVariable(struct environment* env,const char* varName, const char* valueString)
{
    size_t len;
    size_t envSize = MAX_PATH - (env->p_head-env->env);
    StringCbCopyA(env->p_head, envSize, varName);
    StringCbCatA(env->p_head, envSize, "=");
    StringCbCatA(env->p_head, envSize, valueString);
    StringCbCatA(env->p_head, envSize, "\0");
    len = strnlen_s(env->p_head, envSize);
    env->p_head += (len + 1);
}