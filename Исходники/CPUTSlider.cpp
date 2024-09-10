// Get's the value the slider is current positioned at
//--------------------------------------------------------------------------------
CPUTResult CPUTSlider::GetValue(float & fValue)
{
    LocationGuides guides;
    CalculateLocationGuides(guides);
  
    float fractpart, intpart;
    fractpart = modff((mSliderNubLocation/guides.StepSpacing) , &intpart);
    int index = (int) intpart;
    if(fractpart>=0.5f)
        index++;

    float stepSizeValue = (mSliderEndValue - mSliderStartValue)/(float)(mSliderNumberOfSteps-1);

    // calculate the slider location's value
    fValue = mSliderStartValue + stepSizeValue*index;

    // In extreme range cases, the calculated value might be off by a fractional amount
    // prevent the slider from returning an above/below start/end value
    if(fValue > mSliderEndValue)
    {
        fValue = mSliderEndValue;
    }
    if(fValue < mSliderStartValue)
    {
        fValue = mSliderStartValue;
    }

    return CPUT_SUCCESS;
}