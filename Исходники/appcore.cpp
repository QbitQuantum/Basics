//--------------------------------------------------------------
void AppCore::setup(const int numOutChannels, const int numInChannels,
                    const int sampleRate, const int ticksPerBuffer) {

	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	//ofSetLogLevel(OF_LOG_VERBOSE);
    
	// double check where we are ...
	cout << ofFilePath::getCurrentWorkingDirectory() << endl;

    //----------------------------------- PD START-------------------------------------------
	if(!pd.init(numOutChannels, numInChannels, sampleRate, ticksPerBuffer)) {
		OF_EXIT_APP(1);
	}
    Externals::setup();
	midiChan = 1; // midi channels are 1-16

	// subscribe to receive source names
	pd.subscribe("toOf");
	pd.subscribe("env");

    pd.addReceiver(*this);   // automatically receives from all subscribed sources
	pd.ignore(*this, "env"); // don't receive from "env"
	
	pd.addMidiReceiver(*this);  // automatically receives from all channels

	pd.addToSearchPath("pd/abs");

	pd.start();
    //Patch patch = pd.openPatch("pd/somename.pd");
    //cout << patch << endl;
    //----------------------------------- PD END-------------------------------------------
    
    //----------------------------------- KINECT START -------------------------------------------
    kinect.listDevices();
    kinect.init();
    kinect.open("A00365917784047A");
    kinect.setCameraTiltAngle(0);
    grayImage.allocate(kinect.width, kinect.height);

    kinect1.init();
    kinect1.open("A00364A11700045A");
    kinect1.setCameraTiltAngle(0);
    grayImage1.allocate(kinect1.width, kinect1.height);
    
    bothKinects.allocate(kinect.height*2, kinect.width);
    combinedVideo = (unsigned char*)malloc(640 * 480 * 2 * sizeof(unsigned char*));
    
    blobs.resize(100);
    blobCenterX.resize(100);
    blobCenterXmap.resize(100);
    blobCenterY.resize(100);
    blobCenterYmap.resize(100);
    
    //----------------------------------- KINECT END -------------------------------------------

    // Setup OSC Sender
    sender.setup(HOST, PORT);
    
    allPipes = new ofPipe*[TUBE_NUM]; // an array of pointers for the objects
    persons = new ofPerson*[PERSON_NUM];
    
    //the string is printed at the top of the app
    //to give the user some feedback
    message = "loading data.xml";
    
    //we load our data file
    
    if( XML.loadFile("data.xml") ){
        message = "data.xml loaded!";
    }else{
        message = "unable to load data.xml check data/ folder";
    }
    
    XML.pushTag("document");
    newXML.addTag("document");
    newXML.pushTag("document");
    
    for(int i=0; i<TUBE_NUM; i++){
        
        XML.pushTag("tube",i);
        
        float x = XML.getValue("y",0.0);
        float y = XML.getValue("x",0.0);
        
        // rotate
        float angle = ofDegToRad(-20);
        float rX = (x*cos(angle) - y*sin(angle));
        float rY = (x*sin(angle) + y*cos(angle));
        
        
        // map to the of window size
        float mult = 6;
        x = (rX * mult + ofGetWidth() / 2) - 50;
        y = rY * mult + ofGetHeight() / 2;
        
        float radius = XML.getValue("diameter",0.0 ) / 1.8;
        float length = XML.getValue("length",0.0 );
        float height= XML.getValue("height",0.0);
        float frequency = 342 / ((length*2)/100);
        int idNum = XML.getValue("num",0);
        int element = XML.getValue("element",0 );
        int open = XML.getValue("oc",0 );
        
        allPipes[i] = new ofPipe(x,y,radius,length,height,frequency, idNum, element, open);
        
        newXML.addTag("tube");
        newXML.pushTag("tube", i);
        newXML.addValue("num", idNum);
        newXML.addValue("length", length);
        newXML.addValue("height", height);
        newXML.addValue("diameter", radius);
        newXML.addValue("x", ofMap(x, 0, ofGetWidth(), 0, 1));
        newXML.addValue("y", ofMap(y, 0, ofGetHeight(), 0, 1));
        newXML.addValue("element", element);
        newXML.addValue("oc", open);
        
        XML.popTag();
        newXML.popTag();
    }
    
    newXML.saveFile("newXML.xml");
    
    // load the PD patches and create the people
    for(int i = 0; i<PERSON_NUM; i++){
        //patches[i] = pd.openPatch("pd/main.pd");
        persons[i] = new ofPerson(0.0,0.0,0.0, i);
    }
    // load a separate patch for the mouse
    //mousePatch = pd.openPatch("pd/main.pd");
    mPerson = new ofPerson(0.0,0.0,0.0,0);
    outputState=false;
}