ULONG
DeviceAtaHealthInfo(
    _In_ PDEVICE_LIST     DeviceList,
    _In_ ULONG            DeviceIndex
    )
{
    ULONG                status = ERROR_SUCCESS;
    ATA_PT               ataPt = {0};
    PATA_PASS_THROUGH_EX passThru = &ataPt.AtaPassThrough;
    ULONG                bytesReturned = 0;

    PUSHORT                            logpages = (PUSHORT)ataPt.Buffer;
    PDEVICE_STATISTICS_LOG_PAGE_HEADER pageHeader = (PDEVICE_STATISTICS_LOG_PAGE_HEADER)ataPt.Buffer;
    PUCHAR                             pageSupported = (PUCHAR)ataPt.Buffer;

    BOOLEAN     generalPage = FALSE;
    BOOLEAN     freeFallPage = FALSE;
    BOOLEAN     rotatingMediaPage = FALSE;
    BOOLEAN     generalErrorPage = FALSE;
    BOOLEAN     temperaturePage = FALSE;
    BOOLEAN     transportPage = FALSE;
    BOOLEAN     ssdPage = FALSE;
    BOOLEAN     vendorSpecificPage = FALSE;

    int         i = 0;

    //
    // Get Log Directory to see if it supports Device Statistics
    //
    BuildReadLogExCommand(passThru, IDE_GP_LOG_DIRECTORY_ADDRESS, 0, 1, 0);

    bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                       passThru,
                                       sizeof(ATA_PT),
                                       sizeof(ATA_PT),
                                       FALSE
                                       );

    if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
        status = ERROR_INVALID_DATA;
        goto exit;
    }

    _tprintf(_T("\n\tATA - Info from Device Statistics Log:\n\n"));

    if (logpages[0] != 1) {
        _tprintf(_T("\t Warning: Log Directory Version is not 0x0001. Reported value: %d\n"), logpages[0]);
    }
