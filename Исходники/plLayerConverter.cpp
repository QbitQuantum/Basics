plLayerInterface* plLayerConverter::IConvertAngleAttenLayer(plPlasmaMAXLayer *layer, 
                                                                plMaxNode *maxNode, uint32_t blendFlags, 
                                                                bool preserveUVOffset, bool upperLayer)
{
    hsGuardBegin( "plPlasmaMAXLayer::IConvertAngleAttenLayer" );
    if( !upperLayer )
    {
        fErrorMsg->Set(true, maxNode->GetName(), "Angle Attenuation layers can only be used as a top layer").Show();
        fErrorMsg->Set();
        return nil;
    }
    plAngleAttenLayer* aaLay = (plAngleAttenLayer*)layer;
    Box3 fade = aaLay->GetFade();
    float tr0 = cosf(DegToRad(180.f - fade.Min().x));
    float op0 = cosf(DegToRad(180.f - fade.Min().y));
    float tr1 = cosf(DegToRad(180.f - fade.Max().x));
    float op1 = cosf(DegToRad(180.f - fade.Max().y));

    int loClamp = aaLay->GetLoClamp();
    int hiClamp = aaLay->GetHiClamp();

    int uvwSrc = aaLay->Reflect() ? plLayerInterface::kUVWReflect : plLayerInterface::kUVWNormal;

    plLayer* lut = ICreateAttenuationLayer(plString::FromUtf8(layer->GetName()), maxNode, uvwSrc, tr0, op0, tr1, op1, loClamp, hiClamp);

    return lut;

    hsGuardEnd;
}