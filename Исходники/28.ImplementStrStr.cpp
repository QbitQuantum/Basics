void testCase_strStr()
{
    string haystack = "hello world, i am Marin Young";
    string s1 = "hello";
    string s2 = "world";
    string s3 = "i";
    string s4 = "am";
    string s5 = "Marin";
    string s6 = "Young";

    cout<<strStr(haystack, s1)<<endl;
    cout<<strStr(haystack, s2)<<endl;
    cout<<strStr(haystack, s3)<<endl;
    cout<<strStr(haystack, s4)<<endl;
    cout<<strStr(haystack, s5)<<endl;
    cout<<strStr(haystack, s6)<<endl;
}