Byte calculateImageBrightnessFactor(const std::string& inImageFilePath)
{
    BrightnessState state;
    InputFile inputFile;
    ByteVector brightnessValues;
    DistanceAndBrightnessVector valuesForAverage;
    
    inputFile.OpenFile(inImageFilePath);
    
    state.mStream = inputFile.GetInputStream();
    InitializeDecodingState(state);
    StartRead(state);
    
    LongBufferSizeType samplesSkipping = 1; // max samples 20
    if(state.mJPGState.output_width > 500)
        samplesSkipping = state.mJPGState.output_width / 50; // max samples - 50
    else if(state.mJPGState.output_width > 20)
        samplesSkipping = 10; // max samples - 50
    
    LongBufferSizeType rowsSkipping = 1; // max samples 20
    if(state.mJPGState.output_height > 500)
        rowsSkipping = state.mJPGState.output_height / 50; // max samples - 50
    else if(state.mJPGState.output_height > 20)
        rowsSkipping = 10; // max samples - 50
    
    LongBufferSizeType rowCounter = 0;
    
    
    // read samples from image, converting to hsb and keeping the "b" component, as a brightness factor
    while(state.mJPGState.output_scanline < state.mJPGState.output_height)
    {
        try
        {
            state.mTotalSampleRows = jpeg_read_scanlines(&(state.mJPGState), state.mSamplesBuffer, state.mJPGState.rec_outbuf_height);
            ++rowCounter;
            if(rowCounter >= rowsSkipping)
                rowCounter = 0;
            else if(rowCounter != 1)
                continue;
        }
        catch(HummusJPGException)
        {
            state.mTotalSampleRows = 0;
        }
        state.mIndexInRow = 0;
        state.mCurrentSampleRow = 0;
        
        while(state.mCurrentSampleRow < state.mTotalSampleRows)
        {
            LongBufferSizeType row_stride = state.mJPGState.output_width * state.mJPGState.output_components;
            
            // convert samples to HSB (note that some samples are skipped)
            for(LongBufferSizeType i=0;i<row_stride;i+=(state.mJPGState.output_components*samplesSkipping))
            {
                // get rgb
                Byte r = state.mSamplesBuffer[state.mCurrentSampleRow][i];
                Byte g = state.mSamplesBuffer[state.mCurrentSampleRow][i+1];
                Byte b = state.mSamplesBuffer[state.mCurrentSampleRow][i+2];
                
                // calculate brightness [converting to HSB]
                brightnessValues.push_back(RGBtoHSVtoBrightness(r,g,b));
            }
            
            
            ++state.mCurrentSampleRow;
        }
    }
    FinalizeDecoding(state);
    
    // prepare distance data and sort, to remove extremes from calculation
    ByteVector::const_iterator it = brightnessValues.begin();
    for(;it!=brightnessValues.end();++it)
        valuesForAverage.push_back(DistanceAndBrightness(*it,calculateDistance(*it,brightnessValues)));
    
    std::sort(valuesForAverage.begin(),valuesForAverage.end(),DistanceAndBrightnessSort);
    
    
    // now simply calculate the average based on the first 2/3 of the vector, to reduce the effects of extremes
    double average = 0;
    DistanceAndBrightnessVector::const_iterator itCurrent = valuesForAverage.begin();
    unsigned long interestingItemsCount = floor(valuesForAverage.size()*2.0/3.0);
    DistanceAndBrightnessVector::const_iterator itEnd = valuesForAverage.begin()+interestingItemsCount;
    for(itCurrent = valuesForAverage.begin();itCurrent!=itEnd;++itCurrent)
        average+=(double)(itCurrent->brightness)/interestingItemsCount;
    return ceil(average);
}