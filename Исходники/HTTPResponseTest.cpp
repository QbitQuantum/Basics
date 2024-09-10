void HTTPResponseTest::testRead3()
{
	std::string s("HTTP/1.1 200 \r\nContent-Length: 0\r\n\r\n");
	std::istringstream istr(s);
	HTTPResponse response;
	response.read(istr);
	assert (response.getVersion() == HTTPMessage::HTTP_1_1);
	assert (response.getStatus() == HTTPResponse::HTTP_OK);
	assert (response.getReason() == "");
	assert (response.size() == 1);
	assert (response.getContentLength() == 0);
	assert (istr.get() == -1);
}