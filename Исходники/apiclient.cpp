void ApiClient::GetObjects(const String& pluralType, const ObjectsCompletionCallback& callback,
    const std::vector<String>& names, const std::vector<String>& attrs, const std::vector<String>& joins, bool all_joins) const
{
	Url::Ptr url = new Url();
	url->SetScheme("https");
	url->SetHost(m_Connection->GetHost());
	url->SetPort(m_Connection->GetPort());

	std::vector<String> path;
	path.push_back("v1");
	path.push_back("objects");
	path.push_back(pluralType);
	url->SetPath(path);

	std::map<String, std::vector<String> > params;

	for (const String& name : names) {
		params[pluralType.ToLower()].push_back(name);
	}

	for (const String& attr : attrs) {
		params["attrs"].push_back(attr);
	}

	for (const String& join : joins) {
		params["joins"].push_back(join);
	}

	params["all_joins"].push_back(all_joins ? "1" : "0");

	url->SetQuery(params);

	try {
		boost::shared_ptr<HttpRequest> req = m_Connection->NewRequest();
		req->RequestMethod = "GET";
		req->RequestUrl = url;
		req->AddHeader("Authorization", "Basic " + Base64::Encode(m_User + ":" + m_Password));
		req->AddHeader("Accept", "application/json");
		m_Connection->SubmitRequest(req, boost::bind(ObjectsHttpCompletionCallback, _1, _2, callback));
	} catch (const std::exception& ex) {
		callback(boost::current_exception(), std::vector<ApiObject::Ptr>());
	}
}