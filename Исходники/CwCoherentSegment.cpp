void CwCoherentSegment::marshall()
{
    path.marshall();
    HTONF(pfa);
    HTONF(snr);
}