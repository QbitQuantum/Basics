int main() {
	char buf[100];
	Solution solution;
	while (fgets(buf, 90, stdin) != NULL) {
		buf[strlen(buf)-1] = 0;
		cout << solution.atoi(buf) << endl;
	}
	return 0;
}