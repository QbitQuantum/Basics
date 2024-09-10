std::string OAuthPrivate::baseString(const std::string & method, const std::string & url, const std::string & paramStr){

	std::string baseStr = toUpper(method) + "&" + Helper::urlencode(url);
	baseStr += "&" + Helper::urlencode(paramStr);
    return baseStr;
}