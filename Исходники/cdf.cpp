double last_in_line(const string& str)
{
    typedef string::const_iterator iter;
    vector<string> ret;
    
    iter i = str.begin();
    while (i != str.end()) {
        i = find_if(i, str.end(), not_space);
        iter j = find_if(i, str.end(), space);
        
        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }
    return atof(ret[ret.size() - 1].c_str());
}