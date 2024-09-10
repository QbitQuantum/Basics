static
ISTATUS
AttenuatedSumReflectorGetAlbedo(
    _In_ const void *context,
    _Out_ float_t *reflectance
    )
{
    PCATTENUATED_SUM_REFLECTOR reflector = (PCATTENUATED_SUM_REFLECTOR)context;

    float_t added_albedo;
    ISTATUS status = ReflectorGetAlbedoInline(reflector->added_reflector,
                                              &added_albedo);

    if (status != ISTATUS_SUCCESS)
    {
        return status;
    }

    status = ReflectorGetAlbedoInline(reflector->attenuated_reflector,
                                      reflectance);

    if (status != ISTATUS_SUCCESS)
    {
        return status;
    }

    *reflectance = fma(reflector->attenuation,
                       *reflectance,
                       added_albedo);

    return ISTATUS_SUCCESS;
}