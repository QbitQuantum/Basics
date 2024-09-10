void writeContinuosDataFile()
{
    ofstream outputfile;
    outputfile.open("data.dat");

    outputfile << "Yaw: " << toDegrees(headEyeCoords.getYaw()) << endl <<"Pitch: " << toDegrees(headEyeCoords.getPitch()) << endl;
    outputfile << "EyeLeft: " <<  eyeLeft.transpose() << endl;
    outputfile << "EyeRight: " << eyeRight.transpose() << endl << endl;
    outputfile << "Factors:" << endl;
    for (map<string,double>::iterator iter=factors.begin(); iter!=factors.end(); ++iter)
    {
        outputfile << "\t\t" << iter->first << "= " << iter->second << endl;
    }
    outputfile << "Trials done: " << trialNumber << endl;
	if (trialNumber!=0)
		outputfile << "Last response (right=0, left=1): " << response << endl;
    outputfile.clear();
    outputfile.seekp(0,ios::beg);
}