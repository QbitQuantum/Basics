/** Prints packet timestaps regardless of format*/
int _tmain(int argc, _TCHAR* argv[])
{
    char errbuf[PCAP_ERRBUF_SIZE];
    wchar_t cmd[1024];
    wchar_t tshark_path[MAX_PATH];
    wchar_t file_path[MAX_PATH];

    if ( argc != 3 ) {
        wprintf(L"Prints packet timestaps regardless of format.\n");
        wprintf(L"Usage:\n\t%ls <tshark path> <trace file>\n", argv[0]);
        return 1;
    }

    // conversion to short path name in case there are spaces
    if ( ! GetShortPathNameW(argv[1], tshark_path, MAX_PATH) || 
         ! GetShortPathNameW(argv[2], file_path, MAX_PATH) )
    {
        printf("Failed to convert paths to short form.");
        return 1;
    }

    // create tshark command, which will make the trace conversion and print in libpcap format to stdout
    if ( swprintf_s(cmd, 1024, L"%ls -r %ls -w - -F libpcap", tshark_path, file_path) < 0 ) {
        wprintf(L"Failed to create command\n");
        return 1;
    }

    // start tshark
    FILE *tshark_out = _wpopen(cmd, L"rb");
    if ( tshark_out == NULL ) {
        strerror_s(errbuf, PCAP_ERRBUF_SIZE, errno);
        printf("Failed run tshark: %s\n", errbuf);
        wprintf(L"Command: %ls", cmd);
        return 1;
    }

    // open stdout from tshark
    pcap_t *pcap = pcap_fopen_offline(tshark_out, errbuf);
    if ( pcap == NULL ) {
        printf("Error opening stream from tshark: %s\n", errbuf);
        return 1;
    }

    // print information about every packet int trace
    struct pcap_pkthdr hdr;
    while ( pcap_next(pcap, &hdr) ) {
        printf("packet: ts: %u.%06u,  len: %4u,  caplen: %4u\n", hdr.ts.tv_sec, hdr.ts.tv_usec, hdr.len, hdr.caplen);
    }

    // clean up
    pcap_close(pcap);
    _pclose(tshark_out);
    return 0;
}