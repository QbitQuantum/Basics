void AppFrame::OnMenu(wxCommandEvent& event) {
    if (event.GetId() >= wxID_RT_AUDIO_DEVICE && event.GetId() < wxID_RT_AUDIO_DEVICE + devices.size()) {
        if (activeDemodulator) {
            activeDemodulator->setOutputDevice(event.GetId() - wxID_RT_AUDIO_DEVICE);
            activeDemodulator = NULL;
        }
    } else if (event.GetId() == wxID_SET_FREQ_OFFSET) {
        long ofs = wxGetNumberFromUser("Shift the displayed frequency by this amount.\ni.e. -125000000 for -125 MHz", "Frequency (Hz)",
                "Frequency Offset", wxGetApp().getOffset(), -2000000000, 2000000000, this);
        if (ofs != -1) {
            wxGetApp().setOffset(ofs);
            wxGetApp().saveConfig();
        }
    } else if (event.GetId() == wxID_SET_DS_OFF) {
        wxGetApp().setDirectSampling(0);
        wxGetApp().saveConfig();
    } else if (event.GetId() == wxID_SET_DS_I) {
        wxGetApp().setDirectSampling(1);
        wxGetApp().saveConfig();
    } else if (event.GetId() == wxID_SET_DS_Q) {
        wxGetApp().setDirectSampling(2);
        wxGetApp().saveConfig();
    } else if (event.GetId() == wxID_SET_SWAP_IQ) {
        bool swap_state = !wxGetApp().getSwapIQ();
        wxGetApp().setSwapIQ(swap_state);
        wxGetApp().saveConfig();
        iqSwapMenuItem->Check(swap_state);
    } else if (event.GetId() == wxID_SET_PPM) {
        long ofs = wxGetNumberFromUser("Frequency correction for device in PPM.\ni.e. -51 for -51 PPM\n\nNote: you can adjust PPM interactively\nby holding ALT over the frequency tuning bar.\n", "Parts per million (PPM)",
                "Frequency Correction", wxGetApp().getPPM(), -1000, 1000, this);
            wxGetApp().setPPM(ofs);
            wxGetApp().saveConfig();
    } else if (event.GetId() == wxID_SAVE) {
        if (!currentSessionFile.empty()) {
            saveSession(currentSessionFile);
        } else {
            wxFileDialog saveFileDialog(this, _("Save XML Session file"), "", "", "XML files (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
            if (saveFileDialog.ShowModal() == wxID_CANCEL) {
                return;
            }
            saveSession(saveFileDialog.GetPath().ToStdString());
        }
    } else if (event.GetId() == wxID_OPEN) {
        wxFileDialog openFileDialog(this, _("Open XML Session file"), "", "", "XML files (*.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (openFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }
        loadSession(openFileDialog.GetPath().ToStdString());
    } else if (event.GetId() == wxID_SAVEAS) {
        wxFileDialog saveFileDialog(this, _("Save XML Session file"), "", "", "XML files (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }
        saveSession(saveFileDialog.GetPath().ToStdString());
    } else if (event.GetId() == wxID_RESET) {
        wxGetApp().getDemodMgr().terminateAll();
        wxGetApp().setFrequency(100000000);
        wxGetApp().setOffset(0);
        SetTitle(CUBICSDR_TITLE);
        currentSessionFile = "";
    } else if (event.GetId() == wxID_EXIT) {
        Close(false);
    } else if (event.GetId() == wxID_THEME_DEFAULT) {
        ThemeMgr::mgr.setTheme(COLOR_THEME_DEFAULT);
    } else if (event.GetId() == wxID_THEME_SHARP) {
        ThemeMgr::mgr.setTheme(COLOR_THEME_SHARP);
    } else if (event.GetId() == wxID_THEME_BW) {
        ThemeMgr::mgr.setTheme(COLOR_THEME_BW);
    } else if (event.GetId() == wxID_THEME_RAD) {
        ThemeMgr::mgr.setTheme(COLOR_THEME_RAD);
    } else if (event.GetId() == wxID_THEME_TOUCH) {
        ThemeMgr::mgr.setTheme(COLOR_THEME_TOUCH);
    } else if (event.GetId() == wxID_THEME_HD) {
        ThemeMgr::mgr.setTheme(COLOR_THEME_HD);
    } else if (event.GetId() == wxID_THEME_RADAR) {
        ThemeMgr::mgr.setTheme(COLOR_THEME_RADAR);
    }

    switch (event.GetId()) {
        case wxID_BANDWIDTH_250K:
            wxGetApp().setSampleRate(250000);
            break;
        case wxID_BANDWIDTH_1000M:
            wxGetApp().setSampleRate(1000000);
            break;
        case wxID_BANDWIDTH_1024M:
            wxGetApp().setSampleRate(1024000);
            break;
        case wxID_BANDWIDTH_1500M:
            wxGetApp().setSampleRate(1500000);
            break;
        case wxID_BANDWIDTH_1800M:
            wxGetApp().setSampleRate(1800000);
            break;
        case wxID_BANDWIDTH_1920M:
            wxGetApp().setSampleRate(1920000);
            break;
        case wxID_BANDWIDTH_2000M:
            wxGetApp().setSampleRate(2000000);
            break;
        case wxID_BANDWIDTH_2048M:
            wxGetApp().setSampleRate(2048000);
            break;
        case wxID_BANDWIDTH_2160M:
            wxGetApp().setSampleRate(2160000);
            break;
        case wxID_BANDWIDTH_2400M:
            wxGetApp().setSampleRate(2400000);
            break;
        case wxID_BANDWIDTH_2560M:
            wxGetApp().setSampleRate(2560000);
            break;
        case wxID_BANDWIDTH_2880M:
            wxGetApp().setSampleRate(2880000);
            break;
//        case wxID_BANDWIDTH_3000M:
//            wxGetApp().setSampleRate(3000000);
//            break;
        case wxID_BANDWIDTH_3200M:
            wxGetApp().setSampleRate(3200000);
            break;
    }

    std::vector<SDRDeviceInfo *> *devs = wxGetApp().getDevices();
    if (event.GetId() >= wxID_DEVICE_ID && event.GetId() <= wxID_DEVICE_ID + devs->size()) {
        int devId = event.GetId() - wxID_DEVICE_ID;
        wxGetApp().setDevice(devId);

        SDRDeviceInfo *dev = (*wxGetApp().getDevices())[devId];
        DeviceConfig *devConfig = wxGetApp().getConfig()->getDevice(dev->getDeviceId());
        
        int dsMode = devConfig->getDirectSampling();
        
        if (dsMode >= 0 && dsMode <= 2) {
            directSamplingMenuItems[devConfig->getDirectSampling()]->Check();
        }
        
        iqSwapMenuItem->Check(devConfig->getIQSwap());
    }

    if (event.GetId() >= wxID_AUDIO_BANDWIDTH_BASE) {
        int evId = event.GetId();
        std::vector<RtAudio::DeviceInfo>::iterator devices_i;
        std::map<int, RtAudio::DeviceInfo>::iterator mdevices_i;

        int i = 0;
        for (mdevices_i = outputDevices.begin(); mdevices_i != outputDevices.end(); mdevices_i++) {
            int menu_id = wxID_AUDIO_BANDWIDTH_BASE + wxID_AUDIO_DEVICE_MULTIPLIER * mdevices_i->first;

            int j = 0;
            for (std::vector<unsigned int>::iterator srate = mdevices_i->second.sampleRates.begin(); srate != mdevices_i->second.sampleRates.end();
                    srate++) {

                if (evId == menu_id + j) {
                    //audioSampleRateMenuItems[menu_id+j];
                    //std::cout << "Would set audio sample rate on device " << mdevices_i->second.name << " (" << mdevices_i->first << ") to " << (*srate) << "Hz" << std::endl;
                    AudioThread::setDeviceSampleRate(mdevices_i->first, *srate);
                }

                j++;
            }
            i++;
        }
    }

}