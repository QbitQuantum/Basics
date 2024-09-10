bool IPLCanny::processInputData(IPLImage* image , int, bool useOpenCV)
{
    // delete previous result
    delete _result;
    _result = NULL;
    delete _binaryImage;
    _binaryImage = NULL;

    int width = image->width();
    int height = image->height();

    _result = new IPLImage( image->type(), width, height );
    _binaryImage = new IPLImage( IPLData::IMAGE_BW, width, height );

    // get properties
    int window              = getProcessPropertyInt("window");
    double sigma            = getProcessPropertyDouble("sigma");
    double lowThreshold     = getProcessPropertyDouble("lowThreshold");
    double highThreshold    = getProcessPropertyDouble("highThreshold");

    std::stringstream s;
    s << "Window: ";
    s << window;
    addInformation(s.str());

    //! @todo currently only the opencv implementation works
    if(useOpenCV || true)
    {
        notifyProgressEventHandler(-1);
        cv::Mat input;
        cv::Mat output;
        cvtColor(image->toCvMat(), input, CV_BGR2GRAY);
        cv::Canny(input, output, lowThreshold*255, highThreshold*255, window);

        delete _result;
        _result = new IPLImage(output);

        return true;
    }

    return false;

    // Create a Gaussian 1D filter
    int N = ceil( sigma * sqrt( 2.0*log( 1.0/0.015 ) ) + 1.0 );
    double ssq = sigma*sigma;
    double* gau = new double [window];
    double* dgau = new double [window];
    for( int k = -N; k <= N; ++k )
    {
        gau[k+N] = gauss ( (double)k, ssq );
        dgau[k+N] = dGauss ( (double)k, 0, ssq );
    }

    // Create a directional derivative of 2D Gaussian (along X-axis)
    // Since the result is symmetric along X, we can get the derivative along
    // Y-axis simply by transposing the result for X direction.
//		DoubleImage* dgau = new DoubleImage( window, window );
//		for( int y = -N; y <= N; ++y )
//			for( int x = -N; x <= N; ++x )
//				dgau->f(x+N, y+N) = dGauss( x, y, ssq );

    int progress = 0;
    int maxProgress = width * image->getNumberOfPlanes();
    int nrOfPlanes = image->getNumberOfPlanes();

    //#pragma omp parallel for
    for( int planeNr=0; planeNr < nrOfPlanes; planeNr++ )
    {
        IPLImagePlane* plane = image->plane( planeNr );
        IPLImagePlane* newplane = _result->plane( planeNr );

// ******** Gaussian filtering of input image
        IPLImagePlane* gI = new IPLImagePlane( width, height );

        // horizontal run (normalizing original image)
        IPLImagePlane* tmpI = new IPLImagePlane( width, height );
        for(int x=0; x<width; x++)
        {            // progress
            notifyProgressEventHandler(100*progress++/maxProgress);

            for(int y=0; y<height; y++)
            {
                double sum = 0;
                int i = 0;
                for( int kx=-N; kx<=N; kx++ )
                {
                        double img = (double) plane->bp(x+kx, y);
                        sum += (img * gau[i++]);
                }
                tmpI->p(x,y) = (double) (sum);
            }
        }
        // vertiacl run
        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                double sum = 0;
                int i = 0;
                for( int ky=-N; ky<=N; ky++ )
                {
                        double img = tmpI->bp(x, y+ky);
                        sum += (img * gau[i++]);
                }
                gI->p(x,y) = sum;
            }
        }
        //delete tmpI;

// ******** Apply directional derivatives ...

        // ... in x-direction
        IPLImagePlane* dx = new IPLImagePlane( width, height );
        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                dx->p(x,y) = 0.0;
                for( int k=1; k<N; k++ )
                {
                    dx->p(x,y) += ( gI->bp(x-k,y) - gI->bp(x+k,y) ) * dgau[k];
                }
            }
        }
//			double maxVal = 0.0;
//			for(int x=0; x<width; x++)
//				for(int y=0; y<height; y++)
//					if( dx->f(x,y) > maxVal ) maxVal = dx->f(x,y);

        // ... in y-direction
        IPLImagePlane* dy = new IPLImagePlane( width, height );
        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                dy->p(x,y) = 0.0;
                for( int k=1; k<N; k++ )
                {
                    dy->p(x,y) += ( gI->bp(x,y-k) - gI->bp(x,y+k) ) * dgau[k];
                }
            }
        }

