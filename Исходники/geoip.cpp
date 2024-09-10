PGeoIpBs TGeoIpBs::LoadBin(const TStr& FNm){
    // load and return if exists
    if (TFile::Exists(FNm)) {
        TFIn SIn(FNm); return Load(SIn);
    } 
    // otherwise assume we have CSV and we need to parse it first
    printf("Cannot fine %s, loading from raw files\n", FNm.CStr());
    TStr FPath = FNm.GetFPath() + "/GeoIP/";
    PGeoIpBs GeoIpBs = LoadCsv(FPath);
    GeoIpBs->SaveBin(FNm);
    return GeoIpBs;
}