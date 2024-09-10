// Save a palette to an open MMIO handle
BOOL CDIBPal::Save(HMMIO hmmio)
{
    // Create a RIFF chunk for a PAL file
    MMCKINFO ckFile;
    ckFile.cksize = 0; // corrected later
    ckFile.fccType = mmioFOURCC('P','A','L',' ');
    if (mmioCreateChunk(hmmio,
                        &ckFile,
                        MMIO_CREATERIFF) != 0) {
        TRACE("Failed to create RIFF-PAL chunk");
        return FALSE;
    }
    // create the LOGPALETTE data which will become
    // the data chunk
    int iColors = GetNumColors();
    ASSERT(iColors > 0);
    int iSize = sizeof(LOGPALETTE)
                + (iColors-1) * sizeof(PALETTEENTRY);
    LOGPALETTE* plp = (LOGPALETTE*) malloc(iSize);
    ASSERT(plp);
    plp->palVersion = 0x300;
    plp->palNumEntries = iColors;
    GetPaletteEntries(0, iColors, plp->palPalEntry);
    // create the data chunk
    MMCKINFO ckData;
    ckData.cksize = iSize; 
    ckData.ckid = mmioFOURCC('d','a','t','a');
    if (mmioCreateChunk(hmmio,
                        &ckData,
                        0) != 0) {
        TRACE("Failed to create data chunk");
        return FALSE;
    }
    // write the data chunk
    if (mmioWrite(hmmio,
                 (char*)plp,
                 iSize) != iSize) {
        TRACE("Failed to write data chunk");
        free(plp);
        return FALSE;
    }
    free(plp);
    // Ascend from the data chunk which will correct the length
    mmioAscend(hmmio, &ckData, 0);
    // Ascend from the RIFF/PAL chunk
    mmioAscend(hmmio, &ckFile, 0);

    return TRUE;
}