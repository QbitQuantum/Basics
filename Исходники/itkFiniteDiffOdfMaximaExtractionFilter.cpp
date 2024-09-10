void FiniteDiffOdfMaximaExtractionFilter< PixelType, ShOrder, NrOdfDirections>
::ThreadedGenerateData( const OutputImageRegionType& outputRegionForThread, ThreadIdType threadID )
{
    typename CoefficientImageType::Pointer ShCoeffImage = static_cast< CoefficientImageType* >( this->ProcessObject::GetInput(0) );

    ImageRegionConstIterator< CoefficientImageType > cit(ShCoeffImage, outputRegionForThread );

    OdfType odf;
    while( !cit.IsAtEnd() )
    {
        typename CoefficientImageType::IndexType index = cit.GetIndex();
        if (m_MaskImage->GetPixel(index)==0)
        {
            ++cit;
            continue;
        }

        CoefficientPixelType c = cit.Get();

        // calculate ODF
        double max = 0;
        odf.Fill(0.0);
        for (int i=0; i<NrOdfDirections; i++)
        {
            for (int j=0; j<m_NumCoeffs; j++)
                odf[i] += c[j]*m_ShBasis(i,j);
            if (odf[i]>max)
                max = odf[i];
        }
        if (max<0.0001)
        {
            ++cit;
            continue;
        }

        std::vector< DirectionType > candidates, peaks, temp;
        peaks.clear();
        max *= m_PeakThreshold;                         // relative threshold
        FindCandidatePeaks(odf, max, candidates);       // find all local maxima
        candidates = MeanShiftClustering(candidates);   // cluster maxima

        vnl_matrix< double > shBasis, sphCoords;
        Cart2Sph(candidates, sphCoords);                // convert candidate peaks to spherical angles
        shBasis = CalcShBasis(sphCoords);            // evaluate spherical harmonics at each peak
        max = 0.0;
        for (unsigned int i=0; i<candidates.size(); i++)         // scale peaks according to ODF value
        {
            double val = 0;
            for (int j=0; j<m_NumCoeffs; j++)
                val += c[j]*shBasis(i,j);
            if (val>max)
                max = val;
            peaks.push_back(candidates[i]*val);
        }
        std::sort( peaks.begin(), peaks.end(), CompareVectors );  // sort peaks

        // kick out directions to close to a larger direction (too far away to cluster but too close to keep)
        unsigned int m = peaks.size();
        if ( m>m_DirectionImageContainer->Size() )
            m = m_DirectionImageContainer->Size();
        for (unsigned int i=0; i<m; i++)
        {
            DirectionType v1 = peaks.at(i);
            double val = v1.magnitude();
            if (val<max*m_PeakThreshold || val<m_AbsolutePeakThreshold)
                break;

            bool flag = true;
            for (unsigned int j=0; j<peaks.size(); j++)
                if (i!=j)
                {
                    DirectionType v2 = peaks.at(j);
                    double val2 = v2.magnitude();
                    double angle = fabs(dot_product(v1,v2)/(val*val2));
                    if (angle>m_AngularThreshold && val<val2)
                    {
                        flag = false;
                        break;
                    }
                }

            if (flag)
                temp.push_back(v1);
        }
        peaks = temp;

        // fill output image
        unsigned int num = peaks.size();
        if ( num>m_DirectionImageContainer->Size() )
            num = m_DirectionImageContainer->Size();
        for (unsigned int i=0; i<num; i++)
        {
            vnl_vector<double> dir = peaks.at(i);

            ItkDirectionImage::Pointer img = m_DirectionImageContainer->GetElement(i);

            switch (m_NormalizationMethod)
            {
            case NO_NORM:
                break;
            case SINGLE_VEC_NORM:
                dir.normalize();
                break;
            case MAX_VEC_NORM:
                dir /= max;
                break;
            }

            dir = m_MaskImage->GetDirection()*dir;
            itk::Vector< float, 3 > pixel;
            pixel.SetElement(0, -dir[0]);
            pixel.SetElement(1, dir[1]);
            pixel.SetElement(2, dir[2]);
            img->SetPixel(index, pixel);
        }
        m_NumDirectionsImage->SetPixel(index, num);
        ++cit;
    }
    MITK_INFO << "Thread " << threadID << " finished extraction";
}