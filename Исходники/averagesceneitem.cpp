void AverageSceneItem::paintAveragePath(QPainter *painter)
{
    if(m_lAverageData.size() == 0)
        return;

    //get maximum range of respective channel type (range value in FiffChInfo does not seem to contain a reasonable value)
    float dMaxValue = 1e-9f;

    switch(m_iChannelKind) {
        case FIFFV_MEG_CH: {
            if(m_iChannelUnit == FIFF_UNIT_T_M) { //gradiometers
                dMaxValue = 1e-10f;
                if(m_scaleMap.contains(FIFF_UNIT_T_M))
                    dMaxValue = m_scaleMap[FIFF_UNIT_T_M];
            }
            else if(m_iChannelUnit == FIFF_UNIT_T) //magnitometers
            {
                dMaxValue = 1e-11f;

                if(m_scaleMap.contains(FIFF_UNIT_T))
                    dMaxValue = m_scaleMap[FIFF_UNIT_T];
            }
            break;
        }

        case FIFFV_REF_MEG_CH: {  /*11/04/14 Added by Limin: MEG reference channel */
            dMaxValue = 1e-11f;
            if(m_scaleMap.contains(FIFF_UNIT_T))
                dMaxValue = m_scaleMap[FIFF_UNIT_T];
            break;
        }
        case FIFFV_EEG_CH: {
            dMaxValue = 1e-4f;
            if(m_scaleMap.contains(FIFFV_EEG_CH))
                dMaxValue = m_scaleMap[FIFFV_EEG_CH];
            break;
        }
        case FIFFV_EOG_CH: {
            dMaxValue = 1e-3f;
            if(m_scaleMap.contains(FIFFV_EOG_CH))
                dMaxValue = m_scaleMap[FIFFV_EOG_CH];
            break;
        }
        case FIFFV_STIM_CH: {
            dMaxValue = 5;
            if(m_scaleMap.contains(FIFFV_STIM_CH))
                dMaxValue = m_scaleMap[FIFFV_STIM_CH];
            break;
        }
        case FIFFV_MISC_CH: {
            dMaxValue = 1e-3f;
            if(m_scaleMap.contains(FIFFV_MISC_CH))
                dMaxValue = m_scaleMap[FIFFV_MISC_CH];
            break;
        }
    }

    //Plot averaged data
    QRectF boundingRect = this->boundingRect();
    double dScaleY = (boundingRect.height()*10)/(2*dMaxValue);
    QPointF qSamplePosition;

    //do for all currently stored evoked set data
    for(int dataIndex = 0; dataIndex<m_lAverageData.size(); dataIndex++) {
        //plot data from averaged data m_lAverageData with the calculated downsample factor
        const double* averageData = m_lAverageData.at(dataIndex).first;
        int totalCols =  m_lAverageData.at(dataIndex).second;

        //Calculate downsampling factor of averaged data in respect to the items width
        int dsFactor;
        totalCols / boundingRect.width()<1 ? dsFactor = 1 : dsFactor = totalCols / boundingRect.width();
        if(dsFactor == 0)
            dsFactor = 1;

        //Create path
        //float offset = (*(averageData+(abs(m_firstLastSample.first)*m_iTotalNumberChannels)+m_iChannelNumber)); //choose offset to be the signal value at time instance 0
        QPainterPath path = QPainterPath(QPointF(boundingRect.x(), boundingRect.y() + boundingRect.height()/2));
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(Qt::yellow);
        if(!m_cAverageColors.isEmpty() && !(dataIndex<m_cAverageColors.size()))
            pen.setColor(m_cAverageColors.at(dataIndex));
        pen.setWidthF(5);
        painter->setPen(pen);

        for(int i = 0; i < totalCols && path.elementCount() <= boundingRect.width(); i += dsFactor) {
            //evoked matrix is stored in column major
            double val = ((*(averageData+(i*m_iTotalNumberChannels)+m_iChannelNumber))/*-offset*/) * dScaleY;

            qSamplePosition.setY(-val);
            qSamplePosition.setX(path.currentPosition().x()+1);

            path.lineTo(qSamplePosition);
        }

        painter->drawPath(path);
    }
}