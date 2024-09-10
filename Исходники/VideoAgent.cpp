void VideoHelper::OpenVideo(CString strFilePath, FrameData& data)
{    
    AVIFileInit();

    LONG hr;  
    hr = AVIStreamOpenFromFile(&m_pAviStream, strFilePath, streamtypeVIDEO, 0, OF_READ, NULL);
    if (hr != 0){ 
        // Handle failure.
        AfxMessageBox(L"Failed to open file."); 
    }
    else
    {
        PAVIFILE         pf; 
        PAVISTREAM       psSmall; 
        HRESULT          hr; 
        AVISTREAMINFO    strhdr; 
        BITMAPINFOHEADER bi; 
        BITMAPINFOHEADER biNew; 
        LONG             lStreamSize; 
        LPVOID           lpOld; 
        LPVOID           lpNew; 

        // Determine the size of the format data using 
        // AVIStreamFormatSize. 
        AVIStreamFormatSize(m_pAviStream, 0, &lStreamSize); 
        if (lStreamSize > sizeof(bi)) // Format too large? 
            return; 

        lStreamSize = sizeof(bi); 
        hr = AVIStreamReadFormat(m_pAviStream, 0, &bi, &lStreamSize); // Read format 
        if (bi.biCompression != BI_RGB) // Wrong compression format? 
            return; 

        hr = AVIStreamInfo(m_pAviStream, &strhdr, sizeof(strhdr)); 

        // Create new AVI file using AVIFileOpen. 
        hr = AVIFileOpen(&pf, strFilePath + L".Processed.avi", OF_WRITE | OF_CREATE, NULL); 
        if (hr != 0) 
            return; 

        // Set parameters for the new stream. 
        biNew = bi; 

        SetRect(&strhdr.rcFrame, 0, 0, (int) biNew.biWidth, 
            (int) biNew.biHeight); 

        // Create a stream using AVIFileCreateStream. 
        hr = AVIFileCreateStream(pf, &psSmall, &strhdr); 
        if (hr != 0) {            //Stream created OK? If not, close file. 
            AVIFileRelease(pf); 
            return; 
        } 

        // Set format of new stream using AVIStreamSetFormat. 
        hr = AVIStreamSetFormat(psSmall, 0, &biNew, sizeof(biNew)); 
        if (hr != 0) { 
            AVIStreamRelease(psSmall); 
            AVIFileRelease(pf); 
            return; 
        } 

        // Allocate memory for the bitmaps. 
        lpOld = malloc(bi.biSizeImage); 

        // Read the stream data using AVIStreamRead. 
        for (lStreamSize = AVIStreamStart(m_pAviStream); lStreamSize <
            AVIStreamEnd(m_pAviStream)/*1500*/; lStreamSize++) { 
                //Context::Oversubscribe(true);
                hr = AVIStreamRead(m_pAviStream, lStreamSize, 1, lpOld, bi.biSizeImage,
                    NULL, NULL); 
                //Context::Oversubscribe(false);
                //memcpy_s(lpNew, bi.biSizeImage, lpOld, bi.biSizeImage);
                data.m_BBP = bi.biBitCount;
                data.m_ColorPlanes = bi.biPlanes;
                data.m_EndHeight = bi.biHeight;
                data.m_EndWidth = bi.biWidth;
                data.m_pFrame = (BYTE*)lpOld;
                data.m_Pitch = bi.biWidth * (bi.biBitCount / 8);
                data.m_Size = bi.biSizeImage;
                data.m_StartHeight = 0;
                data.m_StartWidth = 0;
                lpNew = m_pVideoAgent->ProcessFrame(data);
               

                if(NULL != lpNew)
                {
                    // Save the compressed data using AVIStreamWrite.
                    hr = AVIStreamWrite(psSmall, lStreamSize, 1, lpNew,
                    biNew.biSizeImage, AVIIF_KEYFRAME, NULL, NULL);
                }
        } 
        free(lpOld);
        // Close the stream and file. 
        AVIStreamRelease(psSmall); 
        AVIFileRelease(pf); 
    }
    AVIFileExit();
}