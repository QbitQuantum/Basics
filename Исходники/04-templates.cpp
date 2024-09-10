void t01_url(){
	INIT_LOCAL();
	
	Onion::Onion o;

	// Create an empty url handler
	Onion::Url url(o);
	
	url.add("", [](Onion::Request &req, Onion::Response &res){
		return Onion::render_to_response(_04_templates_html, std::map<std::string,std::string>{{"test","ok"}} , res);
	});
	
	o.listen();
	
	END_LOCAL();
}