void   main()
{
    int     i;
    int     buf[20][28];
    long    l;

    time(&l);
    sRand(l);

    filltri(buf);
    Initialise();
    for(i = 0; i < 5; i++) {
        plottri(buf[i], 28, 1, 7 + 13*i, 0);
        plottri(buf[i+5], 28, 0, 7 + 13*i, 12);
        plottri(buf[i+10], 28, 1, 14 + 13*i, 7);
        plottri(buf[i+15], 28, 0, 14 + 13*i, 19);
    }
    getch();
    closegraph();
    restorecrtmode();
}