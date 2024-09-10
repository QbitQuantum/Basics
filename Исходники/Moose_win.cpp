/** I'm not sure what this does really --mxcl */
std::wstring
Moose::fixStr(const std::wstring& str)
{
    std::wstring ret;

    if (str.length() == 0) return str;

    // Mac strings store the length in the first char of the string:
    size_t len = (size_t)str[0];
    ret = str.substr(1);
    if(len > 0 && len < ret.length())
    {
        ret = ret.substr(0,len);
    }
    return ret;
}