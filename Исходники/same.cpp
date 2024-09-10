void cfn_read(std::istream & is, string & dest)
{
    const int BSZ = 1000;

    char buf[BSZ + 1];

    is.read(buf, BSZ);

    auto sz = is.gcount();
    string x(buf, sz);

    dest.swap(x);
}