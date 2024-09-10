	virtual void onHttpRequestContentCompleted(HttpRequest & request, AutoRef<DataSink> sink, HttpResponse & response) {
		cout << " ** path : " << request.getHeader().getPart2() << endl;
		if (request.getPath() == "/device.xml") {
			response.setStatus(200);
			response.setContentType("text/xml");
			setFixedTransfer(response, dd(_udn));
		} else if (request.getHeader().getPart2() == "/scpd.xml?udn=" + _udn + "&serviceType=" + dummy) {
			response.setStatus(200);
			response.setContentType("text/xml");
			setFixedTransfer(response, scpd());
		} else {
			response.setStatus(404);
		}
	}