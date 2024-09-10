void PulseAnalysisDisplay::setup ()
{
    Fl_Widget* w;
    int bigx = 1000;
    int bigy = 400;
    int xbuffer=5, ybuffer=5;
    int xsize0,xsize1,xsize2, xsize3;
    int ysize0,ysize1;
    int x[5];
    int y[INDEPENDENT_TRACES + 3];

    window = new Fl_Double_Window(bigx,bigy, "Pulse Analysis Window");
    // set the current user data (void *) argument to the instance pointer
    window->user_data((void*)(this));

    // position the window on screen
    window->resizable(window);

    // begin the main window group
    window->begin();
    {
        xsize0 = 50;                              // channel selector
        xsize1 = 100;                             // color selector
        xsize2 = xsize1 + xsize0 + xbuffer;       // plot selector
        ysize0 = 25;                              // standard size
        ysize1 = (bigy - 2*ybuffer);              // plotWindow height

        x[0] = xbuffer+xbuffer;                   // channel
        x[1] = x[0] + xsize0 + xbuffer;           // color
        x[2] = x[0];                              // plot type
        x[3] = x[1] + xsize1 + xbuffer;           // plot itself
                                                  // plotWindow width
        xsize3 = bigx - (x[1] + xsize1 + xbuffer) - xbuffer;

        y[0] = ybuffer;                           // plot selector
        y[1] = y[1] + ysize0 + ybuffer;           // analysis enable
        y[2] = y[1] + 2*ysize0 + ybuffer;         // label
        for (unsigned int i=0; i<INDEPENDENT_TRACES; i++)
        {
            y[3+i] = y[2+i] + ysize0 + ybuffer;   // top of top plot choice
        }

        // what kind of plot the user wants to see
        Fl_Menu_Item plotPopup[] =
        {
            {"Pulse Height", 0, (Fl_Callback*) handleEvent, (void*) this},
            {"Baseline",     0, (Fl_Callback*) handleEvent, (void*) this},
            {0}
        };
        w = plotSelector = new Fl_Choice (x[0],y[1],xsize2,ysize0,"");
        plotSelector->copy(plotPopup,NULL);
        w->align(FL_ALIGN_RIGHT);

        // enable analysis button
        w = performAnalysisFlagButton = new Fl_Light_Button(x[0],y[0],xsize2,ysize0,"Enable Analysis");
        w->callback((Fl_Callback*) handleEvent, (void*) this);

        // the channel selectors
        w  = new Fl_Box (x[0],y[2],xsize0,0,"Channel");
        w->align(FL_ALIGN_TOP);

        w  = new Fl_Box (x[1],y[2],xsize0,0,"Color");
        w->align(FL_ALIGN_TOP);

        Fl_Menu_Item topChanPopup[] =
        {
            {"-", 0,(Fl_Callback*) handleEvent, (void*) this},
            {0}
        };

        for (unsigned int i=0; i< INDEPENDENT_TRACES; i++)
        {
            w = channelSelector[i] = new Fl_Choice (x[0],y[i+2],xsize0,ysize0);
            channelSelector[i]->copy(topChanPopup,NULL);
            w->align(FL_ALIGN_TOP);
        }

        // color selector
        Fl_Menu_Item colorPopup[] =
        {
            {"Black",      0, NULL, (void*) this},
            {"Red",        0, NULL, (void*) this},
            {"Blue",       0, NULL, (void*) this},
            {"Green",      0, NULL, (void*) this},
            {"Dark Red",   0, NULL, (void*) this},
            {"Dark Blue",  0, NULL, (void*) this},
            {"Dark Green", 0, NULL, (void*) this},
            {"Dark Cyan",  0, NULL, (void*) this},
            {0}
        };
        for (unsigned int i=0; i< INDEPENDENT_TRACES; i++)
        {
            w = traceColorSelector[i] = new Fl_Choice (x[1],y[i+2],xsize1, ysize0);
            traceColorSelector[i]->copy(colorPopup,NULL);
            w->align(FL_ALIGN_TOP);
        }

        // the actual plotter widget
        plot = new plotWindow (x[3],y[0],xsize3,ysize1);

        // set some flags
        plot->connectedLineFlag(false);
        plot->xDisplayMethod (3);                 // set x to auto scroll
        plot->yDisplayMethod (1);                 // set y to maximum

    }   window->end();                            // end main window grouping

    // now that we are out of the group, init the plot
    plot->init();

}