void TSettings::LoadFromFile(String filename) {
    TIniFile *ini = new TIniFile(filename);

    Fullscreen = ini->ReadBool("Global", "FullScreen", false);
    FormsWidth = ini->ReadInteger("Global", "Width", 1024);
    FormsHeight = ini->ReadInteger("Global", "Height", 1024);
    FormsLeft = ini->ReadInteger("Global", "Left", 0);
    FormsTop = ini->ReadInteger("Global", "Top", 0);
    SoundEnabled = ini->ReadBool("Global", "Sound", false);
    SoundVolume = ini->ReadInteger("Global", "SoundVolume", 100);
	SetVolumeSFX(SoundVolume/100.);
    MusicEnabled = ini->ReadBool("Global", "Music", false);
	MusicVolume = ini->ReadInteger("Global", "MusicVolume", 100);
	SetVolumeMusic(MusicVolume/100.);
    HostMode = ini->ReadBool("Global", "HostMode", false);

    MinWidth = 1024;
    MinHeight = 768;

    for (int i = 1; i <= 5; i++) {
        PlayerNames[i - 1] = ini->ReadString("Players", "Player" + IntToStr(i), "PlayerName");
        PlayerType[i - 1] = (TBotType)ini->ReadInteger("Players", "PlayerType" + IntToStr(i), 0);
    }

    LastBase = ini->ReadString("Global", "LastBase", "");
    if (LastBase == "") {
        if (FileExists("base\\main.dat")) {
            LastBase = "main.dat";
        } else {
            MessageBox(Application->Handle,
                "Ошибка загрузки последней базы вопросов\n" "Попытка загрузить base\\main.dat также провалилась - файла не существует.",
                "Критическая ошибка", MB_OK | MB_ICONSTOP);
            Application->Terminate();
        }
    }

    int i = 0;
    BaseFiles.clear();
    BaseNames = new TStringList;
    while (1) {
        String name = ini->ReadString("Bases", "basename" + IntToStr(i), "");
        String file = ini->ReadString("Bases", "base" + IntToStr(i), "");
        if ((name != "") && (file != "")) {
            BaseFiles[name] = file;
            BaseNames->Add(name);
        } else {
            break;
        }
        i++ ;
    }

    ini->Free();
}