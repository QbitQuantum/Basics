void FrameAnalyser::analyseHorizont(string filename, string label, bool print)
{

    HorizontDetector hDetector(1, 180, 100);

    vector<Horizont> horizontVector;
    fs.open(label, FileStorage::READ);
    if (!fs.isOpened())
        cout << "Ahhhhhhhhhh! Kann datei nicht öffnen: " << label << endl;
    else
        fs["HorizontVector"] >> horizontVector;

    ausgabe.open(filename.c_str(), ios::out);

    int index = 0;

    int frames = 0;
    int moeglich = 0;
    int richtig = 0;
    double abweichungr = 0;
    double abweichungf = 0;
    int entfernung = 0;
    int varianz = 0;
    double zeit = 0;


    for (int var = myStack->size()-1; var > 0; var--, index++) {

        clock_t start, end;
        start = clock();
        if(var < myStack->size()-1){
            Horizont a = myStack->getFrame(var+1).getHorizont();
            hDetector.getStableHorizont(myStack->getFrame(var),a);

            myStack->getFrame(var).calcFlow(myStack->getFrame(var+1));
        }else{
            hDetector.getStableHorizont(myStack->getFrame(var));
        }
        end = clock();

        Horizont b = myStack->getFrame(var).getHorizont();
        Horizont c = horizontVector[index];

        frames++;
        if(!c.empty()){
            moeglich++;
            if(b.dAngle(c) <=2 && b.dPoint(c) <= 100){
                richtig++;
                abweichungr += b.dAngle(c);
            }else
                abweichungf += b.dAngle(c);
            varianz += b.compareHorizont(c);
            entfernung += b.dPoint(c);
            zeit += (end-start);///CLOCKS_PER_SEC;
        }


        ausgabe << b.dAngle(c) << "\t";
        ausgabe << b.dPoint(c) << "\t";
        ausgabe << b.dCenter() << "\t";
        ausgabe << b.compareHorizont(c) << "\t";
        ausgabe << b.angle << "\t";
        ausgabe << c.angle << "\t";
        ausgabe << (end - start) << "\t";
        ausgabe << myStack->getFrame(var).getMean().x << "\t";
        ausgabe << myStack->getFrame(var).getMean().y << "\t";
        if(myStack->getFrame(var).hasLog()){
            ausgabe << myStack->getFrame(var).getLog().kompass << "\t";
            ausgabe << myStack->getFrame(var).getLog().kraengung << "\t";
            ausgabe << myStack->getFrame(var).getLog().accY << "\t";
            ausgabe << myStack->getFrame(var).getLog().gyroY;
        }
        ausgabe << endl;

        if(print){
            Mat im = myStack->getFrame(var).getFrame();
            line(im, b.p1, b.p2, Scalar(0, 0, 255), 1, 8);
            line(im, c.p1, c.p2, Scalar(0, 255, 0), 1, 8);

            ostringstream oss;
            oss << b.dAngle(c) << " - " << b.dPoint(c ) << " - " << b.compareHorizont(c) << " - " << b.distance(c);
            string msg = oss.str();
            int baseLine = 0;
            Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
            Point textOrigin(im.cols - 2*textSize.width - 10, im.rows - 2*baseLine - 10);
            putText( im, msg, textOrigin, 1, 1, Scalar(255,255,255));

            imshow("Ausgabe",im);
            waitKey(0);
        }

    }
    if (print) {
        destroyWindow("Ausgabe");
    }
    ausgabe.close();

    double prozent = (double)(100/frames) * richtig;

    cout << "Frames: " << frames << endl;
    cout << "Möglich: " << moeglich << endl;
    cout << "Erkannt: " << richtig << " , Prozent: " << prozent << endl;
    cout << "Abweichung R: " << abweichungr/moeglich << endl;
    cout << "Abweichung F: " << abweichungf/moeglich << endl;
    cout << "Entfernung: " << entfernung/moeglich << endl;
    cout << "Varianz: " << varianz/moeglich << endl;
    cout << "Clocks per second: " << zeit/moeglich << endl;
    cout << "Millisekunden: " << zeit/moeglich/CLOCKS_PER_SEC*1000 << endl;
}