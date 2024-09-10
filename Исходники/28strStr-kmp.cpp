int main(){
	Solution sol;
	string haystack = "mississippi";
	string needle = "issip";
	int indx = sol.strStr(haystack,needle);
	cout << haystack << ","<<needle<<","<<indx << endl;
	return 1;
}