ImageObject *
CreateDropShadowMask(const ViewportInfo *vpInfo, int offx, int offy, int r)
{
    int rx2 = r * 2;
    int img_w = vpInfo->file->Width();
    int img_h = vpInfo->file->Height();

    ImageObject *mask = new ImageObject(
        offx + r + img_w, offy + r + img_h, 1);

    // Create the blur image
    float *blur = new float[rx2 * rx2];
    //float root2 = sqrt(2.);
    float blurSum = 0.;
    for (int i=0; i<rx2; i++)
    {
        for (int j=0; j<rx2; j++)
        {
            float u = float(i)/float(rx2-1);
            float v = float(j)/float(rx2-1);

            float gu = exp(-pow((4*(u - .5)), 2));
            float gv = exp(-pow((4*(v - .5)), 2));
            float a = gu * gv;
            blur[i*rx2+j] = a;
            blurSum += a;
        }
    }
    for(int j = 0; j < rx2; ++j)
        for(int i = 0; i < rx2; ++i)
            blur[j*rx2 + i] /= blurSum;

    if(vpInfo->opaqueMode == M_OPAQUE)
    {
        int white = 255;
        mask->SetBlockToColor(offx, offy, offx + img_w, offy + img_h, &white);
    }
    else if(vpInfo->opaqueMode == M_TRANSPARENT)
    {
        int gray = int(vpInfo->opacity * 255.);
        mask->SetBlockToColor(offx, offy, offx + img_w, offy + img_h, &gray);
    }
    else
    {
        unsigned char rr, rg, rb;
        rr = vpInfo->transparentColor[0];
        rg = vpInfo->transparentColor[1];
        rb = vpInfo->transparentColor[2];

        // Everywhere that does not match the bg color, color white.
        for(int y = 0; y < img_h; ++y)
        {
            for(int x = 0; x < img_w; ++x)
            {
                unsigned char *src = vpInfo->file->Pixel(x, y);
                unsigned char *dest = mask->Pixel(x+offx, y+offy);

                if(src[0] != rr || src[1] != rg || src[2] != rb)
                    *dest = 255;
            }
        }
    }

    // Blur the mask by convolving it with the blur kernel.
    for(int y = offy; y < offy + img_h; ++y)
    {
        for(int x = offx; x < offx + img_w; ++x)
        {
            int ksrcx = x - r;
            int ksrcy = y - r;
            float channelSum = 0.;
            for(int ky = 0; ky < rx2; ++ky)
            {
                for(int kx = 0; kx < rx2; ++kx)
                {
                    unsigned char *mask_ptr = mask->Pixel(ksrcx + kx, ksrcy + ky);
                    channelSum += float(*mask_ptr) * blur[ky*rx2+kx];
                }
            }
            unsigned char *dest = mask->Pixel(x, y);
            *dest = (unsigned char)(int)(channelSum);
        }
    }

    if(vpInfo->opaqueMode == M_TRANSPARENT)
    {
        int black = 0;
        mask->SetBlockToColor(0, 0, img_w, img_h, &black);
    }
    delete [] blur;

    return mask;
}