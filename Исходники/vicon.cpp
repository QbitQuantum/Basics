void initialize_VICON( void )
{
	int trying = 0;

	cout << " Connecting to Giganet......" << endl;


	// ============================= Connect to Giganet (Vicon motion systems) ============================= 
	while( !MyClient.IsConnected().Connected )
	{
		if(trying++ > 3)
			break;

		Output_Connect _Output_Connect = MyClient.Connect( "localhost:801" );
		Sleep(200);
	}

	if(trying > 3)
		return;

	Output_EnableMarkerData          _Output_EnableMarkerData          = MyClient.EnableMarkerData();
	Output_EnableUnlabeledMarkerData _Output_EnableUnlabeledMarkerData = MyClient.EnableUnlabeledMarkerData();
	Output_EnableDeviceData          _Output_EnableDeviceData          = MyClient.EnableDeviceData();


	Output_SetStreamMode _Output_SetStreamMode = MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPull );

	cout << " Giganet successfully connected." << endl << endl;

	/// Wait until frame is arrived.
	while( MyClient.GetFrame().Result != Result::Success );

	/// Get number of object shown in vicon
	unsigned int SubjectCount = MyClient.GetSubjectCount().SubjectCount;

	cout << "[NOTICE] " << SubjectCount << " objects found" << endl;

	for( unsigned int SubjectIndex = 0 ; SubjectIndex < SubjectCount ; ++SubjectIndex )
	{
		cout << "Object name : " << MyClient.GetSubjectName(SubjectIndex).SubjectName << endl;

		if(MyClient.GetSubjectName(SubjectIndex).SubjectName == "pitta")
		{
			cout << "Pitta found ID = " << SubjectIndex << endl;
			pitta_obj_id = SubjectIndex;
			pitta_name = MyClient.GetSubjectName(SubjectIndex).SubjectName;
		}
	}
}