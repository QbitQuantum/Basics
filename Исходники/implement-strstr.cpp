void test(){
    //char str[] = "abcdabaabetffsdafdsa";
    //char p[] = "abet";
    char str[] = "bbbbababbbaabbba";
    char p[] = "abb";
    //char str[] = "abab";
    //char p[] = "ab";
    Solution sol;
    Solution_old sol_old;
    cout<<sol.strStr(str,p)<<endl;
    cout<<sol_old.strStr(str,p)<<endl;
}