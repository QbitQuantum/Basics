    bool Init(const std::string& path){
        path_ = path; 

        // すでにアイコンが読み込まれていたら、破棄する。
        Destroy();

        // SHFILEINFO構造体の初期化
        SHFILEINFO info;
        ZeroMemory(&info, sizeof(info));

        // スモールアイコンを取得
        SHGetFileInfoA(path.c_str(), 0, &info, sizeof(info),
                       SHGFI_ICON | SHGFI_SMALLICON);
        hIcon_ = info.hIcon;

        // NULLなら、取得に失敗している。
        return hIcon_ != NULL;
    }