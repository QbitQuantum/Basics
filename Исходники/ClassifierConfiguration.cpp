void ClassifierConfiguration::entryPoint(){

    //_begin = time(0);
    if(!fileExists(outputFilename)){
        buildClassifier();
    }else{
        logln("Output already exists: " + outputFilename);
    }
    //_end = time(0);

    ClassifierOutput *clOut = handleOutput();

    writeToCSV(clOut);


    return terminateThread();
}