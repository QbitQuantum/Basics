// serveral things need to consider
// 1. positive or negative
// 2. string has invalid character
// 3. out of bounds
// 4.heading or trailing space
int main()
{
    Solution sol;
    string str = "    -2322322";
    string str1 = "9223372036854775809";
    //char str[30] = "    -123243434343434343";
    cout << sol.atoi( str );
    cout << sol.atoi( str1 );
    return 0;
}