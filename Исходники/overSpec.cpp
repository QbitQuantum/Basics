int compare(const char* const &p1, const char* const &p2)
{
cout << "specialized template" << endl;
    return strcmp(p1, p2);
}