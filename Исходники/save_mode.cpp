bool SaveMode::_PreviewGame(uint32 id)
{
    std::ostringstream f;
    f << GetUserDataPath() + "saved_game_" << id << ".lua";
    std::string filename = f.str();

    // Check for the file existence, prevents a useless warning
    if(!vt_utils::DoesFileExist(filename)) {
        _ClearSaveData(false);
        return false;
    }

    ReadScriptDescriptor file;

    // Clear out the save data namespace to avoid loading false information
    // when dealing with a save game that has an invalid namespace
    ScriptManager->DropGlobalTable("save_game1");

    if(!file.OpenFile(filename)) {
        _ClearSaveData(true);
        return false;
    }

    if(!file.DoesTableExist("save_game1")) {
        file.CloseFile();
        _ClearSaveData(true);
        return false;
    }

    // open the namespace that the save game is encapsulated in.
    file.OpenTable("save_game1");

    // The map file, tested after the save game is closed.
    // DEPRECATED: Old way, will be removed in one release.
    std::string map_script_filename;
    std::string map_data_filename;
    if (file.DoesStringExist("map_filename")) {
        map_script_filename = file.ReadString("map_filename");
        map_data_filename = file.ReadString("map_filename");
    }
    else {
        map_script_filename = file.ReadString("map_script_filename");
        map_data_filename = file.ReadString("map_data_filename");
    }

    // DEPRECATED: Remove in one release
    // Hack to permit the split of last map data and scripts.
    if (!map_script_filename.empty() && map_data_filename == map_script_filename) {
        std::string map_common_name = map_data_filename.substr(0, map_data_filename.length() - 4);
        map_data_filename = map_common_name + "_map.lua";
        map_script_filename = map_common_name + "_script.lua";
    }

    // Used to store temp data to populate text boxes
    int32 hours = file.ReadInt("play_hours");
    int32 minutes = file.ReadInt("play_minutes");
    int32 seconds = file.ReadInt("play_seconds");
    int32 drunes = file.ReadInt("drunes");

    if(!file.DoesTableExist("characters")) {
        file.CloseTable(); // save_game1
        file.CloseFile();
        _ClearSaveData(true);
        return false;
    }

    file.OpenTable("characters");
    std::vector<uint32> char_ids;
    file.ReadUIntVector("order", char_ids);
    GlobalCharacter *character[4];

    // Loads only up to the first four slots (Visible battle characters)
    for(uint32 i = 0; i < 4 && i < char_ids.size(); ++i) {
        // Create a new GlobalCharacter object using the provided id
        // This loads all of the character's "static" data, such as their name, etc.
        character[i] = new GlobalCharacter(char_ids[i], false);

        if(!file.DoesTableExist(char_ids[i]))
            continue;

        file.OpenTable(char_ids[i]);

        // Read in all of the character's stats data
        character[i]->SetExperienceLevel(file.ReadUInt("experience_level"));
        character[i]->SetExperiencePoints(file.ReadUInt("experience_points"));

        character[i]->SetMaxHitPoints(file.ReadUInt("max_hit_points"));
        character[i]->SetHitPoints(file.ReadUInt("hit_points"));
        character[i]->SetMaxSkillPoints(file.ReadUInt("max_skill_points"));
        character[i]->SetSkillPoints(file.ReadUInt("skill_points"));

        file.CloseTable(); // character id
    }
    file.CloseTable(); // characters

    // Report any errors detected from the previous read operations
    if(file.IsErrorDetected()) {
        PRINT_WARNING << "One or more errors occurred while reading the save game file - they are listed below:"
            << std::endl << file.GetErrorMessages() << std::endl;
            file.ClearErrors();
    }

    file.CloseTable(); // save_game1
    file.CloseFile();

    for(uint32 i = 0; i < 4 && i < char_ids.size(); ++i) {
        _character_window[i].SetCharacter(character[i]);
    }

    std::ostringstream time_text;
    time_text << (hours < 10 ? "0" : "") << static_cast<uint32>(hours) << ":";
    time_text << (minutes < 10 ? "0" : "") << static_cast<uint32>(minutes) << ":";
    time_text << (seconds < 10 ? "0" : "") << static_cast<uint32>(seconds);
    _time_textbox.SetDisplayText(MakeUnicodeString(time_text.str()));

    std::ostringstream drunes_amount;
    drunes_amount << drunes;
    _drunes_textbox.SetDisplayText(MakeUnicodeString(drunes_amount.str()));

    // Test the map file

    // Tests the map file and gets the untranslated map hud name from it.
    ReadScriptDescriptor map_file;
    if(!map_file.OpenFile(map_script_filename)) {
        _ClearSaveData(true);
        return false;
    }

    if (map_file.OpenTablespace().empty()) {
        _ClearSaveData(true);
        map_file.CloseFile();
        return false;
    }

    // Read the in-game location of the save
    std::string map_hud_name = map_file.ReadString("map_name");
    _map_name_textbox.SetDisplayText(UTranslate(map_hud_name));

    // Loads the potential location image
    std::string map_image_filename = map_file.ReadString("map_image_filename");
    if (map_image_filename.empty()) {
        _location_image.Clear();
    }
    else {
        if (_location_image.Load(map_image_filename))
            _location_image.SetWidthKeepRatio(340.0f);
    }

    map_file.CloseTable(); // Tablespace
    map_file.CloseFile();

    return true;
} // bool SaveMode::_PreviewGame(string& filename)