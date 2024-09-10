/**
 * @brief First Estimation of the fitted shape by scaling only
 * @param iShape -- input shape
 * @param rect   -- the rectangle to calculate the scalar
 * @return VO_Shape -- the scaled shape
 */
VO_Shape VO_Fitting2DSM::VO_FirstEstimationByScaling(   const VO_Shape& iShape,
        const cv::Rect& rect )
{
    VO_Shape res = iShape;
    cv::Rect_<float> rect0 = iShape.GetShapeRect();
    float fScaleX = (float)rect.width/rect0.width *0.80;
    float fScaleY = (float)rect.height/rect0.height *0.80;
    res.ScaleX(fScaleX);
    res.ScaleY(fScaleY);
    rect0 = iShape.GetShapeBoundRect();
    cv::Mat_<float> translation = cv::Mat_<float>::zeros(2, 1);
    float centerX = (float)rect.x + (float)rect.width/2.0f;
    float centerY = (float)rect.y + (float)rect.height/2.0f;
    float center0X = (float)rect0.x + (float)rect0.width/2.0f;
    float center0Y = (float)rect0.x + (float)rect0.height/2.0f;
    translation(0,0) = centerX - center0X;
    translation(1,0) = centerY - center0Y;
    res.Translate( translation );
    return res;
}