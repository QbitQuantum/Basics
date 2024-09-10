int main()
{
    Sine s;
    Triangle t;
    Square sq;

    vector<double> buf(44100*5);
    
    s.generate(0, 440.0, &buf);
    // t.generate(0, 440.0, &buf);
    // sq.generate(0, 440.0, &buf);

    //   printf("Generated Sine\n");
    //    for (int i = 0; i < 100; i++) printf("%f\n", buf[i]);

    vector<short> bufShort(44100*5);

    transform(buf.begin(), buf.end(), bufShort.begin(), [](double x){
        return static_cast<short>(x * 30000);
    });

//    for (int i = 0; i <= 100; i++) printf("%d\n", bufShort[3000+i]);	

    //    printf("Ready to initialize\n");
    initialize();
    checkError();
    
    ALuint buffer;
    alGenBuffers(1, &buffer);

    alBufferData(buffer, AL_FORMAT_MONO16, bufShort.data(), bufShort.size(), 44100);
    checkError();

    ALuint source;
    alGenSources(1, &source);
    checkError();

    alSourcei(source, AL_BUFFER, buffer);
    checkError();

    //    printf("Before play\n");

    alSourcePlay(source);
    checkError();
    
     //   printf("After play\n");

     //   printf("Before wait\n");

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

     //   printf("After wait\n");

    checkError();
    exit();
    return(EXIT_SUCCESS);
}