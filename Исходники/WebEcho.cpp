	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		HTMLForm form(request, request.stream());

		response.setContentType("text/html");
		response.setChunkedTransferEncoding(true);
        
		std::ostream& ostr = response.send();
        
        URI requestURI(request.getURI());
        
		ostr << "<html><head><title>Echo HTTP Headers and HTML Form Information</title>"
		        "<link rel=\"stylesheet\" href=\"css/styles.css\" type=\"text/css\"/></head><body>"
		        "<div class=\"header\">"
				"<h1 class=\"category\">Open Service Platform</h1>"
				"<h1 class=\"title\">Echo HTTP Headers and HTML Form Information</H1>"
				"</div>"
		        "<div class=\"body\">";
        
		// echo the items available by method
		ostr << "<h2>Request</h2>"
		     << "<ul>"
		     << "<li><b>Method:</b> " << request.getMethod() << "</li>"
             << "<li><b>URI Path:</b> " << requestURI.getPath() << "</li>"
             << "<li><b>URI Query:</b> " << requestURI.getQuery() << "</li>"
             << "<li><b>HTTP Version:</b> " << request.getVersion() << "</li>"
             << "<li><b>Host:</b> " << request.getHost() << "</li>"
             << "<li><b>Content Type:</b> " << request.getContentType() << "</li>"
             << "<li><b>Chunked:</b> " << (request.getChunkedTransferEncoding() ? "true" : "false") << "</li>"
             << "<li><b>Keep Alive:</b> " << (request.getKeepAlive() ? "true" : "false") << "</li>"
             << "<li><b>Transfer Encoding:</b> " << request.getTransferEncoding() << "</li>"
             << "<li><b>Client Address:</b> " << request.clientAddress().toString() << "</li>";

        if (request.hasContentLength())
        {
            ostr << "<li><b>Content Length:</b> " << request.getContentLength64() << "</li>";
        }

		ostr << "</ul>";

        // echo the request headers
        {
            ostr << "<hr>"
                    "<h2>Request Headers</h2><ul>\n";

            NameValueCollection headers;
            NameValueCollection::ConstIterator itr(request.begin());
            NameValueCollection::ConstIterator itrEnd(request.end());
            
            for (; itr != itrEnd; ++itr)
            {
                ostr << "<li><b>" << htmlize(itr->first) << "</b>: " <<  htmlize(itr->second) << "</li>";
            }
            ostr << "</ul>";
        }

        // echo any cookies
        {
            NameValueCollection cookies;
            request.getCookies(cookies);

            if (!cookies.empty())
            {
                ostr << "<hr>";
                ostr << "<h2>Cookies</h2><ul>\n";

                NameValueCollection::ConstIterator itr(cookies.begin());
                NameValueCollection::ConstIterator itrEnd(cookies.end());
                
                for (; itr != itrEnd; ++itr)
                {
                    ostr << "<li><b>" << htmlize(itr->first) << "</b>: " <<  htmlize(itr->second) << "</li>";
                }
                ostr << "</ul>";
            }
        }
        
        // echo any form data (GETs or POSTs)
		if (!form.empty())
		{
            ostr << "<hr>"
			        "<h2>Form Data</h2><ul>\n";

			NameValueCollection::ConstIterator itr(form.begin());
			NameValueCollection::ConstIterator itrEnd(form.end());
			for (; itr != itrEnd; ++itr)
			{
				ostr << "<li><b>" << htmlize(itr->first) << "</b>: " << htmlize(itr->second) << "</li>\n";
			}
			ostr << "</ul>";
		}
        
        ostr << "<hr>"
             << "<h2>Response</h2>"
             << "<ul>"
		     << "<li><b>Status:</b> "  << response.getStatus()  << "</li>"
             << "<li><b>Reason:</b> "  << response.getReason()  << "</li>"
            << "</ul>";
        
        // echo the response headers
        {
            ostr << "<hr>"
                    "<h2>Response Headers</h2><ul>\n";
            
            NameValueCollection headers;
            NameValueCollection::ConstIterator itr(response.begin());
            NameValueCollection::ConstIterator itrEnd(response.end());
            
            for (; itr != itrEnd; ++itr)
            {
                ostr << "<li><b>" << htmlize(itr->first) << "</b>: " <<  htmlize(itr->second) << "</li>";
            }
            ostr << "</ul>";
        }
        
		ostr << "</div></body></html>";
	}