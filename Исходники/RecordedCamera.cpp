void RecordedCamera::moveCamera_translation()
{
    double simuTime = this->getContext()->getTime();
    SReal totalTime = this->m_endTime.getValue();
    simuTime -= m_startTime.getValue();
    totalTime -= m_startTime.getValue();

    if (totalTime == 0.0)
        totalTime = 200.0;

    if(m_translationPositions.isSet() && m_translationPositions.getValue().size() > 0)
    {
        unsigned int nbrPoints = (unsigned int)m_translationPositions.getValue().size();
        double timeBySegment = totalTime/(nbrPoints - 1);
        double simuTimeModTotalTime = fmod((SReal)simuTime,(SReal)totalTime);
        unsigned int currentIndexPoint = (unsigned int)floor((simuTimeModTotalTime/timeBySegment));
        double ratio = fmod(simuTimeModTotalTime,timeBySegment)/timeBySegment;

        // if the view up vector was not initialized
        if (m_cameraUp.getValue().norm() < 1e-6)
        this->initializeViewUp();

        if(currentIndexPoint < nbrPoints - 1)
        {
            Vec3 _pos = m_translationPositions.getValue()[currentIndexPoint];
            p_lookAt.setValue(m_translationPositions.getValue()[currentIndexPoint + 1]);
            Vec3 cameraFocal = p_lookAt.getValue() - _pos;

            // Set camera's position: linear interpolation
            p_position.setValue( m_translationPositions.getValue()[currentIndexPoint] + cameraFocal * ratio);

            // Set camera's orientation
            Vec3 zAxis = - (p_lookAt.getValue() - _pos);
            Vec3 xAxis = m_cameraUp.getValue().cross(zAxis);
            Vec3 yAxis = zAxis.cross(xAxis);    
            xAxis.normalize();
            yAxis.normalize();
            zAxis.normalize();
           
#ifdef my_debug
    std::cout << "xAxis: " << xAxis << std::endl;
    std::cout << "yAxis: " << yAxis << std::endl;
    std::cout << "zAxis: " << zAxis << std::endl;
#endif
         
            m_cameraUp.setValue(yAxis);
            Quat orientation  = Quat::createQuaterFromFrame(xAxis, yAxis, zAxis);
            orientation.normalize();
            p_orientation.setValue(orientation);
        }

        else if (currentIndexPoint == nbrPoints - 1 )
        {
            p_position.setValue(m_translationPositions.getValue()[currentIndexPoint]);
            p_lookAt.setValue(m_translationPositions.getValue()[currentIndexPoint]);
        }
    }

    return;
}