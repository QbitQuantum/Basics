int CMMDVMHost::run()
{
	bool ret = m_conf.read();
	if (!ret) {
		::fprintf(stderr, "MMDVMHost: cannot read the .ini file\n");
		return 1;
	}

	ret = ::LogInitialise(m_conf.getLogPath(), m_conf.getLogRoot(), m_conf.getLogDisplay());
	if (!ret) {
		::fprintf(stderr, "MMDVMHost: unable to open the log file\n");
		return 1;
	}

	::LogSetLevel(m_conf.getLogLevel());

	LogInfo(HEADER1);
	LogInfo(HEADER2);
	LogInfo(HEADER3);

	LogMessage("MMDVMHost-%s is starting", VERSION);

	readParams();

	ret = createModem();
	if (!ret)
		return 1;

	createDisplay();

	if (m_dmrEnabled) {
		ret = createDMRNetwork();
		if (!ret)
			return 1;
	}

	CStopWatch stopWatch;
	stopWatch.start();

	CDStarEcho* dstar = NULL;
	if (m_dstarEnabled)
		dstar = new CDStarEcho(2U, 10000U);

	CDMRControl* dmr = NULL;
	if (m_dmrEnabled) {
		unsigned int id        = m_conf.getDMRId();
		unsigned int colorCode = m_conf.getDMRColorCode();
		unsigned int timeout   = m_conf.getTimeout();

		LogInfo("DMR Parameters");
		LogInfo("    Id: %u", id);
		LogInfo("    Color Code: %u", colorCode);
		LogInfo("    Timeout: %us", timeout);

		dmr = new CDMRControl(id, colorCode, timeout, m_modem, m_dmrNetwork, m_display);
	}

	CYSFEcho* ysf = NULL;
	if (m_ysfEnabled)
		ysf = new CYSFEcho(2U, 10000U);

	unsigned char mode = MODE_IDLE;
	CTimer modeTimer(1000U, m_conf.getModeHang());

	m_display->setIdle();

	while (!m_killed) {
		unsigned char data[200U];
		unsigned int len;
		bool ret;

		len = m_modem->readDStarData(data);
		if (dstar != NULL && len > 0U) {
			if (mode == MODE_IDLE && (data[0U] == TAG_HEADER || data[0U] == TAG_DATA)) {
				LogMessage("Mode set to D-Star");
				mode = MODE_DSTAR;
				m_display->setDStar();
				m_modem->setMode(MODE_DSTAR);
				modeTimer.start();
			}
			if (mode != MODE_DSTAR) {
				LogWarning("D-Star data received when in mode %u", mode);
			} else {
				if (data[0U] == TAG_HEADER || data[0U] == TAG_DATA || data[0U] == TAG_EOT) {
					dstar->writeData(data, len);
					modeTimer.start();
				}
			}
		}

		len = m_modem->readDMRData1(data);
		if (dmr != NULL && len > 0U) {
			if (mode == MODE_IDLE) {
				bool ret = dmr->processWakeup(data);
				if (ret) {
					LogMessage("Mode set to DMR");
					mode = MODE_DMR;
					m_display->setDMR();
					// This sets the mode to DMR within the modem
					m_modem->writeDMRStart(true);
					modeTimer.start();
				}
			} else if (mode == MODE_DMR) {
				dmr->writeModemSlot1(data);
				modeTimer.start();
			} else {
				LogWarning("DMR data received when in mode %u", mode);
			}
		}

		len = m_modem->readDMRData2(data);
		if (dmr != NULL && len > 0U) {
			if (mode == MODE_IDLE) {
				bool ret = dmr->processWakeup(data);
				if (ret) {
					LogMessage("Mode set to DMR");
					mode = MODE_DMR;
					m_display->setDMR();
					// This sets the mode to DMR within the modem
					m_modem->writeDMRStart(true);
					modeTimer.start();
				}
			} else if (mode == MODE_DMR) {
				dmr->writeModemSlot2(data);
				modeTimer.start();
			} else {
				LogWarning("DMR data received when in mode %u", mode);
			}
		}

		len = m_modem->readYSFData(data);
		if (ysf != NULL && len > 0U) {
			if (mode == MODE_IDLE && data[0U] == TAG_DATA) {
				LogMessage("Mode set to System Fusion");
				mode = MODE_YSF;
				m_display->setFusion();
				m_modem->setMode(MODE_YSF);
				modeTimer.start();
			}
			if (mode != MODE_YSF) {
				LogWarning("System Fusion data received when in mode %u", mode);
			} else {
				if (data[0U] == TAG_DATA) {
					data[1U] = 0x00U;		// FICH digest
					ysf->writeData(data, len);
					modeTimer.start();
				}
			}
		}

		if (modeTimer.isRunning() && modeTimer.hasExpired()) {
			LogMessage("Mode set to Idle");

			if (mode == MODE_DMR)
				m_modem->writeDMRStart(false);

			mode = MODE_IDLE;
			m_display->setIdle();
			m_modem->setMode(MODE_IDLE);
			modeTimer.stop();
		}

		if (dstar != NULL) {
			ret = dstar->hasData();
			if (ret) {
				ret = m_modem->hasDStarSpace();
				if (ret) {
					len = dstar->readData(data);
					if (mode != MODE_DSTAR) {
						LogWarning("D-Star echo data received when in mode %u", mode);
					} else {
						m_modem->writeDStarData(data, len);
						modeTimer.start();
					}
				}
			}
		}

		if (dmr != NULL) {
			ret = m_modem->hasDMRSpace1();
			if (ret) {
				len = dmr->readModemSlot1(data);
				if (len > 0U && mode == MODE_IDLE) {
					m_display->setDMR();
					mode = MODE_DMR;
				}
				if (len > 0U && mode == MODE_DMR) {
					m_modem->writeDMRData1(data, len);
					modeTimer.start();
				}
			}

			ret = m_modem->hasDMRSpace2();
			if (ret) {
				len = dmr->readModemSlot2(data);
				if (len > 0U && mode == MODE_IDLE) {
					m_display->setDMR();
					mode = MODE_DMR;
				}
				if (len > 0U && mode == MODE_DMR) {
					m_modem->writeDMRData2(data, len);
					modeTimer.start();
				}
			}
		}

		if (ysf != NULL) {
			ret = ysf->hasData();
			if (ret) {
				ret = m_modem->hasYSFSpace();
				if (ret) {
					len = ysf->readData(data);
					if (mode != MODE_YSF) {
						LogWarning("System Fusion echo data received when in mode %u", mode);
					} else {
						m_modem->writeYSFData(data, len);
						modeTimer.start();
					}
				}
			}
		}

		unsigned int ms = stopWatch.elapsed();
		m_modem->clock(ms);
		modeTimer.clock(ms);
		if (dstar != NULL)
			dstar->clock(ms);
		if (dmr != NULL)
			dmr->clock(ms);
		if (ysf != NULL)
			ysf->clock(ms);
		stopWatch.start();

		if (ms < 5U) {
#if defined(WIN32)
			::Sleep(5UL);		// 5ms
#else
			::usleep(5000);		// 5ms
#endif
		}
	}

	LogMessage("MMDVMHost is exiting on receipt of SIGHUP1");

	m_display->setIdle();

	m_modem->close();
	delete m_modem;

	m_display->close();
	delete m_display;

	if (m_dmrNetwork != NULL) {
		m_dmrNetwork->close();
		delete m_dmrNetwork;
	}

	delete dstar;
	delete dmr;
	delete ysf;

	return 0;
}