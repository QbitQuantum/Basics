INT_PTR
CALLBACK
ProcessorDlgProc (HWND hDlg, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch (uMessage) {
        case WM_INITDIALOG:
        {
            WCHAR szFeatures[MAX_PATH] = L"";
            WCHAR szModel[3];
            WCHAR szStepping[3];
            WCHAR szCurrentMhz[10];
            BOOL bFirst = TRUE;
            SYSTEM_INFO SystemInfo;
            PROCESSOR_POWER_INFORMATION PowerInfo;

            if (IsProcessorFeaturePresent(PF_MMX_INSTRUCTIONS_AVAILABLE))
                AddFeature(szFeatures, sizeof(szFeatures), L"MMX", &bFirst);
            if (IsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE))
                AddFeature(szFeatures, sizeof(szFeatures), L"SSE", &bFirst);
            if (IsProcessorFeaturePresent(PF_XMMI64_INSTRUCTIONS_AVAILABLE))
                AddFeature(szFeatures, sizeof(szFeatures), L"SSE2", &bFirst);
            /*if (IsProcessorFeaturePresent(PF_SSE3_INSTRUCTIONS_AVAILABLE))
                AddFeature(szFeatures, sizeof(szFeatures), L"SSE3", &bFirst); */
            if (IsProcessorFeaturePresent(PF_3DNOW_INSTRUCTIONS_AVAILABLE))
                AddFeature(szFeatures, sizeof(szFeatures), L"3DNOW", &bFirst);

            SetDlgItemTextW(hDlg, IDC_FEATURES, szFeatures);

            GetSystemInfo(&SystemInfo);

            StringCbPrintfW(szModel, sizeof(szModel), L"%x", HIBYTE(SystemInfo.wProcessorRevision));
            StringCbPrintfW(szStepping, sizeof(szStepping), L"%d", LOBYTE(SystemInfo.wProcessorRevision));

            SetDlgItemTextW(hDlg, IDC_MODEL, szModel);
            SetDlgItemTextW(hDlg, IDC_STEPPING, szStepping);

            CallNtPowerInformation(11, NULL, 0, &PowerInfo, sizeof(PowerInfo));
            StringCbPrintfW(szCurrentMhz, sizeof(szCurrentMhz), L"%ld %s", PowerInfo.CurrentMhz, L"MHz");
            SetDlgItemTextW(hDlg, IDC_CORESPEED, szCurrentMhz);

            return TRUE;
        }
    }
    return FALSE;
}