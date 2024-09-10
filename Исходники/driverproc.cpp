extern "C" __declspec(dllexport) LRESULT WINAPI DriverProc(DWORD dwDriverId, HDRVR hDriver, UINT uMsg, LPARAM lParam1, LPARAM lParam2)
{
    Iffacm2 *ffacm = (Iffacm2*)dwDriverId;
    switch (uMsg) {
        case DRV_LOAD:
            return DRV_OK;
        case DRV_FREE:
            if (hdll) {
                FreeModule(hdll);
                hdll = NULL;
            }
            return DRV_OK;
        case DRV_OPEN: {
            ACMDRVOPENDESCW *icopen = (ACMDRVOPENDESCW*)lParam2;
            if (icopen != NULL && icopen->fccType != ACMDRIVERDETAILS_FCCTYPE_AUDIOCODEC) {
                return DRVCNF_CANCEL;
            }
            if (!hdll) {
                TregOpRegRead r(HKEY_CLASSES_ROOT, "CLSID\\{F6E8FC04-8B05-48B1-9399-848229502A06}\\InprocServer32");
                char pth[MAX_PATH];
                r._REG_OP_S(0, "", pth, MAX_PATH, "");
                hdll = LoadLibrary(pth);
            }
            typedef Iffacm2creator* (__stdcall * Tcreate)(void);
            Tcreate create = (Tcreate)GetProcAddress(hdll, "ffacm2creator");
            if (!create) {
                return DRVCNF_CANCEL;
            }
            Iffacm2creator *creator = create();
            if (!creator) {
                return DRVCNF_CANCEL;
            }
            //if (FAILED(CoCreateInstance(CLSID_FFACM2CREATOR,NULL,CLSCTX_INPROC_SERVER,IID_Iffacm2creator,(void**)&creator))) return DRVCNF_CANCEL;
            int size = creator->getSize();
            ffacm = (Iffacm2*)LocalAlloc(LPTR, size);
            if (!ffacm) {
                creator->Release();
                return DRVCNF_CANCEL;
            }
            creator->create(ffacm);
            creator->Release();
            if (icopen != NULL) {
                icopen->dwError = DRV_OK;
            }
            DPRINTF("ACM DRV_OPEN %i %p", hDriver, ffacm);
            return (LRESULT)ffacm;
        }
        case DRV_CLOSE:
            DPRINTF("ACM DRV_CLOSE %i %p", hDriver, ffacm);
            if (ffacm) {
                LocalFree(ffacm);
            }
            return DRV_OK;
        case DRV_CONFIGURE:
            return DRVCNF_OK;
        case DRV_QUERYCONFIGURE:
            return FALSE;
        case DRV_INSTALL:
            return DRVCNF_RESTART;
        case DRV_REMOVE:
            return DRVCNF_RESTART;
            // ACM
        case ACMDM_DRIVER_DETAILS:
            DPRINTF("ACM ACMDM_DRIVER_DETAILS %i %p", hDriver, ffacm);
            return ffacm->driverDetails((LPACMDRIVERDETAILSW)lParam1);
        case ACMDM_DRIVER_ABOUT:
            DPRINTF("ACM ACMDM_DRIVER_ABOUT %i %p", hDriver, ffacm);
            return ffacm->driverAbout((HWND)lParam1);
        case ACMDM_FORMAT_SUGGEST:
            DPRINTF("ACM ACMDM_FORMAT_SUGGEST %i %p", hDriver, ffacm);
            return ffacm->formatSuggest((LPACMDRVFORMATSUGGEST)lParam1);
        case ACMDM_FORMATTAG_DETAILS:
            DPRINTF("ACM ACMDM_FORMATTAG_DETAILS %i %p", hDriver, ffacm);
            return ffacm->formatTagDetails((LPACMFORMATTAGDETAILSW)lParam1, (DWORD)lParam2);
        case ACMDM_FORMAT_DETAILS:
            DPRINTF("ACM ACMDM_FORMAT_DETAILS %i %p", hDriver, ffacm);
            //lr = acmdFormatDetails(pdi, (LPACMFORMATDETAILS)lParam1, (DWORD)lParam2);
            return 0;
        case ACMDM_STREAM_OPEN:
            DPRINTF("ACM ACMDM_STREAM_OPEN %i %p", hDriver, ffacm);
            return ffacm->streamOpen((LPACMDRVSTREAMINSTANCE)lParam1);
        case ACMDM_STREAM_CLOSE:
            DPRINTF("ACM ACMDM_STREAM_CLOSE %i %p", hDriver, ffacm);
            return ffacm->streamClose((LPACMDRVSTREAMINSTANCE)lParam1);
        case ACMDM_STREAM_SIZE:
            DPRINTF("ACM ACMDM_STREAM_SIZE %i %p", hDriver, ffacm);
            return ffacm->streamSize((LPACMDRVSTREAMINSTANCE)lParam1, (LPACMDRVSTREAMSIZE)lParam2);
        case ACMDM_STREAM_CONVERT:
            DPRINTF("ACM ACMDM_STREAM_SIZE %i %p", hDriver, ffacm);
            return ffacm->convert((LPACMDRVSTREAMINSTANCE) lParam1, (LPACMDRVSTREAMHEADER)lParam2);
        default:
            if (uMsg < DRV_USER) {
                return DefDriverProc(dwDriverId, hDriver, uMsg, lParam1, lParam2);
            }
    }
    return MMSYSERR_NOTSUPPORTED;
}