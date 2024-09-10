	api_return SystemApi::handleGetSystemInfo(ApiRequest& aRequest) {
		aRequest.setResponseBody(getSystemInfo());
		return websocketpp::http::status_code::ok;
	}