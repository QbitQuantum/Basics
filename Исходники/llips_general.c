/********************************************//**
 * \brief Create an image with a view of histogram (RGBY).
 *
 * \param img_in t_img* - input image
 * \param img_out t_img* - output image
 * \return CPU_CHAR - status of operation
 *
 * Width and precision of histogram depend on image width
 ***********************************************/
CPU_CHAR histogram(t_img * img_in,t_img * img_out)
{
    CPU_CHAR ret = ERR_NONE;
    CPU_INT16U i,j;

    CPU_INT32U histowidth ;
    CPU_INT32U histoheigh ;
    CPU_INT32U histo_x = 1 ;
    CPU_INT32U histo_y_red = 1,histo_y_green,histo_y_blue,histo_y_lum ;

    CPU_INT32U * redpixel = calloc((PIXEL_8bit_RANGE+1),sizeof(CPU_INT32U));
    CPU_INT32U * greenpixel = calloc((PIXEL_8bit_RANGE+1),sizeof(CPU_INT32U));
    CPU_INT32U * bluepixel = calloc((PIXEL_8bit_RANGE+1),sizeof(CPU_INT32U));
    CPU_INT32U * luminancepixel = calloc((PIXEL_8bit_RANGE+1),sizeof(CPU_INT32U));
    CPU_CHAR Luminance = 0;

    CPU_INT32U index,histomaxred=0,histomaxgreen=0,histomaxblue=0,histomaxlum =0;

    // configure historgam
    histowidth = (img_in->wi)/4.5;

    if(histowidth>PIXEL_8bit_RANGE)
    {
         histowidth = PIXEL_8bit_RANGE;
    }
    histoheigh = histowidth / 2 ;

    histo_y_green = histo_y_red + histowidth + 2;
    histo_y_blue = histo_y_green + histowidth + 2;
    histo_y_lum = histo_y_blue + histowidth + 2;

    //Write Header
    for(i=0;i<img_in->FileHeader_size;i++)
    {
        img_out->FileHeader[i] = img_in->FileHeader[i];
    }
    img_out->signature = img_in->signature;
    img_out->depth = img_in->depth;
    img_out->wi = img_in->wi;
    img_out->he = img_in->he;
    img_out->FileHeader_size = img_in->FileHeader_size;

    //count distribution of red pixel
    for(i=0;i< (img_in->he ) ;i++)
    {
        for(j=0 ; (j< img_in->wi );j++)
        {
            //getting red pixel
            index = img_in->Red[i][j] / (PIXEL_8bit_RANGE/(histowidth-1));
            redpixel[index]++;
            histomaxred = maxi(histomaxred,redpixel[index]);

            //getting green pixel
            index = img_in->Green[i][j] / (PIXEL_8bit_RANGE/(histowidth-1));
            greenpixel[index]++;
            histomaxgreen = maxi(histomaxgreen,greenpixel[index]);
            //getting red pixel
            index = img_in->Blue[i][j] / (PIXEL_8bit_RANGE/(histowidth-1));
            bluepixel[index]++;
            histomaxblue = maxi(histomaxblue,bluepixel[index]);

            //calcultate luminance Y = 0,299 R + 0,587 G + 0,114 B
            Luminance = (CPU_CHAR)(  (CPU_FP32)img_in->Red[i][j]   * 0.299
                                        + (CPU_FP32)img_in->Green[i][j] * 0.587
                                        + (CPU_FP32)img_in->Blue[i][j]  * 0.114 );

            //getting lumi pixel
            index = Luminance / (PIXEL_8bit_RANGE/(histowidth-1));
            luminancepixel[index]++;
            histomaxlum = maxi(histomaxlum,luminancepixel[index]);
        }
    }

    // normalize histogramm according to highest pixel distribution
    // and height of histogram, and to histogram width
    for(i=0;i<histowidth;i++)
    {
        redpixel[i] = redpixel[i] * histoheigh / histomaxred ;
        greenpixel[i] = greenpixel[i] * histoheigh / histomaxgreen ;
        bluepixel[i] = bluepixel[i] * histoheigh / histomaxblue ;

        luminancepixel[i] = luminancepixel[i] * histoheigh / histomaxblue ;

    }

    //copy input img to output including histogram
    for(i=0;i< (img_in->he ) ;i++)
    {
        for(j=0 ; (j< img_in->wi );j++)
        {
            // Looking for red drawing area
            if(    ((j>=histo_y_red) && (j<=(histo_y_red+histowidth)))
                && ((i>=histo_x) && (i<(histo_x+histoheigh)))
              )
            {
                if(redpixel[j-histo_y_red] >= (i-histo_x))
                {
                    img_out->Red[i][j]   = 255;
                    img_out->Green[i][j] = 0;
                    img_out->Blue[i][j]  = 0;
                }else
                {
                    img_out->Red[i][j]   = (img_in->Red[i][j])/2;
                    img_out->Green[i][j] = (img_in->Green[i][j])/2;
                    img_out->Blue[i][j]  = (img_in->Blue[i][j])/2;
                }
            }// Looking for green drawing area
            else if(   ((j>=histo_y_green) && (j<=(histo_y_green+histowidth)))
                    && ((i>=histo_x) && (i<(histo_x+histoheigh)))
                   )
            {
                if(greenpixel[j-histo_y_green] >= (i-histo_x))
                {
                    img_out->Red[i][j]   = 0;
                    img_out->Green[i][j] = 255;
                    img_out->Blue[i][j]  = 0;
                }else
                {
                    img_out->Red[i][j]   = (img_in->Red[i][j])/2;
                    img_out->Green[i][j] = (img_in->Green[i][j])/2;
                    img_out->Blue[i][j]  = (img_in->Blue[i][j])/2;
                }
            }// Looking for blue drawing area
            else if(   ((j>=histo_y_blue) && (j<=(histo_y_blue+histowidth)))
                    && ((i>=histo_x) && (i<(histo_x+histoheigh)))
                   )
            {
                if(bluepixel[j-histo_y_blue] >= (i-histo_x))
                {
                    img_out->Red[i][j]   = 0;
                    img_out->Green[i][j] = 0;
                    img_out->Blue[i][j]  = 255;
                }else
                {
                    img_out->Red[i][j]   = (img_in->Red[i][j])/2;
                    img_out->Green[i][j] = (img_in->Green[i][j])/2;
                    img_out->Blue[i][j]  = (img_in->Blue[i][j])/2;
                }
            }// looking for lum drawing area
            else if(   ((j>=histo_y_lum) && (j<=(histo_y_lum+histowidth)))
                    && ((i>=histo_x) && (i<(histo_x+histoheigh)))
                   )
            {
                if(luminancepixel[j-histo_y_lum] >= (i-histo_x))
                {
                    img_out->Red[i][j]   = 180;
                    img_out->Green[i][j] = 180;
                    img_out->Blue[i][j]  = 180;
                }else
                {
                    img_out->Red[i][j]   = (img_in->Red[i][j])/2;
                    img_out->Green[i][j] = (img_in->Green[i][j])/2;
                    img_out->Blue[i][j]  = (img_in->Blue[i][j])/2;
                }
            }
            else
            {
                img_out->Red[i][j]   = img_in->Red[i][j];
                img_out->Green[i][j] = img_in->Green[i][j];
                img_out->Blue[i][j]  = img_in->Blue[i][j];
            }
        }
    }




    return ret;
}