/*
    if (logpages[IDE_GP_SUMMARY_SMART_ERROR] > 0) {
        _tprintf(_T("\t Log Page: Smart Error Page Count: %d\n"), logpages[IDE_GP_SUMMARY_SMART_ERROR]);
    }

    if (logpages[IDE_GP_COMPREHENSIVE_SMART_ERROR] > 0) {
        _tprintf(_T("\t Log Page: Comprehensive Smart Error Page Count: %d\n"), logpages[IDE_GP_COMPREHENSIVE_SMART_ERROR]);
    }

    if (logpages[IDE_GP_EXTENDED_COMPREHENSIVE_SMART_ERROR] > 0) {
        _tprintf(_T("\t Log Page: Extended Comprehensive Smart Error Page Count: %d\n"), logpages[IDE_GP_EXTENDED_COMPREHENSIVE_SMART_ERROR]);
    }
*/

    if (logpages[IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS] == 0) {
        status = ERROR_INVALID_DATA;
        _tprintf(_T("\t Error: Not support Device Statistics Log.\n"));
        goto exit;
    }

    //_tprintf(_T("\t Log Page: Device Statistics Page Count: %d\n"), logpages[IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS]);

    //
    // Get supported Device Statistics log pages
    //
    ZeroMemory(&ataPt, sizeof(ATA_PT));

    BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, 0, 1, 0);

    bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                       passThru,
                                       sizeof(ATA_PT),
                                       sizeof(ATA_PT),
                                       FALSE
                                       );

    if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
        status = ERROR_INVALID_DATA;
        _tprintf(_T("\t Error: Couldn't get Device Statistics Log supported pages.\n"));
        goto exit;
    }


    // first byte after header is how many entries in following list.
    UCHAR pageCount = *(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER));

    // The value of revision number word shall be 0001h. The first supported page shall be 00h.
    if ((pageHeader->RevisionNumber != IDE_GP_LOG_VERSION) ||
        (pageHeader->PageNumber != IDE_GP_LOG_SUPPORTED_PAGES) ||
        (pageCount == 0)) {

        status = ERROR_INVALID_DATA;
        _tprintf(_T("\t Error: Device Statistics - Supported Page data not valid.\n"));
        goto exit;
    }

    // if the page number is shown in supported list, mark it's supported.
    for (i = 1; i <= pageCount; i++) {
        if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == IDE_GP_LOG_DEVICE_STATISTICS_GENERAL_PAGE) {
            generalPage = TRUE;
        } else if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == IDE_GP_LOG_DEVICE_STATISTICS_FREE_FALL_PAGE) {
            freeFallPage = TRUE;
        } else if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == IDE_GP_LOG_DEVICE_STATISTICS_ROTATING_MEDIA_PAGE) {
            rotatingMediaPage = TRUE;
        } else if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == IDE_GP_LOG_DEVICE_STATISTICS_GENERAL_ERROR_PAGE) {
            generalErrorPage = TRUE;
        } else if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == IDE_GP_LOG_DEVICE_STATISTICS_TEMPERATURE_PAGE) {
            temperaturePage = TRUE;
        } else if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == IDE_GP_LOG_DEVICE_STATISTICS_TRANSPORT_PAGE) {
            transportPage = TRUE;
        } else if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == IDE_GP_LOG_DEVICE_STATISTICS_SSD_PAGE) {
            ssdPage = TRUE;
        } else if (*(pageSupported + sizeof(DEVICE_STATISTICS_LOG_PAGE_HEADER) + i) == 0xFF) {
            vendorSpecificPage = TRUE;
        }
    }

    if (temperaturePage) {
        ZeroMemory(&ataPt, sizeof(ATA_PT));

        BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, IDE_GP_LOG_DEVICE_STATISTICS_TEMPERATURE_PAGE, 1, 0);

        bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                           passThru,
                                           sizeof(ATA_PT),
                                           sizeof(ATA_PT),
                                           FALSE
        );

        PGP_LOG_TEMPERATURE_STATISTICS temperaturelLog = (PGP_LOG_TEMPERATURE_STATISTICS)ataPt.Buffer;

        if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
            status = ERROR_INVALID_DATA;
            _tprintf(_T("\t Error: Couldn't get Device Statistics Log Temperature Page.\n"));
        } else if (//(generalLog->Header.RevisionNumber != IDE_GP_LOG_VERSION) ||
            (temperaturelLog->Header.PageNumber != IDE_GP_LOG_DEVICE_STATISTICS_TEMPERATURE_PAGE)) {
            status = ERROR_INVALID_DATA;
            //_tprintf(_T("\t Error: Couldn't get Device Statistics Log Temperature Page.\n"));
        } else {
            if ((temperaturelLog->CurrentTemperature.Supported == 1) && (temperaturelLog->CurrentTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Current Temperature: %I64d\n"), temperaturelLog->CurrentTemperature.Value);
            }

            if ((temperaturelLog->HighestTemperature.Supported == 1) && (temperaturelLog->HighestTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Highest Temperature: %I64d\n"), temperaturelLog->HighestTemperature.Value);
            }

            if ((temperaturelLog->LowestTemperature.Supported == 1) && (temperaturelLog->LowestTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Lowest Temperature: %I64d\n"), temperaturelLog->LowestTemperature.Value);
            }

            if ((temperaturelLog->AverageShortTermTemperature.Supported == 1) && (temperaturelLog->AverageShortTermTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Average Short Term Temperature: %I64d\n"), temperaturelLog->AverageShortTermTemperature.Value);
            }

            if ((temperaturelLog->AverageLongTermTemperature.Supported == 1) && (temperaturelLog->AverageLongTermTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Average Long Term Temperature: %I64d\n"), temperaturelLog->AverageLongTermTemperature.Value);
            }

            if ((temperaturelLog->HighestAverageShortTermTemperature.Supported == 1) && (temperaturelLog->HighestAverageShortTermTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Highest Average Short TermTemperature: %I64d\n"), temperaturelLog->HighestAverageShortTermTemperature.Value);
            }

            if ((temperaturelLog->LowestAverageShortTermTemperature.Supported == 1) && (temperaturelLog->LowestAverageShortTermTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Lowest Average Short Term Temperature: %I64d\n"), temperaturelLog->LowestAverageShortTermTemperature.Value);
            }

            if ((temperaturelLog->HighstAverageLongTermTemperature.Supported == 1) && (temperaturelLog->HighstAverageLongTermTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Highst Average Long Term Temperature: %I64d\n"), temperaturelLog->HighstAverageLongTermTemperature.Value);
            }

            if ((temperaturelLog->LowestAverageLongTermTemperature.Supported == 1) && (temperaturelLog->LowestAverageLongTermTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Lowest Average Long Term Temperature: %I64d\n"), temperaturelLog->LowestAverageLongTermTemperature.Value);
            }

            if ((temperaturelLog->TimeInOverTemperature.Supported == 1) && (temperaturelLog->TimeInOverTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Time In Over Temperature (Minutes): %I64d\n"), temperaturelLog->TimeInOverTemperature.Value);
            }

            if ((temperaturelLog->SpecifiedMaximumOperatingTemperature.Supported == 1) && (temperaturelLog->SpecifiedMaximumOperatingTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Specified Maximum Operating Temperature: %I64d\n"), temperaturelLog->SpecifiedMaximumOperatingTemperature.Value);
            }

            if ((temperaturelLog->TimeInUnderTemperature.Supported == 1) && (temperaturelLog->TimeInUnderTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Time In Under Temperature (Minutes): %I64d\n"), temperaturelLog->TimeInUnderTemperature.Value);
            }

            if ((temperaturelLog->SpecifiedMinimumOperatingTemperature.Supported == 1) && (temperaturelLog->SpecifiedMinimumOperatingTemperature.ValidValue == 1)) {
                _tprintf(_T("\t Specified Minimum Operating Temperature: %I64d\n"), temperaturelLog->SpecifiedMinimumOperatingTemperature.Value);
            }

            _tprintf(_T(" \n"));
        }
    }

    if (generalPage) {
        ZeroMemory(&ataPt, sizeof(ATA_PT));

        BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, IDE_GP_LOG_DEVICE_STATISTICS_GENERAL_PAGE, 1, 0);

        bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                           passThru,
                                           sizeof(ATA_PT),
                                           sizeof(ATA_PT),
                                           FALSE
        );

        PGP_LOG_GENERAL_STATISTICS generalLog = (PGP_LOG_GENERAL_STATISTICS)ataPt.Buffer;

        if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
            status = ERROR_INVALID_DATA;
            _tprintf(_T("\t Error: Couldn't get Device Statistics Log general page.\n"));
        } else if (//(generalLog->Header.RevisionNumber != IDE_GP_LOG_VERSION) ||
            (generalLog->Header.PageNumber != IDE_GP_LOG_DEVICE_STATISTICS_GENERAL_PAGE)) {
            status = ERROR_INVALID_DATA;
            //_tprintf(_T("\t Error: Couldn't get Device Statistics Log general page.\n"));
        } else {
            if ((generalLog->LifeTimePoweronResets.Supported == 1) && (generalLog->LifeTimePoweronResets.ValidValue == 1)) {
                _tprintf(_T("\t Power-on Reset Count: %I64d\n"), generalLog->LifeTimePoweronResets.Count);
            }

            if ((generalLog->PoweronHours.Supported == 1) && (generalLog->PoweronHours.ValidValue == 1)) {
                _tprintf(_T("\t Power-on Hours: %I64d\n"), generalLog->PoweronHours.Count);
            }

            if ((generalLog->LogicalSectorsWritten.Supported == 1) && (generalLog->LogicalSectorsWritten.ValidValue == 1)) {
                _tprintf(_T("\t Logical Sectors Written: %I64d\n"), generalLog->LogicalSectorsWritten.Count);
            }

            if ((generalLog->WriteCommandCount.Supported == 1) && (generalLog->WriteCommandCount.ValidValue == 1)) {
                _tprintf(_T("\t Write Command Count: %I64d\n"), generalLog->WriteCommandCount.Count);
            }

            if ((generalLog->LogicalSectorsRead.Supported == 1) && (generalLog->LogicalSectorsRead.ValidValue == 1)) {
                _tprintf(_T("\t Logical Sectors Read: %I64d\n"), generalLog->LogicalSectorsRead.Count);
            }

            if ((generalLog->ReadCommandCount.Supported == 1) && (generalLog->ReadCommandCount.ValidValue == 1)) {
                _tprintf(_T("\t Read Command Count: %I64d\n"), generalLog->ReadCommandCount.Count);
            }

            if ((generalLog->DateAndTime.Supported == 1) && (generalLog->DateAndTime.ValidValue == 1)) {
                // convert the value to system time

                SYSTEMTIME systemTime = {0};
                TCHAR localDate[255] = {0};
                TCHAR localTime[255] = {0};

                ULONGLONG time = generalLog->DateAndTime.TimeStamp + 0xA9741731300;

                time *= 10000;

                FileTimeToLocalFileTime((LPFILETIME)&time, (LPFILETIME)&time);
                FileTimeToSystemTime((LPFILETIME)&time, &systemTime);

                GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &systemTime, NULL, localDate, 255);
                GetTimeFormat(LOCALE_USER_DEFAULT, 0, &systemTime, NULL, localTime, 255);

                _tprintf(_T("\t Time Stamp: %s %s\n"), localDate, localTime);
            }

            if ((generalLog->PendingErrorCount.Supported == 1) && (generalLog->PendingErrorCount.ValidValue == 1)) {
                _tprintf(_T("\t Pending Error Sectors Count: %I64d\n"), generalLog->PendingErrorCount.Count);
            }

            if ((generalLog->WorkloadUtilizaton.Supported == 1) && (generalLog->WorkloadUtilizaton.ValidValue == 1)) {
                _tprintf(_T("\t Workload Utilization Percentage: %I64d\n"), generalLog->WorkloadUtilizaton.Value);
            }

            if ((generalLog->UtilizationUsageRate.Supported == 1) && (generalLog->UtilizationUsageRate.ValidValue == 1)) {

                if (generalLog->UtilizationUsageRate.RateValidity == 0x00) {
                    //valid
                    _tprintf(_T("\t Utilization Usage Rate Percentagge: %I64d"), generalLog->UtilizationUsageRate.Value);

                    if (generalLog->UtilizationUsageRate.RateBasis == 0x0) {
                        _tprintf(_T(" (Based on the time of manufacture until the time indicated by the Date and Time TimeStamp device statistic, including times during which the device was powered off.) \n"));
                    } else if (generalLog->UtilizationUsageRate.RateBasis == 0x4) {
                        _tprintf(_T(" (Based on the time elapsed since the most recent processing of a power-on reset.) \n"));
                    } else if (generalLog->UtilizationUsageRate.RateBasis == 0x8) {
                        _tprintf(_T(" (Based on the Power-on Hours device statistic.) \n"));
                    } else if (generalLog->UtilizationUsageRate.RateBasis == 0xF) {
                        _tprintf(_T(" (Basis is undetermined.) \n"));
                    } else {
                        _tprintf(_T(" (Basis is not a valid value.) \n"));
                    }

                } else if (generalLog->UtilizationUsageRate.RateValidity == 0x10) {
                    _tprintf(_T("\t UTILIZATION USAGE RATE field is not valid because insufficient information has been collected about the workload utilization.\n"));
                } else if (generalLog->UtilizationUsageRate.RateValidity == 0x81) {
                    _tprintf(_T("\t UTILIZATION USAGE RATE field is not valid because the most recently processed SET DATE & TIME command specified a timestamp resulted in usage rate that is unreasonable.\n"));
                } else if (generalLog->UtilizationUsageRate.RateValidity == 0xFF) {
                    _tprintf(_T("\t UTILIZATION USAGE RATE field is not valid for an undetermined reason.\n"));
                } else {
                    _tprintf(_T("\t UTILIZATION USAGE RATE field is not valid because Rate Validity field has invalid value.\n"));
                }
            }

            _tprintf(_T(" \n"));
        }
    }

    if (ssdPage) {
        ZeroMemory(&ataPt, sizeof(ATA_PT));

        BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, IDE_GP_LOG_DEVICE_STATISTICS_SSD_PAGE, 1, 0);

        bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                           passThru,
                                           sizeof(ATA_PT),
                                           sizeof(ATA_PT),
                                           FALSE
        );

        PGP_LOG_SOLID_STATE_DEVICE_STATISTICS ssdLog = (PGP_LOG_SOLID_STATE_DEVICE_STATISTICS)ataPt.Buffer;

        if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
            status = ERROR_INVALID_DATA;
            _tprintf(_T("\t Error: Couldn't get Device Statistics Log SSD Page.\n"));
        } else if (//(generalLog->Header.RevisionNumber != IDE_GP_LOG_VERSION) ||
            (ssdLog->Header.PageNumber != IDE_GP_LOG_DEVICE_STATISTICS_SSD_PAGE)) {
            status = ERROR_INVALID_DATA;
            //_tprintf(_T("\t Error: Couldn't get Device Statistics Log SSD Page.\n"));
        } else {
            if ((ssdLog->PercentageUsedEnduranceIndicator.Supported == 1) && (ssdLog->PercentageUsedEnduranceIndicator.ValidValue == 1)) {
                _tprintf(_T("\t Percentage Used Endurance Indicator: %I64d\n"), ssdLog->PercentageUsedEnduranceIndicator.Value);
            }

            _tprintf(_T(" \n"));
        }
    }

    if (generalErrorPage) {
        ZeroMemory(&ataPt, sizeof(ATA_PT));

        BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, IDE_GP_LOG_DEVICE_STATISTICS_GENERAL_ERROR_PAGE, 1, 0);

        bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                           passThru,
                                           sizeof(ATA_PT),
                                           sizeof(ATA_PT),
                                           FALSE
        );

        PGP_LOG_GENERAL_ERROR_STATISTICS generalErrorlLog = (PGP_LOG_GENERAL_ERROR_STATISTICS)ataPt.Buffer;

        if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
            status = ERROR_INVALID_DATA;
            _tprintf(_T("\t Error: Couldn't get Device Statistics Log General Error Page.\n"));
        } else if (//(generalLog->Header.RevisionNumber != IDE_GP_LOG_VERSION) ||
            (generalErrorlLog->Header.PageNumber != IDE_GP_LOG_DEVICE_STATISTICS_GENERAL_ERROR_PAGE)) {
            status = ERROR_INVALID_DATA;
            //_tprintf(_T("\t Error: Couldn't get Device Statistics Log General Error Page.\n"));
        } else {
            if ((generalErrorlLog->NumberOfReportedUncorrectableErrors.Supported == 1) && (generalErrorlLog->NumberOfReportedUncorrectableErrors.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Reported Uncorrectable Errors: %I64d\n"), generalErrorlLog->NumberOfReportedUncorrectableErrors.Count);
            }

            if ((generalErrorlLog->NumberOfResetsBetweenCommandAcceptanceAndCommandCompletion.Supported == 1) && (generalErrorlLog->NumberOfResetsBetweenCommandAcceptanceAndCommandCompletion.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Resets Between Command Acceptance And Command Completion: %I64d\n"), generalErrorlLog->NumberOfResetsBetweenCommandAcceptanceAndCommandCompletion.Count);
            }

            _tprintf(_T(" \n"));
        }
    }

    if (freeFallPage) {
        ZeroMemory(&ataPt, sizeof(ATA_PT));

        BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, IDE_GP_LOG_DEVICE_STATISTICS_FREE_FALL_PAGE, 1, 0);

        bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                           passThru,
                                           sizeof(ATA_PT),
                                           sizeof(ATA_PT),
                                           FALSE
        );

        PGP_LOG_FREE_FALL_STATISTICS freeFallLog = (PGP_LOG_FREE_FALL_STATISTICS)ataPt.Buffer;

        if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
            status = ERROR_INVALID_DATA;
            _tprintf(_T("\t Error: Couldn't get Device Statistics Log Free Fall Page.\n"));
        } else if (//(generalLog->Header.RevisionNumber != IDE_GP_LOG_VERSION) ||
            (freeFallLog->Header.PageNumber != IDE_GP_LOG_DEVICE_STATISTICS_FREE_FALL_PAGE)) {
            status = ERROR_INVALID_DATA;
            //_tprintf(_T("\t Error: Couldn't get Device Statistics Log Free Fall Page.\n"));
        } else {
            if ((freeFallLog->NumberofFreeFallEventsDetected.Supported == 1) && (freeFallLog->NumberofFreeFallEventsDetected.ValidValue == 1)) {
                _tprintf(_T("\t Number of Free Fall Events Detected: %I64d\n"), freeFallLog->NumberofFreeFallEventsDetected.Count);
            }

            if ((freeFallLog->OverlimitShockEvents.Supported == 1) && (freeFallLog->OverlimitShockEvents.ValidValue == 1)) {
                _tprintf(_T("\t Over limit Shock Events: %I64d\n"), freeFallLog->OverlimitShockEvents.Count);
            }

            _tprintf(_T(" \n"));
        }
    }

    if (rotatingMediaPage) {
        ZeroMemory(&ataPt, sizeof(ATA_PT));

        BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, IDE_GP_LOG_DEVICE_STATISTICS_ROTATING_MEDIA_PAGE, 1, 0);

        bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                           passThru,
                                           sizeof(ATA_PT),
                                           sizeof(ATA_PT),
                                           FALSE
        );

        PGP_LOG_ROTATING_MEDIA_STATISTICS rotatingMediaLog = (PGP_LOG_ROTATING_MEDIA_STATISTICS)ataPt.Buffer;

        if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
            status = ERROR_INVALID_DATA;
            _tprintf(_T("\t Error: Couldn't get Device Statistics Log Rotating Media Page.\n"));
        } else if (//(generalLog->Header.RevisionNumber != IDE_GP_LOG_VERSION) ||
            (rotatingMediaLog->Header.PageNumber != IDE_GP_LOG_DEVICE_STATISTICS_ROTATING_MEDIA_PAGE)) {
            status = ERROR_INVALID_DATA;
            //_tprintf(_T("\t Error: Couldn't get Device Statistics Log Rotating Media Page.\n"));
        } else {
            if ((rotatingMediaLog->SpindleMotorPoweronHours.Supported == 1) && (rotatingMediaLog->SpindleMotorPoweronHours.ValidValue == 1)) {
                _tprintf(_T("\t Spindle Motor Power-on Hours: %I64d\n"), rotatingMediaLog->SpindleMotorPoweronHours.Count);
            }

            if ((rotatingMediaLog->HeadFlyingHours.Supported == 1) && (rotatingMediaLog->HeadFlyingHours.ValidValue == 1)) {
                _tprintf(_T("\t Head Flying Hours: %I64d\n"), rotatingMediaLog->HeadFlyingHours.Count);
            }

            if ((rotatingMediaLog->HeadLoadEvents.Supported == 1) && (rotatingMediaLog->HeadLoadEvents.ValidValue == 1)) {
                _tprintf(_T("\t Head Load Events: %I64d\n"), rotatingMediaLog->HeadLoadEvents.Count);
            }

            if ((rotatingMediaLog->NumberOfReallocatedLogicalSectors.Supported == 1) && (rotatingMediaLog->NumberOfReallocatedLogicalSectors.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Reallocated Logical Sectors: %I64d\n"), rotatingMediaLog->NumberOfReallocatedLogicalSectors.Count);
            }

            if ((rotatingMediaLog->ReadRecoveryAttempts.Supported == 1) && (rotatingMediaLog->ReadRecoveryAttempts.ValidValue == 1)) {
                _tprintf(_T("\t Read Recovery Attempts: %I64d\n"), rotatingMediaLog->ReadRecoveryAttempts.Count);
            }

            if ((rotatingMediaLog->NumberOfMechanicalStartFailures.Supported == 1) && (rotatingMediaLog->NumberOfMechanicalStartFailures.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Mechanical Start Failures: %I64d\n"), rotatingMediaLog->NumberOfMechanicalStartFailures.Count);
            }

            if ((rotatingMediaLog->NumberOfReallocationCandidateLogicalSectors.Supported == 1) && (rotatingMediaLog->NumberOfReallocationCandidateLogicalSectors.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Reallocation Candidate Logical Sectors: %I64d\n"), rotatingMediaLog->NumberOfReallocationCandidateLogicalSectors.Count);
            }

            if ((rotatingMediaLog->NumberOfHighPriorityUnloadEvents.Supported == 1) && (rotatingMediaLog->NumberOfHighPriorityUnloadEvents.ValidValue == 1)) {
                _tprintf(_T("\t Number Of High Priority Unload Events: %I64d\n"), rotatingMediaLog->NumberOfHighPriorityUnloadEvents.Count);
            }

            _tprintf(_T(" \n"));
        }
    }

    if (transportPage) {
        ZeroMemory(&ataPt, sizeof(ATA_PT));

        BuildReadLogExCommand(passThru, IDE_GP_LOG_DEVICE_STATISTICS_ADDRESS, IDE_GP_LOG_DEVICE_STATISTICS_TRANSPORT_PAGE, 1, 0);

        bytesReturned = AtaSendPassThrough(DeviceList[DeviceIndex].Handle,
                                           passThru,
                                           sizeof(ATA_PT),
                                           sizeof(ATA_PT),
                                           FALSE
        );

        PGP_LOG_TRANSPORT_STATISTICS transportLog = (PGP_LOG_TRANSPORT_STATISTICS)ataPt.Buffer;

        if (bytesReturned < (FIELD_OFFSET(ATA_PT, Buffer) + IDE_GP_LOG_SECTOR_SIZE)) {
            status = ERROR_INVALID_DATA;
            _tprintf(_T("\t Error: Couldn't get Device Statistics Log Transport Page.\n"));
        } else if (//(generalLog->Header.RevisionNumber != IDE_GP_LOG_VERSION) ||
            (transportLog->Header.PageNumber != IDE_GP_LOG_DEVICE_STATISTICS_TRANSPORT_PAGE)) {
            status = ERROR_INVALID_DATA;
            //_tprintf(_T("\t Error: Couldn't get Device Statistics Log Transport Page.\n"));
        } else {
            if ((transportLog->NumberOfHardwareResets.Supported == 1) && (transportLog->NumberOfHardwareResets.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Hardware Resets: %I64d\n"), transportLog->NumberOfHardwareResets.Count);
            }

            if ((transportLog->NumberOfAsrEvents.Supported == 1) && (transportLog->NumberOfAsrEvents.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Asr Events: %I64d\n"), transportLog->NumberOfAsrEvents.Count);
            }

            if ((transportLog->NumberOfInterfaceCrcErrors.Supported == 1) && (transportLog->NumberOfInterfaceCrcErrors.ValidValue == 1)) {
                _tprintf(_T("\t Number Of Interface Crc Errors: %I64d\n"), transportLog->NumberOfInterfaceCrcErrors.Count);
            }

            _tprintf(_T(" \n"));
        }
    }

    _tprintf(_T("\n"));

exit:

    return status;
}