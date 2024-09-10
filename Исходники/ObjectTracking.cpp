//Diese Funktion erstellt 3 Fenster und 8 Trackbars
void ObjectTracking::setWindowSettings(){

	namedWindow("Kalibrierung",1);
	namedWindow("Farbe1",1);
	//namedWindow("Trackfenster",1);
	namedWindow("Farbe2",1);

	moveWindow("Farbe1",800,50);
	moveWindow("Farbe2",800,50);
	moveWindow("Kalibrierung",50,50);

	cvCreateTrackbar("LowerH", "Farbe1", &lowerH, 180, NULL);
	cvCreateTrackbar("UpperH", "Farbe1", &upperH, 180, NULL);

	cvCreateTrackbar("LowerS", "Farbe1", &lowerS, 256, NULL);
	cvCreateTrackbar("UpperS", "Farbe1", &upperS, 256, NULL);

	cvCreateTrackbar("LowerV", "Farbe1", &lowerV, 256, NULL);
	cvCreateTrackbar("UpperV", "Farbe1", &upperV, 256, NULL);

	cvCreateTrackbar("LowerH2", "Farbe2", &lowerH2, 180, NULL);
	cvCreateTrackbar("UpperH2", "Farbe2", &upperH2, 180, NULL);

	cvCreateTrackbar("LowerS2", "Farbe2", &lowerS2, 256, NULL);
	cvCreateTrackbar("UpperS2", "Farbe2", &upperS2, 256, NULL);

	cvCreateTrackbar("LowerV2", "Farbe2", &lowerV2, 256, NULL);
	cvCreateTrackbar("UpperV2", "Farbe2", &upperV2, 256, NULL); 

	cvCreateTrackbar("rectangleSizeH", "Kalibrierung", &rHeight, 100, NULL);  
	cvCreateTrackbar("rectangleSizeW", "Kalibrierung", &rWidth, 100, NULL);

	setTrackbarPos("rectangleSizeH", "Kalibrierung", 50);
	setTrackbarPos("rectangleSizeW", "Kalibrierung", 50);
}