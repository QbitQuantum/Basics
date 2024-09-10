WDbgArkColorHack::WDbgArkColorHack() : m_inited(false),
                                       m_g_ui_colors(nullptr),
                                       m_g_out_mask_ui_colors(nullptr),
                                       m_internal_colors(),
                                       m_cur_theme(),
                                       m_themes(),
                                       out(),
                                       warn(),
                                       err() {
    try {
        if ( !IsWinDbgWindow() )
            throw ExtStatusException(S_OK, "Can't find WinDBG window");

        m_tp->AddColumn("DML name", 15);
        m_tp->AddColumn("Description", 70);
        m_tp->AddColumn("Original", 10);
        m_tp->AddColumn("New color", 10);

        InitThemes();

        uintptr_t windbg_module_start = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

        if ( !windbg_module_start )
            throw ExtStatusException(S_OK, "GetModuleHandle failed");

        PIMAGE_NT_HEADERS nth = ImageNtHeader(reinterpret_cast<PVOID>(windbg_module_start));

        if ( !nth )
            throw ExtStatusException(S_OK, "Can't get NT header");

        uintptr_t windbg_module_end = reinterpret_cast<uintptr_t>(reinterpret_cast<char*>(windbg_module_start) +\
            static_cast<ptrdiff_t>(nth->OptionalHeader.SizeOfImage));

        PIMAGE_SECTION_HEADER sech = reinterpret_cast<PIMAGE_SECTION_HEADER>(reinterpret_cast<char*>(nth) +\
            sizeof(*nth));

        PIMAGE_SECTION_HEADER sech_text = nullptr;
        PIMAGE_SECTION_HEADER sech_data = nullptr;

        for ( __int16 i = 0; i < nth->FileHeader.NumberOfSections; i++ ) {
            std::string section_name = reinterpret_cast<char*>(&sech->Name[0]);

            if ( sech_text && sech_data )
                break;
            else if ( section_name == ".text" )
                sech_text = sech;
            else if ( section_name == ".data" )
                sech_data = sech;

            sech++;
        }

        if ( !sech_text || !sech_data )
            throw ExtStatusException(S_OK, "Can't get sections header");

        uintptr_t start_data = reinterpret_cast<uintptr_t>(reinterpret_cast<char*>(windbg_module_start) +\
            static_cast<ptrdiff_t>(sech_data->VirtualAddress));

        uintptr_t end_data = reinterpret_cast<uintptr_t>(reinterpret_cast<char*>(start_data) +\
            static_cast<ptrdiff_t>(sech_data->Misc.VirtualSize));

        uintptr_t start_text = reinterpret_cast<uintptr_t>(reinterpret_cast<char*>(windbg_module_start) +\
            static_cast<ptrdiff_t>(sech_text->VirtualAddress));

        uintptr_t end_text = reinterpret_cast<uintptr_t>(reinterpret_cast<char*>(start_text) +\
            static_cast<ptrdiff_t>(sech_text->Misc.VirtualSize));

        if ( start_data >= windbg_module_end || end_data > windbg_module_end ||
             start_text >= windbg_module_end || end_text > windbg_module_end ) {
                 throw ExtStatusException(S_OK, "Something is wrong");
        }

        uintptr_t* mem_point = reinterpret_cast<uintptr_t*>(start_data);
        uintptr_t* mem_point_end = reinterpret_cast<uintptr_t*>(end_data);

        while ( mem_point < mem_point_end ) {
            try {
                if ( *mem_point >= start_text && *mem_point <= end_text ) {
                    std::wstring check_sig = reinterpret_cast<wchar_t*>(*mem_point);
                    if ( check_sig == L"Background" )
                        m_g_ui_colors = reinterpret_cast<UiColor*>(mem_point);
                    else if ( check_sig == L"Normal level command window text" )
                        m_g_out_mask_ui_colors = reinterpret_cast<UiColor*>(mem_point);
                    else if ( m_g_ui_colors && m_g_out_mask_ui_colors )
                        break;
                }
            }
            catch( ... ) { }    // continue

            mem_point++;
        }

        if ( !m_g_ui_colors || !m_g_out_mask_ui_colors )
            throw ExtStatusException(S_OK, "WinDbg internal structures are not found");

        UiColor* loc_ui_color = m_g_ui_colors;

        while ( loc_ui_color->description ) {
            m_internal_colors.push_back(ConvertUiColorToInternal(loc_ui_color, UiColorType::UiColorsType));
            loc_ui_color++;
        }

        loc_ui_color = m_g_out_mask_ui_colors;

        while ( loc_ui_color->description ) {
            m_internal_colors.push_back(ConvertUiColorToInternal(loc_ui_color, UiColorType::UiColorsOutMaskType));
            loc_ui_color++;
        }

        m_inited = true;
    }
    catch ( const ExtStatusException &Ex ) {
        err << wa::showminus << __FUNCTION__ << ": " << Ex.GetMessage() << endlerr;
    }
    catch( ... ) {
        err << wa::showminus << __FUNCTION__ << ": exception error" << endlerr;
    }
}