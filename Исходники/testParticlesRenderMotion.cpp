// redraw the window
void display(void)
{
       
    if(runBench)
    {
        static Int32 preframes = 5; // some drivers don't like to be swamped early
        
        if(--preframes < 0)
        {
            Time start,stop;

            start = getSystemTime();
            for(UInt32 i = 0; i < 100; i++)
            {
                mgr->redraw();
            }
            stop = getSystemTime();
            FLOG(( "100 frames a %d parts in %.2f secs (%.0f parts/sec)\n",
                    numParticles, stop-start, 100 * numParticles / (stop-start) ));
            exit(0);
        }
    }
    
    mgr->redraw();
}