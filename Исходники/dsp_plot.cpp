    dsp_plot::dsp_plot()
    {
        //pipe = _popen("C:\\Tools\\gp442win32\\gnuplot\\binary\\gnuplot.exe","w");
        pipe = _popen("C:\\DiskD\\TooBox\\gnuplot\\binary\\gnuplot.exe","w");

        setvbuf(pipe, NULL, _IONBF, 0 );
    }