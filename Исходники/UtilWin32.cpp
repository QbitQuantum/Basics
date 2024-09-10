std::string getEnv(const std::string& env, const std::string& defaultValue) {
	return ws2s(getEnv(s2ws(env), s2ws(defaultValue)));
}