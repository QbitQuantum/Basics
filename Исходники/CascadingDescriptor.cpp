	void CascadingDescriptor::initializeCascadingDescriptor() {
		typeSet.insert("CascadingDescriptor");

		id = "";
		explicitDuration = NaN();
		playerName = "";
		repetitions = 0;
		freeze = false;
		region = NULL;
		formatterRegion = NULL;

		focusIndex = "";
		moveUp = "";
		moveDown = "";
		moveLeft = "";
		moveRight = "";

		focusSrc = "";
		selectionSrc = "";
		focusBorderColor = NULL;
		selBorderColor = NULL;
		focusBorderWidth = 0;
		focusBorderTransparency = NaN();
		inputTransitions = new vector<Transition*>;
		outputTransitions = new vector<Transition*>;
		parameters = new map<string, string>;
		descriptors = new vector<GenericDescriptor*>;
		unsolvedDescriptors = new vector<GenericDescriptor*>;
	}