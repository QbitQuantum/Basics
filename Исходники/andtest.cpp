int main() 
{
    string s("Expressions in C++ are composed...");

    string::iterator it = s.begin();
    // convert first word in s to uppercase
    while (it != s.end() && !isspace(*it)) {
        *it = toupper(*it);  
        ++it;
    }
    cout << s << endl;

    return 0;
}