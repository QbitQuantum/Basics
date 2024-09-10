/*-----------------------------------------------------------------------------\*
 Add background based on the new image and return the current model if asked for
 \*-----------------------------------------------------------------------------*/
void ImageModel::AddBackground(IplImage* img, MOGParams &mogParams,
        IplImage *bgImage, IplImage* fgImage) {
    std::vector<double> vecFeatures;
    vecFeatures.reserve(mogParams.nNumberOfFeatures);

    for (int i = 0; i < m_nNumberOfPixels; ++i) {
        int nRow = i / m_nWidth;
        int nCol = i % m_nWidth;
        GetPixel(img, nRow, nCol, vecFeatures);
        m_vecPixelModels[i]->AddBackground(vecFeatures, mogParams);
        if (fgImage != NULL)
            ((uchar *) (fgImage->imageData + nRow * fgImage->widthStep))[nCol] =
                    m_vecPixelModels[i]->m_bIsForeground ? 255 : 0;
        if (bgImage != NULL)
            SetPixel(bgImage, nRow, nCol,
                    m_vecPixelModels[i]->GetBackgroundModel());
    }
}