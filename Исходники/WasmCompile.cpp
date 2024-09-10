static SharedBytes
CreateBytecode(const Bytes& env, const Bytes& code, const Bytes& tail, UniqueChars* error)
{
    size_t size = env.length() + code.length() + tail.length();
    if (size > MaxModuleBytes) {
        *error = DuplicateString("module too big");
        return nullptr;
    }

    MutableBytes bytecode = js_new<ShareableBytes>();
    if (!bytecode || !bytecode->bytes.resize(size))
        return nullptr;

    uint8_t* p = bytecode->bytes.begin();

    memcpy(p, env.begin(), env.length());
    p += env.length();

    memcpy(p, code.begin(), code.length());
    p += code.length();

    memcpy(p, tail.begin(), tail.length());
    p += tail.length();

    MOZ_ASSERT(p == bytecode->end());

    return bytecode;
}