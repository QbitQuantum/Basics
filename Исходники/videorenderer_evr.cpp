void VideoRendererEVR::applyMixerSettings(qreal brightness, qreal contrast, qreal hue, qreal saturation)
{
    InputPin sink = BackendNode::pins(m_filter, PINDIR_INPUT).first();
    OutputPin source;
    if (FAILED(sink->ConnectedTo(source.pparam()))) {
        return; //it must be connected to work
    }

    // Get the "Video Processor" (used for brightness/contrast/saturation/hue)
    ComPointer<IMFVideoProcessor> processor = getService<IMFVideoProcessor>(m_filter, MR_VIDEO_MIXER_SERVICE, IID_IMFVideoProcessor);
    Q_ASSERT(processor);

    DXVA2_ValueRange contrastRange;
    DXVA2_ValueRange brightnessRange;
    DXVA2_ValueRange saturationRange;
    DXVA2_ValueRange hueRange;

    if (FAILED(processor->GetProcAmpRange(DXVA2_ProcAmp_Contrast, &contrastRange)))
        return;
    if (FAILED(processor->GetProcAmpRange(DXVA2_ProcAmp_Brightness, &brightnessRange)))
        return;
    if (FAILED(processor->GetProcAmpRange(DXVA2_ProcAmp_Saturation, &saturationRange)))
        return;
    if (FAILED(processor->GetProcAmpRange(DXVA2_ProcAmp_Hue, &hueRange)))
        return;

    DXVA2_ProcAmpValues values;

    values.Contrast = DXVA2FloatToFixed(((contrast < 0
                                          ? DXVA2FixedToFloat(contrastRange.MinValue) : DXVA2FixedToFloat(contrastRange.MaxValue))
                                         - DXVA2FixedToFloat(contrastRange.DefaultValue)) * qAbs(contrast) + DXVA2FixedToFloat(contrastRange.DefaultValue));
    values.Brightness = DXVA2FloatToFixed(((brightness < 0
                                            ? DXVA2FixedToFloat(brightnessRange.MinValue) : DXVA2FixedToFloat(brightnessRange.MaxValue))
                                           - DXVA2FixedToFloat(brightnessRange.DefaultValue)) * qAbs(brightness) + DXVA2FixedToFloat(brightnessRange.DefaultValue));
    values.Saturation = DXVA2FloatToFixed(((saturation < 0
                                            ? DXVA2FixedToFloat(saturationRange.MinValue) : DXVA2FixedToFloat(saturationRange.MaxValue))
                                           - DXVA2FixedToFloat(saturationRange.DefaultValue)) * qAbs(saturation) + DXVA2FixedToFloat(saturationRange.DefaultValue));
    values.Hue = DXVA2FloatToFixed(((hue < 0
                                     ? DXVA2FixedToFloat(hueRange.MinValue) : DXVA2FixedToFloat(hueRange.MaxValue))
                                    - DXVA2FixedToFloat(hueRange.DefaultValue)) * qAbs(hue) + DXVA2FixedToFloat(hueRange.DefaultValue));

    //finally set the settings
    processor->SetProcAmpValues(DXVA2_ProcAmp_Contrast | DXVA2_ProcAmp_Brightness | DXVA2_ProcAmp_Saturation | DXVA2_ProcAmp_Hue, &values);

}