void loadMiddleburyMRFData(const std::string &filename, int *&dataCostArray, int *&hCueTransposed, int *&vCue, int &width, int &height, int &nLabels)
{
    FILE *fp;
    fopen_s(&fp, filename.c_str(),"rb");

    if (fp == 0)
    {
        throw(new npp::Exception("File not found!"));
    }

    fscanf_s(fp,"%d %d %d",&width,&height,&nLabels);

    int i, n, x, y;
    int gt;

    for (i = 0; i < width * height; i++)
    {
        fscanf_s(fp,"%d",&gt);
    }

    dataCostArray = (int *) malloc(width * height * nLabels * sizeof(int));
    n = 0;
    int v;

    for (int c=0; c < nLabels; c++)
    {
        for (i = 0; i < width * height; i++)
        {
            fscanf_s(fp,"%d",&v);
            dataCostArray[n++] = v;
        }
    }

    hCueTransposed = (int *) malloc(width * height * sizeof(int));
    vCue = (int *) malloc(width * height * sizeof(int));

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width-1; x++)
        {
            fscanf_s(fp,"%d",&v);
            hCueTransposed[x*height+y] = v;
        }

        hCueTransposed[(width-1)*height+y] = 0;
    }

    for (y = 0; y < height-1; y++)
    {
        for (x = 0; x < width; x++)
        {
            fscanf_s(fp,"%d",&v);
            vCue[y*width+x] = v;
        }
    }

    for (x = 0; x < width; x++)
    {
        vCue[(height-1)*width+x] = 0;
    }

    fclose(fp);

}