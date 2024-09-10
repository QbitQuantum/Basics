/**
 * Read sto file.
 *
 * @param aFilename name of sto file.
 */
void MarkerData::readStoFile(const string& aFileName)
{

	if (aFileName.empty())
		throw Exception("MarkerData.readStoFile: ERROR- Marker file name is empty",__FILE__,__LINE__);

    Storage store(aFileName);

    // populate map between marker names and column numbers 
    std::map<int, std::string>  markerIndices;
    buildMarkerMap(store, markerIndices);

    if (markerIndices.size()==0){
        throw Exception("MarkerData.readStoFile: ERROR- No markers were identified. Markers should appear on consecutive columns as Marker1.x Marker1.y Marker1.z Marker2.x... etc.",__FILE__,__LINE__);
    }
    std::map<int, std::string>::iterator iter;

    for (iter = markerIndices.begin(); iter != markerIndices.end(); iter++) {
        SimTK::String markerNameWithSuffix = iter->second;
        size_t dotIndex = markerNameWithSuffix.toLower().find_last_of(".x");
        SimTK::String candidateMarkerName = markerNameWithSuffix.substr(0, dotIndex-1);
        _markerNames.append(candidateMarkerName);
    }
    // use map to populate data for MarkerData header
    _numMarkers = (int) markerIndices.size();
    _numFrames = store.getSize();
    _firstFrameNumber = 1;
	_dataRate = 250;
	_cameraRate = 250;
	_originalDataRate = 250;
	_originalStartFrame = 1;
	_originalNumFrames = _numFrames;
	_fileName = aFileName;
	_units = Units(Units::Meters);

    double time;
    int sz = store.getSize();
    for (int i=0; i < sz; i++){
        StateVector* nextRow = store.getStateVector(i);
        time = nextRow->getTime();
        int frameNum = i+1;
        MarkerFrame *frame = new MarkerFrame(_numMarkers, frameNum, time, _units);
        const Array<double>& rowData = nextRow->getData();
        // Cycle thru map and add Marker coordinates to the frame. Same order as header.
        for (iter = markerIndices.begin(); iter != markerIndices.end(); iter++) {
            int startIndex = iter->first; // startIndex includes time but data doesn't!
            frame->addMarker(SimTK::Vec3(rowData[startIndex-1], rowData[startIndex], rowData[startIndex+1]));
        }
        _frames.append(frame);
   }
   
}