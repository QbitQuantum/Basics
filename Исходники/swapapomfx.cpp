//-------------------------------------------------------------------------
// Description:
//
//  GetCurrentEffectsSetting
//      Gets the current aggregate effects-enable setting
//
// Parameters:
//
//  properties - Property store holding configurable effects settings
//
//  pkeyEnable - VT_UI4 property holding an enable/disable setting
//
//  processingMode - Audio processing mode
//
// Return values:
//  LONG - true if the effect is enabled
//
// Remarks:
//  The routine considers the value of the specified property, the well known
//  master PKEY_AudioEndpoint_Disable_SysFx property, and the specified
//  processing mode.If the processing mode is RAW then the effect is off. If
//  PKEY_AudioEndpoint_Disable_SysFx is non-zero then the effect is off.
//
LONG GetCurrentEffectsSetting(IPropertyStore* properties, PROPERTYKEY pkeyEnable, GUID processingMode)
{
    HRESULT hr;
    BOOL enabled;
    PROPVARIANT var;

    PropVariantInit(&var);

    // Get the state of whether channel swap MFX is enabled or not. 

    // Check the master disable property defined by Windows
    hr = properties->GetValue(PKEY_AudioEndpoint_Disable_SysFx, &var);
    enabled = (SUCCEEDED(hr)) && !((var.vt == VT_UI4) && (var.ulVal != 0));

    PropVariantClear(&var);

    // Check the APO's enable property, defined by this APO.
    hr = properties->GetValue(pkeyEnable, &var);
    enabled = enabled && ((SUCCEEDED(hr)) && ((var.vt == VT_UI4) && (var.ulVal != 0)));

    PropVariantClear(&var);

    enabled = enabled && !IsEqualGUID(processingMode, AUDIO_SIGNALPROCESSINGMODE_RAW);

    return (LONG)enabled;
}