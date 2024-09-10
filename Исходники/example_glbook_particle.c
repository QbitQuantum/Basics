///
// kdMain()
//
//    Main function for OpenKODE application
//
KDint KD_APIENTRY kdMain(KDint argc, const KDchar *const *argv)
{
    Example *example = exampleInit();

    UserData userdata;
    example->userptr = &userdata;
    Init(example);

    KDust t1 = kdGetTimeUST();
    KDfloat32 deltatime;
    KDfloat32 totaltime = 0.0f;
    KDuint frames = 0;

    // Main Loop
    while(example->run)
    {
        const KDEvent *event = kdWaitEvent(-1);
        if(event)
        {
            switch(event->type)
            {
                case(KD_EVENT_QUIT):
                case(KD_EVENT_WINDOW_CLOSE):
                {
                    example->run = KD_FALSE;
                    break;
                }
                default:
                {
                    kdDefaultEvent(event);
                    break;
                }
            }
        }
        // Update
        KDust t2 = kdGetTimeUST();
        deltatime = (KDfloat32)((t2 - t1) * 1e-9);
        t1 = t2;
        Update(example, deltatime);

        // Draw frame
        Draw(example);
        exampleRun(example);

        // Benchmark
        totaltime += deltatime;
        frames++;
        if(totaltime > 5.0f)
        {
            kdLogMessagefKHR("%d frames in %3.1f seconds = %6.3f FPS\n", frames, totaltime, frames / totaltime);
            totaltime -= 5.0f;
            frames = 0;
        }
    }

    ShutDown(example);
    return exampleDestroy(example);
}