void FormRenderer::PrintFormBegin(std::ostream &reply, Context &context, const ROAnything &config)
{
	reply << "<FORM ACTION=\"";
	static Renderer *r = Renderer::FindRenderer("URLRenderer");
	String actionURL; // Save the URL for Later use
	{
		OStringStream os(&actionURL);
		r->RenderAll(os, context, config);
	}
	reply << actionURL;

	String method;
	ROAnything methodConfig;
	if ( config.LookupPath(methodConfig, "Method")) {
		RenderOnString(method, context, methodConfig);
	} else {
		method = "POST";
	}
	reply << "\" METHOD=\"" << method << "\"";

	if (config.IsDefined("EncType")) { // optimize with FindIndex if required
		reply << " ENCTYPE=\"" << config["EncType"].AsCharPtr("???") << "\"";
	}

	if (config.IsDefined("Target")) {
		reply << " TARGET=\"" << config["Target"].AsCharPtr("_self") << "\"";
	}

	PrintOptions3(reply, context, config);

	reply << ">";

	bool useBaseURL = (context.Lookup("UseBaseURL", 0L) != 0);

	if ( !useBaseURL && (method == "GET") ) {
		long pos = actionURL.StrChr('=');
		reply << "<INPUT TYPE=HIDDEN NAME=\"X\" VALUE=\"" << actionURL.SubString(pos + 1) << "\">";
	}
}