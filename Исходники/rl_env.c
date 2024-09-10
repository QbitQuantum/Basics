//------------------------------------------------------------------------------
static void capture_env(env_block_t* block)
{
    void* env;
    const wchar_t* c;
    void* data;
    int size;

    env = GetEnvironmentStringsW();

    size = 0;
    c = (const wchar_t*)env;
    while (1)
    {
        if (*((const int*)(c)) == 0)
        {
            size += 4;
            break;
        }

        size += 2;
        ++c;
    }

    data = malloc(size);
    memcpy(data, env, size);

    block->data = data;
    block->size = size;

    FreeEnvironmentStringsW(env);
}