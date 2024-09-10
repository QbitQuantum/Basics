void WebStudioModule::paint(WebPage *page, HttpRequest &request) {
	String p2 = request.header.GET.getValue("p2");
	if (p2 == "") paintIndex(page, request);
	else if (p2 == "site") paintSite(page, request);
	else if (p2 == "mobile") paintMobile(page, request);
	else if (p2 == "desktop") paintDesktop(page, request);
	else if (p2 == "seo") paintSEO(page, request);
	else if (p2 == "articles") paintArticles(page, request);
	else if (p2 == "outsourcing") paintOutsourcing(page, request);
}