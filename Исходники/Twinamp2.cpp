//=========================== Twinamp2dspDll =================================
Twinamp2dspDll::Twinamp2dspDll(const ffstring &flnm): refcount(1)
{
    dll = NULL;
    winampDSPGetHeaderType = NULL;
    hdr = NULL;
    char_t filename[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
    _splitpath_s(flnm.c_str(), NULL, 0, NULL, 0, name, MAX_PATH, ext, MAX_PATH);
    _makepath_s(filename, MAX_PATH, NULL, NULL, name, ext);
    // DSP stacker, Adapt-X and Vst host are not compatible with ffdshow currently. Maybe ffdshow's bug, but I can't help...
    if (_strnicmp(_l("dsp_stacker.dll"), filename, 16) == 0
            || _strnicmp(_l("dsp_adaptx.dll"), filename, 15) == 0
            || _strnicmp(_l("dsp_sps.dll"), filename, 11) == 0
       ) {
        return;
    }
    dll = new Tdll(flnm.c_str(), NULL);
    if (dll->ok) {
        dll->loadFunction(winampDSPGetHeaderType, "winampDSPGetHeader2");
        if (!dll->ok) {
            // retry with index 1.
            dll->ok = true;
            dll->loadFunctionByIndex(winampDSPGetHeaderType, 1);
        }
    }
    if (dll->ok) {
        hdr = winampDSPGetHeaderType();
        if (hdr->version != DSP_HDRVER) {
            hdr = NULL;
            return;
        }
        descr = hdr->description;
        dllFileName = filename;
    }
    if (hdr)
        for (int i = 0;; i++) {
            winampDSPModule *flt = hdr->getModule(i);
            if (!flt) {
                break;
            }
            flt->hDllInstance = dll->hdll;
            filters.push_back(new Twinamp2dsp(this, flt));
        }
}