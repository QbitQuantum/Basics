inline BOOL   Effect::GetDefaultTexture(HANDLE hObject, String &value) const
{
    assert(hObject);

    EffectParam *param = ConvertParam(hObject);
    if(!param || !param->DefaultValue.Num()) return FALSE;

    BufferInputSerializer sIn(param->DefaultValue);
    sIn << value;
    return TRUE;
}