// ******** Compute magnitude and binarization thresholds
        IPLImagePlane* mag = new IPLImagePlane( width, height );
        double magMax = 0.0;
        double magMin = 999999999.0;
        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                double val = sqrt( dx->p(x,y)*dx->p(x,y) + dy->p(x,y)*dy->p(x,y) );
                mag->p(x,y) = val;
                if( val > magMax ) magMax = val;
                if( val < magMin ) magMin = val;
            }
        }

//// ******** Non-maxima suppression - edge pixels should be a local maximum
        _orientedImage = new IPLOrientedImage( width, height );
        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                double ix = dx->p(x,y);
                double iy = dy->p(x,y);
                double g = mag->p(x,y);

                // determine 4-neighbor direction of gradient
                int dir4 = 0;
                if( (iy<=0.0 && ix>-iy) || (iy>=0.0 && ix<-iy) )
                    dir4 = 1;
                else if( (ix>0.0 && -iy>=ix) || (ix<0.0 && -iy<=ix) )
                    dir4 = 2;
                else if( (ix<=0.0 && ix>iy) || (ix>=0.0 && ix<iy) )
                    dir4 = 3;
                else if( (iy<0.0 && ix<=iy) || (iy>0.0 && ix>=iy) )
                    dir4 = 4;
                else
                    continue;

                double gradmag1, gradmag2, d;
                switch(dir4)
                {
                    case 1: d = std::fabs(iy/ix);
                            gradmag1 = mag->bp(x+1,y)*(1-d) + mag->bp(x+1,y-1)*d;
                            gradmag2 = mag->bp(x-1,y)*(1-d) + mag->bp(x-1,y+1)*d;
                            break;
                    case 2: d = std::fabs(ix/iy);
                            gradmag1 = mag->bp(x,y-1)*(1-d) + mag->bp(x+1,y-1)*d;
                            gradmag2 = mag->bp(x,y+1)*(1-d) + mag->bp(x-1,y+1)*d;
                            break;
                    case 3: d = std::fabs(ix/iy);
                            gradmag1 = mag->bp(x,y-1)*(1-d) + mag->bp(x-1,y-1)*d;
                            gradmag2 = mag->bp(x,y+1)*(1-d) + mag->bp(x+1,y+1)*d;
                            break;
                    case 4: d = std::fabs(iy/ix);
                            gradmag1 = mag->bp(x-1,y)*(1-d) + mag->bp(x-1,y-1)*d;
                            gradmag2 = mag->bp(x+1,y)*(1-d) + mag->bp(x+1,y+1)*d;
                            break;
                }

                if( g > gradmag1 && g > gradmag2 )
                {
                    _orientedImage->magnitude(x,y) = g;
                    _orientedImage->phase(x,y) = atan2(iy,ix);
                }
            }

        }


        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                _orientedImage->magnitude(x,y) /= magMax;
                double val = _orientedImage->magnitude(x,y)*255.0;
//					double val = mag->f(x,y)/magMax*255.0;
                if (val > 255.0 ) val = 255.0;
                if (val < 0.0 ) val = 0.0;
                newplane->p(x,y) = (unsigned char ) val;
            }
        }

// ******** Binarize with hysteresis threshold
        double hist[ 256 ];
        for( int i=0; i<256; ++i )
            hist[i] = 0;
        int pixCount = 0;
        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                if( _orientedImage->magnitude(x,y) > 0.0 )
                {
                    int index = floor( _orientedImage->magnitude(x,y)*256.0+0.5 );
                    ++hist[ index ];
                    ++pixCount;
                }
            }
        }
        double PercentOfPixelsNotEdges = 0.7*pixCount;
        double highThresh = 0.0;
        double cumsum = 0.0;
        for( int i=0; i<256; ++i )
        {
            cumsum += hist[i];
            if( cumsum > PercentOfPixelsNotEdges )
            {
                highThresh = (double)i / 256.0;
                break;
            }
        }
        double lowThresh = 0.4 * highThresh;
        IPLImagePlane* binPlane = _binaryImage->plane( 0 );
        for(int x=0; x<width; x++)
        {
            for(int y=0; y<height; y++)
            {
                if(_orientedImage->magnitude(x,y) >= highThresh)
                    trace(x, y, lowThresh, _orientedImage, binPlane);
            }
        }
        //delete dx;
        //delete dy;
        //delete gI;

        thinning(_orientedImage, binPlane, newplane );
    }

    //delete [] gau;
    //delete [] dgau;

    return true;
}