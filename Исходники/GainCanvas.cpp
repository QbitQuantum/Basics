void GainCanvas::updateGainUI() {
    SDRDeviceInfo *devInfo = wxGetApp().getDevice();
    DeviceConfig *devConfig = wxGetApp().getConfig()->getDevice(devInfo->getDeviceId());
    
    gains = devInfo->getGains(SOAPY_SDR_RX, 0);
    SDRRangeMap::iterator gi;
    
    numGains = gains.size();
    float i = 0;
    
    if (!numGains) {
        return;
    }
    
    spacing = 2.0/numGains;
    barWidth = (1.0/numGains)*0.7;
    startPos = spacing/2.0;
    barHeight = 1.0f;
    
    while (gainPanels.size()) {
        MeterPanel *mDel = gainPanels.back();
        gainPanels.pop_back();
        bgPanel.removeChild(mDel);
        delete mDel;
    }
    
    for (auto gi : gains) {
        MeterPanel *mPanel = new MeterPanel(gi.first, gi.second.minimum(), gi.second.maximum(), devConfig->getGain(gi.first,wxGetApp().getGain(gi.first)));

        float midPos = -1.0+startPos+spacing*i;
        mPanel->setPosition(midPos, 0);
        mPanel->setSize(barWidth, barHeight);
        bgPanel.addChild(mPanel);
        
        gainPanels.push_back(mPanel);
        i++;
    }
    
    setThemeColors();
}