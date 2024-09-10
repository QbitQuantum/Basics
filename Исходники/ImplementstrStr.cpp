int main(){
    char str[100] = "mississippi";
    char pat[100] = "issip";
    Solution solution;
    char* res = solution.strStr(str, pat);
    cout << res << endl;
    return 0;
}