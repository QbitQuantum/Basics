/**
 * RTMpPokeCpu worker that uses the Vista and earlier version of HalRequestIpip
 * to get the job done.
 *
 * @returns VINF_SUCCESS
 * @param   idCpu           The CPU identifier.
 */
int rtMpPokeCpuUsingHalReqestIpiPreW7(RTCPUID idCpu)
{
    __debugbreak(); /** @todo this code needs testing!!  */
    KAFFINITY Target = 1;
    Target <<= idCpu;
    g_pfnrtHalRequestIpiPreW7(Target);
    return VINF_SUCCESS;
}