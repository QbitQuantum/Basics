/// <summary>
/// Check if VT-x is supported
/// </summary>
/// <returns>TRUE if supported</returns>
BOOLEAN VmxHardSupported()
{
    CPUID data = { 0 };

    // VMX bit
    __cpuid( (int*)&data, 1 );
    if ((data.ecx & (1 << 5)) == 0)
        return FALSE;

    IA32_FEATURE_CONTROL_MSR Control = { 0 };
    Control.All = __readmsr( MSR_IA32_FEATURE_CONTROL );

    // BIOS lock check
    if (Control.Fields.Lock == 0)
    {
        Control.Fields.Lock = TRUE;
        Control.Fields.EnableVmxon = TRUE;
        __writemsr( MSR_IA32_FEATURE_CONTROL, Control.All );
    }
    else if (Control.Fields.EnableVmxon == FALSE)
    {
        DPRINT( "HyperBone: CPU %d: %s: VMX locked off in BIOS\n", CPU_IDX, __FUNCTION__ );
        return FALSE;
    }

    return TRUE;
}