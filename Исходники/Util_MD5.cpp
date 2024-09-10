LLBC_MD5::MD5GroupDigest &LLBC_MD5::MD5GroupDigest::operator +=(const LLBC_MD5::MD5GroupDigest &right)
{
    SetA(GetA() + right.GetA());
    SetB(GetB() + right.GetB());
    SetC(GetC() + right.GetC());
    SetD(GetD() + right.GetD());

    return *this;
}