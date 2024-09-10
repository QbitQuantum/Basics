double CameraAnimator::determineDurationFactor()
{
    // first try: if the start and end orientation differ by more than 90 degree, make the full animation
    dp::math::Quatf diffQuat = m_cameraMoveStart->getOrientation() / m_cameraMoveTarget->getOrientation();
    dp::math::Vec3f axis;
    float angle;
    decompose( diffQuat, axis, angle );
    double durationFactor = dp::math::clamp( (double)(angle / dp::math::PI_HALF), 0.0, 1.0 );

    // second try: if position moves about the focus distance (in fact the medium between start and end), make the full
    // animation.
    float mediumFocus = 0.5f * ( m_cameraMoveStart->getFocusDistance() + m_cameraMoveTarget->getFocusDistance() );
    float posDistance = dp::math::distance( m_cameraMoveStart->getPosition(), m_cameraMoveTarget->getPosition() );
    durationFactor = dp::math::clamp( (double)(posDistance / mediumFocus), durationFactor, 1.0 );

    // third try: if near distance changes by more than 25%, make the full animation
    durationFactor = clampDeviation( m_cameraMoveStart->getNearDistance(), m_cameraMoveTarget->getNearDistance(), 0.25f, durationFactor );

    // fourth try: if focus distance changes by more than 25%, make the full animation
    durationFactor = clampDeviation( m_cameraMoveStart->getFocusDistance(), m_cameraMoveTarget->getFocusDistance(), 0.25f, durationFactor );

    // fifth try: if far distance changes by more than 25%, make the full animation
    durationFactor = clampDeviation( m_cameraMoveStart->getFarDistance(), m_cameraMoveTarget->getFarDistance(), 0.25f, durationFactor );

    // sixth try: if window size changes by more than 25%, make the full animation
    durationFactor = clampDeviation( m_cameraMoveStart->getWindowSize()[0], m_cameraMoveTarget->getWindowSize()[0], 0.25f, durationFactor );
    durationFactor = clampDeviation( m_cameraMoveStart->getWindowSize()[1], m_cameraMoveTarget->getWindowSize()[1], 0.25f, durationFactor );

    // ignore windowOffset, lowerLeft, upperRight for now! I don't expect them to change much.
    return( durationFactor );
}