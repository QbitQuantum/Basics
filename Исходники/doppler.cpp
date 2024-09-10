int main(int argc, char *argv[])
{
    double velSource;
    double velReciver;
    double distX;
    double distY;
    double velRelativeX;
    double totalTime;
    unsigned long numSamples;

    if ( argc < 7 || argc > 8 ) {
        std::cout<<"\n\n\n****Doppler shift example*****\n\n";
        std::cout<<"Will produce output assuming source is travelling towards\n";
        std::cout<<"and then past receiver in straight line\n\n";
        std::cout<<"Will start simulation at d0=-D and end at d1=+D\n";
        std::cout<<"Simulation time = 2D/(relative velocity)\n";
        std::cout<<"input will be looped for duration of simulation\n\n";
        std::cout<< "usage: doppler [spd src (m/s)] [spd recv (m/s)] [distX (m)] [distY (m)] [input file (wav)] [output file (wav)] [0/1: no mix/mix]\n";
        std::cout<< "NOTE: if source and receiver are diverging, fix simulation duration to 5s\n";
        return 0;
    }
    else {
        std::cout<<"INPUT OK...\n parsed values:";
        velSource = atof(argv[1]);
        velReciver = atof(argv[2]);
        distX = atof(argv[3]);
        distY = atof(argv[4]);
        //visual check to make sure input was parsed properly
        std::cout<<"velSource=" << velSource << " velReciver=" << velReciver << " distX=" << distX << " distY=" <<distY << " if=" << argv[5] << "\n\n";

        velRelativeX = velSource-velReciver;

        double distAbs = sqrt(distX*distX + distY*distY);

        totalTime = 2*distX/velRelativeX; //total simulation time, if not diverging/constant

        //do some basic input checking:
        if ((velSource - velReciver) <= 0) {
            //this is for the "not so interesting" case where
            //the source and receiver will never "cross"
            // will just have a boring, constant frequency...
            //so we force a fixed simulation time here.
            std::cout<<"DIVERGING! clamping time to 5 seconds\n";
            totalTime = 5.0;
        }
        numSamples = totalTime * SAMPLE_RATE;
        std::cout<<"relative speedX = " << velRelativeX<<"; simulation time = " << totalTime<< "s; numSamples = "<< numSamples<<"\n";
    }

    Stk::setSampleRate( SAMPLE_RATE );

    //file i/o
    FileWvOut outputFile;
    FileLoop inputLoop;

    try {
        outputFile.openFile( argv[6], 1, FileWrite::FILE_WAV, Stk::STK_SINT16 );
        inputLoop.openFile(argv[5]);
    }
    catch (StkError &) {
        exit( 1 );
    }

    //the doppler effect's frequency shift is implemented using a delay line whose write
    // pointer is incremented sample by sample and read using a variable delay.
    DelayL delay(1.0, DELAY_SIZE);

    //initialize: since read pointer can increment faster than write pointer, we should
    // fill up the delay line with initial values for continuity's sake...
    // since our input is a loop, it doesn't matter too much where the "starting" point
    // in the audio sample is...
    for (int i=0; i<DELAY_SIZE; i++) {
        delay.tick(inputLoop.tick());
    }

    stk::StkFrames frames( numSamples, 1);
    double readPtr = 0;
    unsigned int writePtr = 0;
    double g=0;

    // set initial locations
    double xSrcCurr = 0, xSrcPrev = 0;
    double xRcvCurr = distX, xRcvPrev = distX;
    double dT = totalTime/numSamples;

    for (int i=0; i<numSamples; i++) {

        //basic kinematic model for estimating current relative speed:
        double timeElapsed = (double)totalTime*i/numSamples;
        xSrcCurr+=dT*velSource;
        xRcvCurr+=dT*velReciver;

        //distY is constant!

        //velRelative = ( sqrt((xSrcCurr-xSrcPrev)*(xSrcCurr-xSrcPrev)+distY*distY) +
        //               sqrt((xRcvPrev-xRcvCurr)*(-xRcvCurr)+distY*distY) ) / dT;

        //double velRelative = ( (xRcvCurr-xSrcCurr) - (xRcvPrev-xSrcPrev) ) / dT;


        //bit of a hack to get the right behaviour, as my quickly cobbled together model
        // was bit sloppy when it came to managing the sign
        double velRelative = -fabs( sqrt((xRcvCurr-xSrcCurr)*(xRcvCurr-xSrcCurr)+distY*distY)
                                    - sqrt((xRcvPrev-xSrcPrev)*(xRcvPrev-xSrcPrev)+distY*distY) ) / dT;

        if (xRcvCurr < xSrcCurr)
            velRelative = -velRelative;

        //std::cout <<xSrcCurr<<"  "<<xRcvCurr<< " "<< velRelative <<"\n";

        xSrcPrev = xSrcCurr;
        xRcvPrev = xRcvCurr;

        //if (i < numSamples/2)
        //  g = - velRelative/SPEED_OF_SOUND; // "growth parameter"
        //else
        g = + velRelative/SPEED_OF_SOUND;
        readPtr+=g; //update read pointer with variable delay

        //wraparound checks:
        if (readPtr < 0)
            readPtr+=DELAY_SIZE;
        if (readPtr>DELAY_SIZE-1)
            readPtr-=DELAY_SIZE;

        //write pointer simply increments...
        writePtr++;
        if (writePtr>DELAY_SIZE)
            writePtr-=DELAY_SIZE;

        //where the magic happens: the variable delay creates the frequency shift
        delay.setDelay(1+readPtr);

        //User Selectable switching of the "Mixing": gets rid of discontinuities
        // when the read pointer crosses the write location by
        // linearly mixing between half a delay line away.
        // maximum amplitude is respected, but at the cost
        // of additional artifacts. better mixing techniques could reduce these...
        double mix = ( (int)(readPtr-writePtr) % (DELAY_SIZE) ) / (double) DELAY_SIZE ;
        if (atoi(argv[7]) == 0)
            mix = 1; // overrides the mixing calculation. i.e. no mixing.

        //update output sample
        float outsample = mix*delay.tick(inputLoop.tick());

        //apply mixing (if any)
        outsample += (1-mix)*delay.tapOut(DELAY_SIZE/2);

        //put into frames
        frames[i] = outsample;
        //std::cout<<"tE = " << timeElapsed<<"\n";
    }


    //dump frames into outputFile file. (could have incrementally done it directly above...)
    outputFile.tick(frames);

    return 0;
}