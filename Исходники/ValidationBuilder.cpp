void ValidationBuilder::addOutputArc(const std::string& transition,
									 const std::string& place,
									 int weight){
	_outputArcs.push_back(Arc(transition, place));
	if(weight < 0){
		string msg = "Weight is " + int2string(weight)
					 + " is less than zero";
		_errors.push_back(ValidationError(transition, place, msg));
	}
}