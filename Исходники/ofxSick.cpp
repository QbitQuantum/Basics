void ofxSickGrabber::stopRecording(string filename) {
	if(recording) {
		ofLogVerbose("ofxSickGrabber") << "Stopped recording data, saving " << recordedData.size() << " frames to " << filename;
		recording = false;
		ofFile out(filename, ofFile::WriteOnly, true);
		for(int i = 0; i < recordedData.size(); i++) {
			ScanData& cur = recordedData[i];
			writeRaw(out, cur.first.distance);
			writeRaw(out, cur.first.brightness);
			writeRaw(out, cur.second.distance);
			writeRaw(out, cur.second.brightness);
		}
		ofLogVerbose("ofxSickGrabber") << "Done saving data.";
	} else {
		ofLogVerbose("ofxSickGrabber") << "Not recording data, not saving.";
	}
}