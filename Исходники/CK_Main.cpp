//ARGUMENT PARSER
int argumentparser(int argc, char*argv[]) {
    char* inFile = (char*)"";
    char* outFile = (char*)"cypher.txt";
    char* transFile = (char*)"";
    char* inFileOriginal = inFile;
    bool RemoveOrigin = false;
    bool onTheGo = false;
    bool runSilent= false;
    bool openOutput = false;
    int fileSize = 0;
   
    
    int repeat = 0;

    string password = "";
    bool mode = ENC;
    bool modeGiven = false;
    bool inFileGiven = false;
    bool outFileGiven = true;
    bool passGiven = false;
    bool b64 = false;
    bool print = false;
    bool loud = false;
    bool pDisplacement = false;
    bool header = false;
    bool vectorAlgorithm =false;
    
    
   /* THIS IS THE PUBLISHED VERSION
    * THEREFORE IT IS ONLY NATURAL THAT THE ENCRYPTION PROTOCOL SHOULD BE THE BEST POSSIBLE
    * SO BY DEFAULT IT WILL HAVE THE FOLLOWING VALUES:
    */
    modeGiven = true;
    b64 = true;
    repeat = 2;
    pDisplacement = true;
    header = true;
    vectorAlgorithm =true;
    //////////////////////

    for(int i = 1; i < argc; i++) {

        if (strcmp(argv[i],"--help")==0){
            return 5;
        }

        else if (strcmp(argv[i],"--about")==0){
            return 6;
        }

        else if (strcmp(argv[i],"--easter")==0){
            return 7;
        }

        //CHECK MODE
        else if (strcmp(argv[i],"-e")==0) {
            mode = ENC;
            modeGiven = true;
        }
        else if (strcmp(argv[i],"-encrypt")==0) {
            mode = ENC;
            modeGiven= true;
        }
        else if (strcmp(argv[i],"-d")==0) {
            mode = DEC;
            modeGiven=true;
        }
        else if (strcmp(argv[i],"-decrypt")==0) {
            mode = DEC;
            modeGiven = true;
        }
        //CHECK OPTIONS
        //-Repeat
        else if (strcmp(argv[i],"-r")==0) {
            if (checkParse(argv,argc,i)){
                i++;
                repeat = atoi(argv[i]);
                if (repeat == 0){
                    return 9;
                }
                if (repeat == 1){
                    repeat = 0; //Because 1 causes a bug.
                }
            } else { return 9;}
        }
        //-Loud
        else if (strcmp(argv[i],"-l")==0) {
            loud = true;
        }
        //-Delete Original
        else if (strcmp(argv[i],"-del")==0) {
            RemoveOrigin = true;
        }
        //-Run Background
        else if (strcmp(argv[i],"-s")==0) {
            runSilent= true;
        }
        //-Run Background
        else if (strcmp(argv[i],"-open")==0) {
            openOutput= true;
        }
        //-Base64 Encoding
        else if (strcmp(argv[i],"-b64")==0) {
            if (checkParse(argv,argc,i)){
                i++;
                b64 = (bool) atoi(argv[i]);
            }
        }
        //-Vector Algorithm
        else if (strcmp(argv[i],"-v")==0) {
            if (checkParse(argv,argc,i)){
                i++;
                vectorAlgorithm = (bool) atoi(argv[i]);
            }
        }
        //-Strong
        else if (strcmp(argv[i],"-strong")==0) {
            b64 = true;
            repeat = 2;
            pDisplacement = true;
            header = true;
        }
        //-Password Displacement
        else if (strcmp(argv[i], "-pdis")==0) {
            if (checkParse(argv,argc,i)){
                i++;
                pDisplacement = (bool) atoi(argv[i]);
            }
        }
        //-Header
        else if (strcmp(argv[i], "-h")==0) {
            if (checkParse(argv,argc,i)){
                i++;
                header = (bool) atoi(argv[i]);
            }
        }


        //CHECK FILES
        else if (strcmp(argv[i],"-i")==0) {
            if (onTheGo == false){
                if (checkParse(argv,argc,i)){
                    i++;
                    inFile = argv[i];
                    ifstream testFile(inFile);
                    if (!testFile.fail()){
                        inFileGiven = true;
                        testFile.seekg (0, ios::end);
                        fileSize = testFile.tellg();
                        testFile.close();
                    }
                }
            }
            else {return 8;}
        }
        else if (strcmp(argv[i],"-o")==0) {
            if (checkParse(argv,argc,i)){
                i++;
                outFile = argv[i];

                ifstream testFile(outFile);
                if (testFile){
                    outFileGiven = true;
                }
            }
        }

        //CHECK IF IT IS ON-THE-GO//
        else if (strcmp(argv[i],"-msg")==0) {
            if (inFileGiven == false){
                onTheGo = true;
            }
            else{ return 8;}
        }

        //CHECK PASSWORD
        else if (strcmp(argv[i],"-p")==0) {
            if (argc > (i+1)){
                if (!checkParse(argv,argc,i)){
                    cout << "\nWARNING: Password \""<<argv[i+1] <<"\" is also considered an option.\n"
                         << "Did you forget to write out the password?\n"
                         << "If you didn't, then disregard this message\n"
                         << "Cyphering will we done with the given password.\n\n";
                }
                i++;
                password = argv[i];
                passGiven = true;
            }
        }
        
        else {cout <<"\nParameter: " <<  argv[i] << " not recognized.\n"; return 10;}
    }
    
    //ON THE GO ENCRYPTION/DECRYPTION
    if (onTheGo == true){
            string clearText = " ";
            cout << "\nWrite your message: \n\n";
            getline( cin, clearText );
            //Create the TempFile
            inFile = (char*) "TempCKTFile.ckt";
            inFileGiven = true;
            //Fill the File with the cleartext
            fstream clearFile;
            clearFile.open(inFile,fstream::out);
            clearFile << clearText;
            clearFile.close();
            //Makesure it is Erased Eventually.
            RemoveOrigin = true;
        }

    //Print Variable - Do we want to print the enc/dec process?
    //if (loud == true || onTheGo == true){ print = true;}
    print = loud;
        
    //If everything is parsed and correct then lets enc/dec!  
    if (modeGiven && inFileGiven && outFileGiven && passGiven) {
        
        //IF GO SILENT, THEN DISAPPEAR
        if (runSilent){
            stealth();
        }
        
        
        //ENCRYPTION MODE
        if (mode == ENC) {
            
            //Copy Original File - Precaution in case somthing goes wrong. We don't want to damage the original.
            inFileOriginal = inFile;
            inFile = fileCopy(inFile);
            
            Encryptor message;
            
            for (int i = 0; i<=repeat; i++) {

                //REPEAT, SWITCHING FILES
                if (i != 0){
                    transFile = outFile;
                    outFile = inFile;
                    inFile = transFile;
                }
                
                message.encrypt(password, inFile, outFile, true, b64, pDisplacement,vectorAlgorithm, print,header);
            }
            
        }
        else if (mode == DEC) {
            
            //Copy Original File - Precaution in case somthing goes wrong. We don't want to damage the original.
            inFileOriginal = inFile;
            inFile = fileCopy(inFile);
            
            Decryptor message;
            
            for (int i = 0; i<=repeat; i++) {
            
                if (i != 0){
                    transFile = outFile;
                    outFile = inFile;
                    inFile = transFile;
                }
                
                message.decrypt(password, inFile, outFile, true, b64, pDisplacement,vectorAlgorithm, print,header);
            }
        }
        
        if (openOutput){
            /*Seems overly complicated just to open a simple file with the Commandline
              But it turns out that the difference between cmd "text.txt" and cmd "start text.txt"
              Is that without the "start" the program will wait for the file to finish executing before continuing.
              With the "start" the program will simply start another detached process. -12:22AM 5/19/2012 (ima gonna go to sleep now)
            */
            stringstream tempStream;
            string cmd;
            tempStream << "start " << outFile << endl;
            getline(tempStream,cmd);
            system(cmd.c_str());
        }
        
        if (RemoveOrigin){
            if (remove(inFileOriginal) != 0){cout << "Couldn't delete original file"<<endl;}
        }
        
    } 
    else if (modeGiven !=true){ return 3;}
    else if (inFileGiven !=true){return 2;}
    else if (passGiven !=true) {return 4;}
    else {return 1;}

    //Loud Printing of Variables for Debuggin Purpose
    if (loud) {
        cout << "<>-----------<>\n"
             << "  Mode: " <<mode << endl
             << "  In File: " << inFileOriginal << endl
             << "  FileSize: " << setw(1) << setprecision(2) << fixed << fileSize << " Bytes" << endl
             << "  Out File: " << outFile << endl
             << "  Password: "******"  Repeats: " << repeat << endl
             << "  Base64: " << (bool) b64 <<endl
             << "  Password Displacement: " <<(bool) pDisplacement<< endl
             << "  Vector Algorithm: " << (bool) vectorAlgorithm << endl
             << "  Delete Original: " << (bool)RemoveOrigin << endl
             << "  Open Output File: " << (bool)openOutput << endl
             << "  Loud : " << loud << "\n\n";

    }

    return 0;
}