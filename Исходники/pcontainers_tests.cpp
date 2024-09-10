void write_random_elements(const int n, Random<int> rand, orb::cstring& prefix, StlSIMap& map)
{
    int i = 0;
    while(i++ < n)
    {
        int r = rand.rand();
        std::string str = prefix + std::to_string(r);
        map[str] = r;
    }
}