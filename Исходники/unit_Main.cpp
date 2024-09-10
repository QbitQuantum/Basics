//===========================================================================
void __fastcall Tform_Main::Setup_lb_WaveFormDevice()
{
    combobox_SoundCard->Items->Clear();
    combobox_SoundFreq->Items->Clear();
    // ----- Количество ВАйфФОрм Устройств ------
    for ( unsigned int i = 0; i < waveInGetNumDevs(); i++)
    {
         WAVEINCAPS wic;
         ZeroMemory(&wic, sizeof(wic));
         waveInGetDevCaps(i, &wic, sizeof(wic));
         combobox_SoundCard->Items->Add(wic.szPname);
    }
}