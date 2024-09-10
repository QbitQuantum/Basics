int COPROCS::write_coproc_info_file(vector<string> &warnings) {
    MIOFILE mf;
    unsigned int i, temp;
    FILE* f;
    
    f = boinc_fopen(COPROC_INFO_FILENAME, "wb");
    if (!f) return ERR_FOPEN;
    mf.init_file(f);
    
    mf.printf("    <coprocs>\n");

    for (i=0; i<ati_gpus.size(); ++i) {
       ati_gpus[i].write_xml(mf, false);
    }
    for (i=0; i<nvidia_gpus.size(); ++i) {
        temp = nvidia_gpus[i].count;
        nvidia_gpus[i].count = 1;
        nvidia_gpus[i].pci_infos[0] = nvidia_gpus[i].pci_info;
        nvidia_gpus[i].write_xml(mf, false);
        nvidia_gpus[i].count = temp;
    }
    for (i=0; i<intel_gpus.size(); ++i) {
        intel_gpus[i].write_xml(mf, false);
    }
    for (i=0; i<ati_opencls.size(); ++i) {
        ati_opencls[i].write_xml(mf, "ati_opencl", true);
    }
    for (i=0; i<nvidia_opencls.size(); ++i) {
        nvidia_opencls[i].write_xml(mf, "nvidia_opencl", true);
    }
    for (i=0; i<intel_gpu_opencls.size(); ++i) {
        intel_gpu_opencls[i].write_xml(mf, "intel_gpu_opencl", true);
    }
    for (i=0; i<cpu_opencls.size(); i++) {
        cpu_opencls[i].write_xml(mf);
    }
    for (i=0; i<warnings.size(); ++i) {
        mf.printf("<warning>%s</warning>\n", warnings[i].c_str());
    }

    mf.printf("    </coprocs>\n");
    fclose(f);
    return 0;
}