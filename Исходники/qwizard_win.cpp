QVistaHelper::VistaState QVistaHelper::vistaState()
{
    if (cachedVistaState == Dirty)
        cachedVistaState =
            isCompositionEnabled() ? VistaAero : isThemeActive() ? VistaBasic : Classic;
    return cachedVistaState;
}