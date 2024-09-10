/*
// Getting feature map for the selected subimage  
//
// API
// int getFeatureMaps(const IplImage * image, const int k, featureMap **map);
// INPUT
// image             - selected subimage
// k                 - size of cells
// OUTPUT
// map               - feature map
// RESULT
// Error status
*/
int getFeatureMaps_dp(const IplImage * image,const int k, CvLSVMFeatureMap **map)
{
    int sizeX, sizeY;
    int p, px, strsz;
    int height, width, channels;
    int i, j, kk, c, ii, jj, d;
    float  * datadx, * datady;
    float tmp, x, y, tx, ty;
    IplImage * dx, * dy;
    int *nearest_x, *nearest_y;
    float *w, a_x, b_x;

    float kernel[3] = {-1.f, 0.f, 1.f}; 
    CvMat kernel_dx = cvMat(1, 3, CV_32F, kernel);
    CvMat kernel_dy = cvMat(3, 1, CV_32F, kernel);

    float * r;
    int    * alfa;
    
    float boundary_x[CNTPARTION+1];
    float boundary_y[CNTPARTION+1];
    float max, tmp_scal;
    int    maxi;

	height = image->height;
	width  = image->width ;

    channels  = image->nChannels;

	dx    = cvCreateImage(cvSize(image->width , image->height) , IPL_DEPTH_32F , 3);
    dy    = cvCreateImage(cvSize(image->width , image->height) , IPL_DEPTH_32F , 3);

    sizeX = width  / k;
    sizeY = height / k;
    px    = CNTPARTION  + 2 * CNTPARTION; // контрастное и не контрастное изображение
    p     = px;
    strsz = sizeX * p;
    allocFeatureMapObject(map, sizeX, sizeY, p,  px);

	cvFilter2D(image, dx, &kernel_dx, cvPoint(-1, 0));
	cvFilter2D(image, dy, &kernel_dy, cvPoint(0, -1));
	
    for(i = 0; i <= CNTPARTION; i++)
    {
        boundary_x[i] = cosf((((float)i) * (((float)PI) / (float) (CNTPARTION))));
        boundary_y[i] = sinf((((float)i) * (((float)PI) / (float) (CNTPARTION))));
    }/*for(i = 0; i <= CNTPARTION; i++) */

    r    = (float *)malloc( sizeof(float) * (width * height));
    alfa = (int   *)malloc( sizeof(int  ) * (width * height * 2));

    for(j = 1; j < height-1; j++)
    {
        datadx = (float*)(dx->imageData + dx->widthStep *j);
        datady = (float*)(dy->imageData + dy->widthStep *j);
        for(i = 1; i < width-1; i++)
        {
			c = 0;
            x = (datadx[i*channels+c]);
            y = (datady[i*channels+c]);

            r[j * width + i] =sqrtf(x*x + y*y);
            for(kk = 1; kk < channels; kk++)
            {
                tx = (datadx[i*channels+kk]);
                ty = (datady[i*channels+kk]);
                tmp =sqrtf(tx*tx + ty*ty);
                if(tmp > r[j * width + i])
                {
                    r[j * width + i] = tmp;
                    c = kk;
                    x = tx;
                    y = ty;
                }
            }/*for(kk = 1; kk < channels; kk++)*/

            
            
            max  = boundary_x[0]*x + boundary_y[0]*y;
            maxi = 0;
            for (kk = 0; kk < CNTPARTION; kk++) {
                tmp_scal = boundary_x[kk]*x + boundary_y[kk]*y;
                if (tmp_scal> max) {
                    max = tmp_scal;
                    maxi = kk;
                }else if (-tmp_scal> max) {
                    max = -tmp_scal;
                    maxi = kk + CNTPARTION;
                }
            }
            alfa[j * width * 2 + i * 2    ] = maxi % CNTPARTION;
            alfa[j * width * 2 + i * 2 + 1] = maxi;  
        }/*for(i = 0; i < width; i++)*/
    }/*for(j = 0; j < height; j++)*/

    //подсчет весов и смещений
    nearest_x = (int *)malloc(sizeof(int) * k);
    nearest_y = (int *)malloc(sizeof(int) * k);
    w         = (float*)malloc(sizeof(float) * (k * 2));
    
    for(i = 0; i < k / 2; i++)
    {
        nearest_x[i] = -1;
        nearest_y[i] = -1;
    }/*for(i = 0; i < k / 2; i++)*/
    for(i = k / 2; i < k; i++)
    {
        nearest_x[i] = 1;
        nearest_y[i] = 1;
    }/*for(i = k / 2; i < k; i++)*/

    for(j = 0; j < k / 2; j++)
    {
        b_x = k / 2 + j + 0.5f;
        a_x = k / 2 - j - 0.5f;
        w[j * 2    ] = 1.0f/a_x * ((a_x * b_x) / ( a_x + b_x)); 
        w[j * 2 + 1] = 1.0f/b_x * ((a_x * b_x) / ( a_x + b_x));  
    }/*for(j = 0; j < k / 2; j++)*/
    for(j = k / 2; j < k; j++)
    {
        a_x = j - k / 2 + 0.5f;
        b_x =-j + k / 2 - 0.5f + k;
        w[j * 2    ] = 1.0f/a_x * ((a_x * b_x) / ( a_x + b_x)); 
        w[j * 2 + 1] = 1.0f/b_x * ((a_x * b_x) / ( a_x + b_x));  
    }/*for(j = k / 2; j < k; j++)*/


    //интерпол¤ци¤
    for(i = 0; i < sizeY; i++)
    {
        for(j = 0; j < sizeX; j++)
        {
            for(ii = 0; ii < k; ii++)
            {
                for(jj = 0; jj < k; jj++)
                {
					if ((i * k + ii > 0) && (i * k + ii < height - 1) && (j * k + jj > 0) && (j * k + jj < width - 1))
					{
						d    =  (k*i + ii)* width + (j*k + jj);
						(*map)->Map[(i                ) * strsz + (j                ) * (*map)->p + alfa[d * 2    ]             ] += 
							r[d] * w[ii * 2    ] * w[jj * 2    ];
						(*map)->Map[(i                ) * strsz + (j                ) * (*map)->p + alfa[d * 2 + 1] + CNTPARTION] += 
							r[d] * w[ii * 2    ] * w[jj * 2    ];
						if ((i + nearest_y[ii] >= 0) && (i + nearest_y[ii] <= sizeY - 1))
						{
							(*map)->Map[(i + nearest_y[ii]) * strsz + (j                ) * (*map)->p + alfa[d * 2    ]             ] += 
								r[d] * w[ii * 2 + 1] * w[jj * 2    ];
							(*map)->Map[(i + nearest_y[ii]) * strsz + (j                ) * (*map)->p + alfa[d * 2 + 1] + CNTPARTION] += 
								r[d] * w[ii * 2 + 1] * w[jj * 2    ];
						}
						if ((j + nearest_x[jj] >= 0) && (j + nearest_x[jj] <= sizeX - 1))
						{
							(*map)->Map[(i                ) * strsz + (j + nearest_x[jj]) * (*map)->p + alfa[d * 2    ]             ] += 
								r[d] * w[ii * 2    ] * w[jj * 2 + 1];
							(*map)->Map[(i                ) * strsz + (j + nearest_x[jj]) * (*map)->p + alfa[d * 2 + 1] + CNTPARTION] += 
								r[d] * w[ii * 2    ] * w[jj * 2 + 1];
						}
						if ((i + nearest_y[ii] >= 0) && (i + nearest_y[ii] <= sizeY - 1) && (j + nearest_x[jj] >= 0) && (j + nearest_x[jj] <= sizeX - 1))
						{
							(*map)->Map[(i + nearest_y[ii]) * strsz + (j + nearest_x[jj]) * (*map)->p + alfa[d * 2    ]             ] += 
								r[d] * w[ii * 2 + 1] * w[jj * 2 + 1];
							(*map)->Map[(i + nearest_y[ii]) * strsz + (j + nearest_x[jj]) * (*map)->p + alfa[d * 2 + 1] + CNTPARTION] += 
								r[d] * w[ii * 2 + 1] * w[jj * 2 + 1];
						}
					}
                }/*for(jj = 0; jj < k; jj++)*/
            }/*for(ii = 0; ii < k; ii++)*/
        }/*for(j = 1; j < sizeX - 1; j++)*/
    }/*for(i = 1; i < sizeY - 1; i++)*/
    
    cvReleaseImage(&dx);
    cvReleaseImage(&dy);


    free(w);
    free(nearest_x);
    free(nearest_y);

    free(r);
    free(alfa);

    return LATENT_SVM_OK;
}