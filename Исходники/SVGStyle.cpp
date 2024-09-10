void SVGStyle::parseNode(xmlNodePtr node, map<string, SVGGradient*> &gradients) {
	AttributeParser parser;
	parser.parseNode(node);

	const map<string, vector<string> > &attributes = parser.getAttributes();
	for(map<string, vector<string> >::const_iterator iter = attributes.begin(); iter != attributes.end(); iter++) {
		const string &attribute = (*iter).first;
		const vector<string> &values = (*iter).second;



		for (vector<string>::const_iterator iterValue = values.begin (); iterValue != values.end (); iterValue ++)
		{
			const string &valueStr = (*iterValue);
			const char *value = valueStr.c_str ();

			bool fParsed = true;
			
			if(attribute == "stroke") {
				SVGGradient *gradient = getGradient(valueStr, gradients);
				if(gradient) {
					strokeGradient = gradient;
					_hasStrokeGradient = true;
					_hasStroke = true;
					fParsed = true;
				} else {
					fParsed = setStrokeColor(value);
				}
			} else if(attribute == "stroke-width") {
				setStrokeWidth(atof(value));
			} else if(attribute == "stroke-opacity") {
				setStrokeAlpha(atof(value));
			} else if(attribute == "stroke-linecap") {
				fParsed = setLineCap(value);
			} else if(attribute == "stroke-linejoin") {
				fParsed = setLineJoin(value);
			} else if(attribute == "stroke-miterlimit") {
				setMiterLimit(atof(value));
			} else if(attribute == "fill") {
				SVGGradient *gradient = getGradient(valueStr, gradients);
				if(gradient) {
					fillGradient = gradient;
					_hasFillGradient = true;
					_hasFill = true;
					fParsed = true;
				} else {
					fParsed = setFillColor(value);
				}
			} else if(attribute == "fill-opacity") {
				setFillAlpha(atof(value));
			} else if(attribute == "opacity") {
				setOpacity(atof(value));
			}

			if (fParsed) {
				break;
			}
		}
	}
}