BOOL
ShowDeviceProblemWizard(IN HWND hWndParent  OPTIONAL,
                        IN HDEVINFO hDevInfo,
                        IN PSP_DEVINFO_DATA DevInfoData,
                        IN HMACHINE hMachine  OPTIONAL)
{
    CONFIGRET cr;
    ULONG Status, ProblemNumber;
    BOOL Ret = FALSE;

    cr = CM_Get_DevNode_Status_Ex(&Status,
                                  &ProblemNumber,
                                  DevInfoData->DevInst,
                                  0,
                                  hMachine);
    if (cr == CR_SUCCESS && (Status & DN_HAS_PROBLEM))
    {
        switch (ProblemNumber)
        {
            case CM_PROB_DEVLOADER_FAILED:
            {
                /* FIXME - only if it's not a root bus devloader */
                /* FIXME - display the update driver wizard */
                break;
            }

            case CM_PROB_OUT_OF_MEMORY:
            case CM_PROB_ENTRY_IS_WRONG_TYPE:
            case CM_PROB_LACKED_ARBITRATOR:
            case CM_PROB_FAILED_START:
            case CM_PROB_LIAR:
            case CM_PROB_UNKNOWN_RESOURCE:
            {
                /* FIXME - display the update driver wizard */
                break;
            }

            case CM_PROB_BOOT_CONFIG_CONFLICT:
            case CM_PROB_NORMAL_CONFLICT:
            case CM_PROB_REENUMERATION:
            {
                /* FIXME - display the conflict wizard */
                break;
            }

            case CM_PROB_FAILED_FILTER:
            case CM_PROB_REINSTALL:
            case CM_PROB_FAILED_INSTALL:
            {
                /* FIXME - display the driver (re)installation wizard */
                break;
            }

            case CM_PROB_DEVLOADER_NOT_FOUND:
            {
                /* FIXME - 4 cases:
                   1) if it's a missing system devloader:
                      - fail
                   2) if it's not a system devloader but still missing:
                      - display the driver reinstallation wizard
                   3) if it's not a system devloader but the file can be found:
                      - display the update driver wizard
                   4) if it's a missing or empty software key
                      - display the update driver wizard
                 */
                break;
            }

            case CM_PROB_INVALID_DATA:
            case CM_PROB_PARTIAL_LOG_CONF:
            case CM_PROB_NO_VALID_LOG_CONF:
            case CM_PROB_HARDWARE_DISABLED:
            case CM_PROB_CANT_SHARE_IRQ:
            case CM_PROB_TRANSLATION_FAILED:
            case CM_PROB_SYSTEM_SHUTDOWN:
            case CM_PROB_PHANTOM:
                /* FIXME - do nothing */
                break;

            case CM_PROB_NOT_VERIFIED:
            case CM_PROB_DEVICE_NOT_THERE:
                /* FIXME - display search hardware wizard */
                break;

            case CM_PROB_NEED_RESTART:
            case CM_PROB_WILL_BE_REMOVED:
            case CM_PROB_MOVED:
            case CM_PROB_TOO_EARLY:
            case CM_PROB_DISABLED_SERVICE:
                /* FIXME - reboot computer */
                break;

            case CM_PROB_REGISTRY:
                /* FIXME - check registry */
                break;

            case CM_PROB_DISABLED:
            {
                /* FIXME - if device was disabled by user display the "Enable Device" wizard,
                           otherwise Troubleshoot because the device was disabled by the system */
                break;
            }

            case CM_PROB_DEVLOADER_NOT_READY:
            {
                /* FIXME - if it's a graphics adapter:
                           - if it's a a secondary adapter and the main adapter
                             couldn't be found
                             - do nothing or default action
                           - else
                             - display the Properties
                         - else
                           - Update driver
                 */
                break;
            }

            case CM_PROB_FAILED_ADD:
            {
                /* FIXME - display the properties of the sub-device */
                break;
            }

            case CM_PROB_NO_SOFTCONFIG:
            case CM_PROB_IRQ_TRANSLATION_FAILED:
            case CM_PROB_FAILED_DRIVER_ENTRY:
            case CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD:
            case CM_PROB_DRIVER_FAILED_LOAD:
            case CM_PROB_DRIVER_SERVICE_KEY_INVALID:
            case CM_PROB_LEGACY_SERVICE_NO_DEVICES:
            case CM_PROB_DUPLICATE_DEVICE:
            case CM_PROB_FAILED_POST_START:
            case CM_PROB_HALTED:
            case CM_PROB_HELD_FOR_EJECT:
            case CM_PROB_DRIVER_BLOCKED:
            case CM_PROB_REGISTRY_TOO_LARGE:
            default:
            {
                /* FIXME - troubleshoot the device */
                break;
            }
        }
    }

    return Ret;
}