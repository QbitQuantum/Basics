	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		response.setStatusAndReason(HTTPResponse::HTTP_NOT_FOUND);
		response.send();
	}