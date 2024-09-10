void GDALdllImageFilledPolygon(int nRasterXSize, int nRasterYSize, 
                               int nPartCount, int *panPartSize,
                               double *padfX, double *padfY,
                               double *dfVariant,
                               llScanlineFunc pfnScanlineFunc, void *pCBData )
{
/*************************************************************************
2nd Method (method=1):
=====================
No known bug
*************************************************************************/

    int i;
    int y;
    int miny, maxy,minx,maxx;
    double dminy, dmaxy;
    double dx1, dy1;
    double dx2, dy2;
    double dy;
    double intersect;

    int ind1, ind2;
    int ints, n, part;
    int *polyInts;

    int horizontal_x1, horizontal_x2;

    if (!nPartCount) {
        return;
    }

    n = 0;
    for( part = 0; part < nPartCount; part++ )
        n += panPartSize[part];

    polyInts = (int *) malloc(sizeof(int) * n);

    dminy = padfY[0];
    dmaxy = padfY[0];
    for (i=1; (i < n); i++) {

        if (padfY[i] < dminy) {
            dminy = padfY[i];
        }
        if (padfY[i] > dmaxy) {
            dmaxy = padfY[i];
        }
    }
    miny = (int) dminy;
    maxy = (int) dmaxy;
    
    
    if( miny < 0 )
        miny = 0;
    if( maxy >= nRasterYSize )
        maxy = nRasterYSize-1;
   
    
    minx = 0;
    maxx = nRasterXSize - 1;

    /* Fix in 1.3: count a vertex only once */
    for (y=miny; y <= maxy; y++) {
        int	partoffset = 0;

        dy = y +0.5; /* center height of line*/
         

        part = 0;
        ints = 0;

        /*Initialize polyInts, otherwise it can sometimes causes a seg fault */
        memset(polyInts, -1, sizeof(int) * n);

        for (i=0; (i < n); i++) {
        
            
            if( i == partoffset + panPartSize[part] ) {
                partoffset += panPartSize[part];
                part++;
            }

            if( i == partoffset ) {
                ind1 = partoffset + panPartSize[part] - 1;
                ind2 = partoffset;
            } else {
                ind1 = i-1;
                ind2 = i;
            }
	    

            dy1 = padfY[ind1];
            dy2 = padfY[ind2];
            

            if( (dy1 < dy && dy2 < dy) || (dy1 > dy && dy2 > dy) )
                continue;

            if (dy1 < dy2) {
                dx1 = padfX[ind1];
                dx2 = padfX[ind2];
            } else if (dy1 > dy2) {
                dy2 = padfY[ind1];
                dy1 = padfY[ind2];
                dx2 = padfX[ind1];
                dx1 = padfX[ind2];
            } else /* if (fabs(dy1-dy2)< 1.e-6) */
            {
                
                /*AE: DO NOT skip bottom horizontal segments 
                  -Fill them separately- 
                  They are not taken into account twice.*/
                if (padfX[ind1] > padfX[ind2])
                {
                    horizontal_x1 = (int) floor(padfX[ind2]+0.5);
                    horizontal_x2 = (int) floor(padfX[ind1]+0.5);
		
                    if  ( (horizontal_x1 >  maxx) ||  (horizontal_x2 <= minx) )
                        continue;

                    /*fill the horizontal segment (separately from the rest)*/
                    pfnScanlineFunc( pCBData, y, horizontal_x1, horizontal_x2 - 1, (dfVariant == NULL)?0:dfVariant[0] );
                    continue;
                }
                else /*skip top horizontal segments (they are already filled in the regular loop)*/
                    continue;

            }

            if(( dy < dy2 ) && (dy >= dy1))
            {
                
                intersect = (dy-dy1) * (dx2-dx1) / (dy2-dy1) + dx1;

                polyInts[ints++] = (int) floor(intersect+0.5);
            }
        }

        /* 
         * It would be more efficient to do this inline, to avoid 
         * a function call for each comparison.
         * NOTE - mloskot: make llCompareInt a functor and use std
         * algorithm and it will be optimized and expanded
         * automatically in compile-time, with modularity preserved.
         */
        qsort(polyInts, ints, sizeof(int), llCompareInt);


        for (i=0; (i < (ints)); i+=2)
        {
            if( polyInts[i] <= maxx && polyInts[i+1] > minx )
            {
                pfnScanlineFunc( pCBData, y, polyInts[i], polyInts[i+1] - 1, (dfVariant == NULL)?0:dfVariant[0] );
            }
        }
    }

    free( polyInts );
}