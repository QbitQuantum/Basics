void Predictor::setupFile ( )
{
	char _outFile[100];
	char _dateStr[9];
	char _timeStr[9];

	_strdate( _dateStr);
    _strtime( _timeStr );

	//replaces invalid character for file names
	replaceChar( _dateStr, '/', '-' );
	replaceChar( _timeStr, ':', ' ' );

	//creates the filename for decoded data
	strcpy(_outFile, "Predicted PreLaunch Data for Launch Date ");
	strcat(_outFile, _dateStr);
	strcat(_outFile, " Time ");
	strcat(_outFile, _timeStr);
	strcat(_outFile, ".txt");
	_fpOutPredicted.open ( _outFile, ios::app );

	_fpOutPredicted <<"Callsign: "
					<< _balloon->getCallSign() <<'\n'
					<<"Area of Parachute: "
					<< _balloon->getArea() <<'\n'
					<<"CD of Balloon: "
					<< _balloon->getDragBalloon() <<'\n'
					<<"CD of Parachute: "
					<< _balloon->getDragPara() <<'\n'
					<<"Mass of Balloon: "
					<< _balloon->getMassBalloon() <<'\n'
					<<"Mass of Payload: "
					<< _balloon->getMassPayload() <<'\n'
					<<"Mass of Helium: "
					<< _balloon->getMassHelium() <<'\n'
					<<"Lift in lbs: "
					<< _balloon->getLift() <<'\n'
					<<"Burst Diameter: "
					<< _balloon->getBurst() <<'\n'
					<<"---------------------" <<'\n';

	_fpOutPredicted <<"Air Density Intercept (b): "
					<< _bAir <<'\n'
					<<"Air Density Slope (m): "
					<< _mAir <<'\n'
					<<"Air Density at Launch: "
					<< air( _balloon->getLatestPoint().getAlt() ) <<'\n'
					<<"---------------------" <<'\n';
	_fpOutPredicted <<"Volume Intercept (b): "
					<< _bVol <<'\n'
					<<"Volume Slope (m): "
					<< _mVol <<'\n'
					<<"Volume at Launch: "
					<< volume ( _balloon->getLatestPoint().getAlt() ) <<'\n'
					<<"---------------------" <<'\n';
	_fpOutPredicted <<"\n*********************"
					<<"\nPrelaunch Prediction"
					<<"\n*********************" <<"\n\n";
}