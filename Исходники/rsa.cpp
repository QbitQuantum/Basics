inline std::vector<char> process(Func func, const char * src, size_t len, ::RSA * rsa, int padding, Error & error)
{
    std::vector<char> result(RSA_size(rsa));
    int sz = func(static_cast<int>(len), mstd::pointer_cast<const unsigned char*>(src), mstd::pointer_cast<unsigned char*>(&result[0]), rsa, padding);
    if(error.checkError(sz))
        return std::vector<char>();
    result.resize(sz);
    return result;
}