RecordingDevice::ReturnCode RecordingDevice::ResolveDevice()
{
    ReturnCode result = OK;
    if(mName.empty())
    {
        result = NO_DEVICE;
    }
    mTrackCount = 0;

    CosNaming::Name name;
    name.length(3); 
    name[0].id = CORBA::string_dup("ProductionAutomation");
    name[1].id = CORBA::string_dup("RecordingDevices");
    name[2].id = CORBA::string_dup(mName.c_str());

    CORBA::Object_var obj;
    if(OK == result)
    {
        obj = CorbaUtil::Instance()->ResolveObject(name);
    }

    if(CORBA::is_nil(obj))
    {
        result = NO_DEVICE;
    }

    if(OK == result)
    {
        try
        {
            mRecorder = ProdAuto::Recorder::_narrow(obj);
        }
        catch(const CORBA::Exception &)
        {
            result = NO_DEVICE;
        }
    }

    // Find out how many recording tracks there are
    ProdAuto::TrackList_var track_list;
    if(OK == result)
    {
        try
        {
            track_list = mRecorder->Tracks();
            mTrackCount = track_list->length();
        }
        catch(const CORBA::Exception &)
        {
            result = NO_DEVICE;
        }
    }

    return result;
}