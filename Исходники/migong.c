     void init(int color)
     {
      int drive,mode;
      drive=DETECT;
      registerbgidriver(EGAVGA_driver);
      initgraph(&drive,&mode,"");
      setbkcolor(color);


    }