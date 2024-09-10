void TalonSRXUtils::TalonSRXFaultDump(const char *talonName, std::shared_ptr<WPI_TalonSRX> talonSRX) {
	int				fwVersion = 0;
	ErrorCode		error = OKAY;
	Faults			faults;
	StickyFaults	stickyFaults;

	// Print out Talon SRX faults and clear sticky ones
	std::printf("2135: %s -------------- %s\n", "Talon SRX", talonName);

    // Check Talon SRX by getting device ID and validating firmware versions
	talonSRX->GetDeviceID();
	if ((error = talonSRX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n",
			talonSRX->GetSubsystem().c_str(), talonSRX->GetName().c_str(), error);
		return;
	}

	fwVersion = talonSRX->GetFirmwareVersion();
	if ((error = talonSRX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetFirmwareVersion error - %d\n",
			talonSRX->GetSubsystem().c_str(), talonSRX->GetName().c_str(), error);
		return;
	}
	if (fwVersion != m_reqVersion) {
		std::printf("2135: WARNING: %s Motor %s Incorrect FW version %d.%d expected %d.%d\n",
			talonSRX->GetSubsystem().c_str(), talonSRX->GetName().c_str(), fwVersion/256, fwVersion%256, m_reqVersion/256, m_reqVersion%256);
		return;
	}

	// Now the Talon has been validated
	talonSRX->GetFaults(faults);
	talonSRX->GetStickyFaults(stickyFaults);
	talonSRX->ClearStickyFaults(100);

	if (faults.HasAnyFault()) {
		std::printf("At Least one fault below\n");
	if (faults.ForwardLimitSwitch)
		std::printf("\tForwardLimitSwitch\n");
	if (faults.ForwardSoftLimit)
		std::printf("\tForwardSoftLimit\n");
	if (faults.HardwareESDReset)
		std::printf("\tHardwareESDReset\n");
	if (faults.HardwareFailure)
		std::printf("\tHardwareFailure\n");
	if (faults.RemoteLossOfSignal)
		std::printf("\tRemoteLossOfSignal\n");
	if (faults.ResetDuringEn)
		std::printf("\tResetDuringEn\n");
	if (faults.ReverseLimitSwitch)
		std::printf("\tReverseLimitSwitch\n");
	if (faults.ReverseSoftLimit)
		std::printf("\tReverseSoftLimit\n");
	if  (faults.SensorOutOfPhase)
		std::printf("\tSensorOutOfPhase\n");
	if (faults.SensorOverflow)
		std::printf("\tSensorOverflow\n");
	if (faults.UnderVoltage)
		std::printf("\tUnderVoltage\n");
	}
	else {
		std::printf("2135: NO Talon SRX active faults detected\n");
	}

	if (stickyFaults.HasAnyFault()) {
		std::printf("At Least one STICKY fault below\n");
	if (stickyFaults.ForwardLimitSwitch)
		std::printf("\tForwardLimitSwitch\n");
	if (stickyFaults.ForwardSoftLimit)
		std::printf("\tForwardSoftLimit\n");
	if (stickyFaults.HardwareESDReset)
		std::printf("\tHardwareESDReset\n");
//	if (stickyFaults.HardwareFailure)
//		std::printf("\tHardwareFailure\n");
	if (stickyFaults.RemoteLossOfSignal)
		std::printf("\tRemoteLossOfSignal\n");
	if (stickyFaults.ResetDuringEn)
		std::printf("\tResetDuringEn\n");
	if (stickyFaults.ReverseLimitSwitch)
		std::printf("\tReverseLimitSwitch\n");
	if (stickyFaults.ReverseSoftLimit)
		std::printf("\tReverseSoftLimit\n");
	if  (stickyFaults.SensorOutOfPhase)
		std::printf("\tSensorOutOfPhase\n");
	if (stickyFaults.SensorOverflow)
		std::printf("\tSensorOverflow\n");
	if (stickyFaults.UnderVoltage)
		std::printf("\tUnderVoltage\n");
	}
	else {
		std::printf("2135: NO Talon SRX sticky faults detected\n");
	}
}