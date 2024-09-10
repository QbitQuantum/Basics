void OculusSocketServerApp::setup()
{
    mServerPort = 9005;

    string configPath = getAppPath().string() + "/config.json";
    
    if(fs::exists(configPath)) {
        JsonTree::ParseOptions options;
        options.ignoreErrors(true);

        try{
            JsonTree config = JsonTree( loadFile( configPath ));
            
            for( JsonTree::ConstIter cIt = config.begin(); cIt != config.end(); ++cIt )
            {
                if( "port" == (*cIt).getKey()){
                    mServerPort = std::stoi((*cIt).getValue());
                    console() << "Port found: " << mServerPort << std::endl;
                }
            }
            
        } catch(JsonTree::Exception ex){
            console() << "Unable to parse config file." << std::endl;
        }
    } else {
        console() << "No config file found." << std::endl;
    }

    mOculusConnected = false;
    mSocketConnected = false;
    
    mServer.addConnectCallback( &OculusSocketServerApp::onConnect, this );
	mServer.addDisconnectCallback( &OculusSocketServerApp::onDisconnect, this );
   
    mServer.listen(mServerPort);
    mOculusVR = Oculus::create();
    
    mBackgroundTexture = gl::Texture( loadImage( loadResource( RES_BACKGROUND_TEX ) ) );
}