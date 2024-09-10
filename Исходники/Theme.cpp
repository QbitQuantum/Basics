    void GetAvailableThemes(List<AvailableTheme> * outThemes)
    {
        Guard::ArgumentNotNull(outThemes);

        outThemes->Clear();

        NumPredefinedThemes = 0;
        for (const UITheme * * predefinedTheme = PredefinedThemes; *predefinedTheme != nullptr; predefinedTheme++)
        {
            AvailableTheme theme;
            String::Set(theme.Path, sizeof(theme.Path), String::Empty);
            String::Set(theme.Name, sizeof(theme.Name), (*predefinedTheme)->Name);
            outThemes->Add(theme);

            NumPredefinedThemes++;
        }

        utf8 themesPattern[MAX_PATH];
        GetThemePath(themesPattern, sizeof(themesPattern));
        Path::Append(themesPattern, sizeof(themesPattern), "*.json");

        int handle = platform_enumerate_files_begin(themesPattern);
        if (handle != INVALID_HANDLE)
        {
            file_info fileInfo;
            while (platform_enumerate_files_next(handle, &fileInfo))
            {
                AvailableTheme theme;
                Path::GetFileNameWithoutExtension(theme.Name, sizeof(theme.Name), fileInfo.path);
                GetThemeFileName(theme.Path, sizeof(theme.Path), theme.Name);
                
                outThemes->Add(theme);

                if (Path::Equals(CurrentThemePath, fileInfo.path))
                {
                    ActiveAvailableThemeIndex = outThemes->GetCount() - 1;
                }
            }
            platform_enumerate_files_end(handle);
        }
    }