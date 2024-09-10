void Downcase(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](char c){return ToLower(c);});
}