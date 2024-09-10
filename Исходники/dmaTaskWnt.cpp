/*
 * dmaStartup -- Start the threads that generate the 10ms interval signal,
 *      and that handle the audio input and output.
 */
OsStatus dmaStartup(int samplesPerFrame)
{
    if (!checkFormat(1, SAMPLES_PER_SEC, BITS_PER_SAMPLE))
    {
        osPrintf(" %3d channels, %5d samples/sec, %2d bits/sample: is NOT supported\n",
                1, SAMPLES_PER_SEC, BITS_PER_SAMPLE) ;

        // 12/16/2004: Allow thread to startup and attempt to open audio
        // channels.  It will likely fail, but the code down stream will
        // fire off alt heartbeat mechanism.
    }


    // start a thread to receive microphone input
    // mic thread will prime the device input queue
    hMicThread = (HANDLE)_beginthreadex(
            NULL,             // pointer to thread security attributes
            16000,            // initial thread stack size, in bytes
            MicThread,        // pointer to thread function
            (LPVOID) 0,       // argument for new thread
            CREATE_SUSPENDED, // creation flags
            (unsigned*)&dwMicThreadID    // pointer to returned thread identifier
    );

    assert(NULL != hMicThread);

    // start a thread to send audio out to the speaker
    // speaker thread will prime the device output queue
    hSpkrThread = (HANDLE)_beginthreadex(
            NULL,             // pointer to thread security attributes
            16000,            // initial thread stack size, in bytes
            SpkrThread,       // pointer to thread function
            (LPVOID) 0,       // argument for new thread
            CREATE_SUSPENDED, // creation flags
            (unsigned*)&dwSpkrThreadID    // pointer to returned thread identifier
    );

    assert(NULL != hSpkrThread);

    // All these threads were started with the SUSPENDED option so that
    // the following thread priority manipulations can happen without
    // yielding the CPU.  They will be resumed soon, but see the comment
    // next below...
    SetThreadPriority(hSpkrThread, THREAD_PRIORITY_TIME_CRITICAL);
    SetThreadPriority(hMicThread, THREAD_PRIORITY_TIME_CRITICAL);


    // Both the Microphone thread and the Speaker thread issue resume
    // commands for the other thread (Mic resumes Spkr, Spkr resumes Mic).
    // (Resuming a running thread is harmless).
    //
    // Exactly one of the two threads should be resumed here, and that one
    // will get the first opportunity to open its side of the audio device.
    // Once it has done so, it will issue the resume command for the other
    // thread, so that on systems with half-duplex audio devices we will be
    // consistent about which device will be opened and which will fail.
    //
    // Currently, we start the Speaker thread first, so that we will be
    // sure to open the output device on a half-duplex system.  If it is
    // decided that we want to open only the input device in such situations,
    // REPLACE the next statement with "ResumeThread(hMicThread);"

    ResumeThread(hSpkrThread);

    return OS_SUCCESS;
}