void FaceRender::PrintLandmarkData(PXCFaceAnalysis::Landmark *landmark, pxcU32 fid) {

    FaceRender::FaceData& itr=Insert(fid);
    wprintf_s(L"Landmark data fid=%d:\n", fid);
    for (int i=0; i<sizeof(itr.landmark)/sizeof(itr.landmark[0]); i++) {
        PXCFaceAnalysis::Landmark::LandmarkData data;
        pxcStatus sts=landmark->QueryLandmarkData(fid,labels[i],0,&data);
        if (sts<PXC_STATUS_NO_ERROR) continue;
        wprintf_s(L"%S : x=%4.1f, y=%4.1f\n", landmarkLabels[i], data.position.x, data.position.y);
    }
    wprintf_s(L"\n");
}