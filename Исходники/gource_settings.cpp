void GourceSettings::importGourceSettings(ConfFile& conffile, ConfSection* gource_settings) {

    setGourceDefaults();

    if(gource_settings == 0) gource_settings = conffile.getSection(default_section_name);

    if(gource_settings == 0) {
        gource_settings = conffile.addSection("gource");
    }

    ConfEntry* entry = 0;

    //hide flags

    std::vector<std::string> hide_fields;

    if((entry = gource_settings->getEntry("hide")) != 0) {

        if(!entry->hasValue()) conffile.missingValueException(entry);

        std::string hide_string = entry->getString();

        size_t sep;
        while((sep = hide_string.find(",")) != std::string::npos) {

            if(sep == 0 && hide_string.size()==1) break;

            if(sep == 0) {
                hide_string = hide_string.substr(sep+1, hide_string.size()-1);
                continue;
            }

            std::string hide_field  = hide_string.substr(0, sep);
            hide_fields.push_back(hide_field);
            hide_string = hide_string.substr(sep+1, hide_string.size()-1);
        }

        if(hide_string.size() > 0 && hide_string != ",") hide_fields.push_back(hide_string);

        //validate field list

        for(std::vector<std::string>::iterator it = hide_fields.begin(); it != hide_fields.end(); it++) {
            std::string hide_field = (*it);

            if(   hide_field != "date"
               && hide_field != "users"
               && hide_field != "tree"
               && hide_field != "files"
               && hide_field != "usernames"
               && hide_field != "filenames"
               && hide_field != "dirnames"
               && hide_field != "bloom"
               && hide_field != "progress"
               && hide_field != "mouse"
               && hide_field != "root") {
                std::string unknown_hide_option = std::string("unknown option hide ") + hide_field;
                conffile.entryException(entry, unknown_hide_option);
            }
        }
    }

    //check hide booleans
    for(std::map<std::string,std::string>::iterator it = arg_types.begin(); it != arg_types.end(); it++) {
        if(it->first.find("hide-") == 0 && it->second == "bool") {

            if(gource_settings->getBool(it->first)) {
                std::string hide_field = it->first.substr(5, it->first.size()-5);
                hide_fields.push_back(hide_field);
            }
        }
    }

    if(hide_fields.size()>0) {

        for(std::vector<std::string>::iterator it = hide_fields.begin(); it != hide_fields.end(); it++) {
            std::string hidestr = (*it);

                if(hidestr == "date")       hide_date      = true;
            else if(hidestr == "users")     hide_users     = true;
            else if(hidestr == "tree")      hide_tree      = true;
            else if(hidestr == "files")     hide_files     = true;
            else if(hidestr == "usernames") hide_usernames = true;
            else if(hidestr == "filenames") hide_filenames = true;
            else if(hidestr == "dirnames")  hide_dirnames  = true;
            else if(hidestr == "bloom")     hide_bloom     = true;
            else if(hidestr == "progress")  hide_progress  = true;
            else if(hidestr == "root")      hide_root      = true;
            else if(hidestr == "mouse")     {
                hide_mouse     = true;
                hide_progress  = true;
            }
        }
    }

    if((entry = gource_settings->getEntry("date-format")) != 0) {

        if(!entry->hasValue()) conffile.missingValueException(entry);

        date_format = entry->getString();
    }

    if(gource_settings->getBool("disable-auto-rotate")) {
        disable_auto_rotate=true;
    }

    if(gource_settings->getBool("disable-auto-skip")) {
        auto_skip_seconds = -1.0;
    }

    if(gource_settings->getBool("loop")) {
        loop = true;
    }

    if((entry = gource_settings->getEntry("git-branch")) != 0) {

        if(!entry->hasValue()) conffile.missingValueException(entry);

        git_branch = entry->getString();
    }

    if(gource_settings->getBool("colour-images")) {
        colour_user_images = true;
    }

    if((entry = gource_settings->getEntry("crop")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify crop (vertical,horizontal)");

        std::string crop = entry->getString();

        if(crop == "vertical") {
            crop_vertical = true;
        } else if (crop == "horizontal") {
            crop_horizontal = true;
        } else {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("log-format")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify log-format (format)");

        log_format = entry->getString();

        if(log_format == "cvs") {
            conffile.entryException(entry, "please use either 'cvs2cl' or 'cvs-exp'");
        }

        if(   log_format != "git"
           && log_format != "cvs-exp"
           && log_format != "cvs2cl"
           && log_format != "svn"
           && log_format != "custom"
           && log_format != "hg"
           && log_format != "bzr"
           && log_format != "apache") {

            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("default-user-image")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify default-user-image (image path)");

        default_user_image = entry->getString();
    }

    if((entry = gource_settings->getEntry("user-image-dir")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify user-image-dir (directory)");

        user_image_dir = entry->getString();

        //append slash
        if(user_image_dir[user_image_dir.size()-1] != '/') {
            user_image_dir += std::string("/");
        }

        //get jpg and png images in dir
        DIR *dp;
        struct dirent *dirp;

        user_image_map.clear();

        if((dp = opendir(gGourceSettings.user_image_dir.c_str())) != 0) {

            while ((dirp = readdir(dp)) != 0) {
                std::string dirfile = std::string(dirp->d_name);

                size_t extpos = 0;

                if(   (extpos=dirfile.rfind(".jpg"))  == std::string::npos
                && (extpos=dirfile.rfind(".jpeg")) == std::string::npos
                && (extpos=dirfile.rfind(".png"))  == std::string::npos) continue;


                std::string image_path = gGourceSettings.user_image_dir + dirfile;
                std::string name       = dirfile.substr(0,extpos);

#ifdef __APPLE__
                CFMutableStringRef help = CFStringCreateMutable(kCFAllocatorDefault, 0);
                CFStringAppendCString(help, name.c_str(), kCFStringEncodingUTF8);
                CFStringNormalize(help, kCFStringNormalizationFormC);
                char data[4096];
                CFStringGetCString(help,
                                   data,
                                   sizeof(data),
                                   kCFStringEncodingUTF8);
                name = data;
#endif

                debugLog("%s => %s\n", name.c_str(), image_path.c_str());

                user_image_map[name] = image_path;
            }

            closedir(dp);
        }
    }

    if((entry = gource_settings->getEntry("bloom-intensity")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify bloom-intensity (float)");

        bloom_intensity = entry->getFloat();

        if(bloom_intensity<=0.0f) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("bloom-multiplier")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify bloom-multiplier (float)");

        bloom_multiplier = entry->getFloat();

        if(bloom_multiplier<=0.0f) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("elasticity")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify elasticity (float)");

        elasticity = entry->getFloat();

        if(elasticity<=0.0f) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("font-size")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify font size");

        font_size = entry->getInt();

        if(font_size<1 || font_size>100) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("hash-seed")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify hash seed (integer)");

        gStringHashSeed = entry->getInt();
    }

    if((entry = gource_settings->getEntry("font-colour")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify font colour (FFFFFF)");

        int r,g,b;

        std::string colstring = entry->getString();

        if(entry->isVec3()) {
            font_colour = entry->getVec3();
        } else if(colstring.size()==6 && sscanf(colstring.c_str(), "%02x%02x%02x", &r, &g, &b) == 3) {
            font_colour = vec3(r,g,b);
            font_colour /= 255.0f;
        } else {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("background-colour")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify background colour (FFFFFF)");

        int r,g,b;

        std::string colstring = entry->getString();

        if(entry->isVec3()) {
            background_colour = entry->getVec3();
        } else if(colstring.size()==6 && sscanf(colstring.c_str(), "%02x%02x%02x", &r, &g, &b) == 3) {
            background_colour = vec3(r,g,b);
            background_colour /= 255.0f;
        } else {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("highlight-colour")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify highlight colour (FFFFFF)");

        int r,g,b;

        std::string colstring = entry->getString();

        if(entry->isVec3()) {
            highlight_colour = entry->getVec3();
        } else if(colstring.size()==6 && sscanf(colstring.c_str(), "%02x%02x%02x", &r, &g, &b) == 3) {
            highlight_colour = vec3(r,g,b);
            highlight_colour /= 255.0f;
        } else {
            conffile.invalidValueException(entry);
        }
    }
    
    if((entry = gource_settings->getEntry("selection-colour")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify selection colour (FFFFFF)");

        int r,g,b;

        std::string colstring = entry->getString();

        if(entry->isVec3()) {
            selection_colour = entry->getVec3();
        } else if(colstring.size()==6 && sscanf(colstring.c_str(), "%02x%02x%02x", &r, &g, &b) == 3) {
            selection_colour = vec3(r,g,b);
            selection_colour /= 255.0f;
        } else {
            conffile.invalidValueException(entry);
        }
    }    
    
    if((entry = gource_settings->getEntry("dir-colour")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify dir colour (FFFFFF)");

        int r,g,b;

        std::string colstring = entry->getString();

        if(entry->isVec3()) {
            dir_colour = entry->getVec3();
        } else if(colstring.size()==6 && sscanf(colstring.c_str(), "%02x%02x%02x", &r, &g, &b) == 3) {
            dir_colour = vec3(r,g,b);
            dir_colour /= 255.0f;
        } else {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("background-image")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify background image (image path)");

        background_image = entry->getString();
    }

    if((entry = gource_settings->getEntry("title")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify title");

        title = entry->getString();
    }

    if((entry = gource_settings->getEntry("logo")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify logo (image path)");

        logo = entry->getString();
    }

    if((entry = gource_settings->getEntry("logo-offset")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify logo-offset (XxY)");

        std::string logo_offset_str = entry->getString();

        int posx = 0;
        int posy = 0;

        if(parseRectangle(logo_offset_str, posx, posy)) {
            logo_offset = vec2(posx, posy);
        } else {
            conffile.invalidValueException(entry);
        }

    }

    if((entry = gource_settings->getEntry("seconds-per-day")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify seconds-per-day (seconds)");

        float seconds_per_day = entry->getFloat();

        if(seconds_per_day<=0.0f) {
            conffile.invalidValueException(entry);
        }

        // convert seconds-per-day to days-per-second
        days_per_second = 1.0 / seconds_per_day;
    }

    if((entry = gource_settings->getEntry("auto-skip-seconds")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify auto-skip-seconds (seconds)");

        auto_skip_seconds = entry->getFloat();

        if(auto_skip_seconds <= 0.0) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("file-idle-time")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify file-idle-time (seconds)");

        std::string file_idle_str = entry->getString();

        file_idle_time = (float) atoi(file_idle_str.c_str());

        if(file_idle_time<0.0f || file_idle_time == 0.0f && file_idle_str[0] != '0' ) {
            conffile.invalidValueException(entry);
        }
        if(file_idle_time==0.0f) {
            file_idle_time = 86400.0f;
        }
    }

    if((entry = gource_settings->getEntry("user-idle-time")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify user-idle-time (seconds)");

        user_idle_time = entry->getFloat();

        if(user_idle_time < 0.0f) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("time-scale")) != 0) {

        if(!entry->hasValue())
            conffile.entryException(entry, "specify time-scale (scale)");

        time_scale = entry->getFloat();

        if(time_scale <= 0.0f || time_scale > 4.0f) {
            conffile.entryException(entry, "time-scale outside of range 0.0 - 4.0");
        }
    }

    if((entry = gource_settings->getEntry("start-position")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify start-position (float,random)");

        if(entry->getString() == "random") {
            srand(time(0));
            start_position = (rand() % 1000) / 1000.0f;
        } else {
            start_position = entry->getFloat();

            if(start_position<=0.0 || start_position>=1.0) {
                conffile.entryException(entry, "start-position outside of range 0.0 - 1.0 (non-inclusive)");
            }
        }
    }

    if((entry = gource_settings->getEntry("stop-position")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify stop-position (float)");

        stop_position = entry->getFloat();

        if(stop_position<=0.0 || stop_position>1.0) {
            conffile.entryException(entry, "stop-position outside of range 0.0 - 1.0 (inclusive)");
        }
    }

    if((entry = gource_settings->getEntry("stop-at-time")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify stop-at-time (seconds)");

        stop_at_time = entry->getFloat();

        if(stop_at_time <= 0.0) {
            conffile.invalidValueException(entry);
        }
    }

    if(gource_settings->getBool("key")) {
        show_key = true;
    }

    if(gource_settings->getBool("ffp")) {
        ffp = true;
    }

    if(gource_settings->getBool("realtime")) {
        days_per_second = 1.0 / 86400.0;
    }

    if(gource_settings->getBool("dont-stop")) {
        dont_stop = true;
    }

    if(gource_settings->getBool("stop-at-end")) {
        stop_at_end = true;
    }

    //NOTE: this no longer does anything
    if(gource_settings->getBool("stop-on-idle")) {
        stop_on_idle = true;
    }

    if((entry = gource_settings->getEntry("max-files")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify max-files (number)");

        max_files = entry->getInt();

        if(max_files<0 || max_files == 0 && entry->getString() != "0") {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("max-file-lag")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify max-file-lag (seconds)");

        max_file_lag = entry->getFloat();

        if(max_file_lag==0.0) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("user-friction")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify user-friction (seconds)");

        user_friction = entry->getFloat();

        if(user_friction<=0.0) {
            conffile.invalidValueException(entry);
        }

        user_friction = 1.0 / user_friction;
    }

    if((entry = gource_settings->getEntry("user-scale")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify user-scale (scale)");

        user_scale = entry->getFloat();

        if(user_scale<=0.0 || user_scale>100.0) {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("max-user-speed")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify max-user-speed (units)");

        max_user_speed = entry->getFloat();

        if(max_user_speed<=0) {
            conffile.invalidValueException(entry);
        }
    }

    if(   gource_settings->getBool("highlight-users")
       || gource_settings->getBool("highlight-all-users")) {
        highlight_all_users = true;
    }

    if(gource_settings->getBool("highlight-dirs")) {
        highlight_dirs = true;
    }

    if((entry = gource_settings->getEntry("camera-mode")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify camera-mode (overview,track)");

        camera_mode = entry->getString();

        if(camera_mode != "overview" && camera_mode != "track") {
            conffile.invalidValueException(entry);
        }
    }

    if((entry = gource_settings->getEntry("padding")) != 0) {

        if(!entry->hasValue()) conffile.entryException(entry, "specify padding (float)");

        padding = entry->getFloat();

        if(padding <= 0.0f || padding >= 2.0f) {
            conffile.invalidValueException(entry);
        }
    }

    // multi-value entries

    if((entry = gource_settings->getEntry("highlight-user")) != 0) {

        ConfEntryList* highlight_user_entries = gource_settings->getEntries("highlight-user");

        for(ConfEntryList::iterator it = highlight_user_entries->begin(); it != highlight_user_entries->end(); it++) {

            entry = *it;

            if(!entry->hasValue()) conffile.entryException(entry, "specify highlight-user (user)");

            highlight_users.push_back(entry->getString());
        }
    }

    if((entry = gource_settings->getEntry("follow-user")) != 0) {

        ConfEntryList* follow_user_entries = gource_settings->getEntries("follow-user");

        for(ConfEntryList::iterator it = follow_user_entries->begin(); it != follow_user_entries->end(); it++) {

            entry = *it;

            if(!entry->hasValue()) conffile.entryException(entry, "specify follow-user (user)");

            follow_users.push_back(entry->getString());
        }
    }

    if(gource_settings->getBool("file-extensions")) {
        file_extensions=true;
    }

    if((entry = gource_settings->getEntry("file-filter")) != 0) {

        ConfEntryList* filters = gource_settings->getEntries("file-filter");

        for(ConfEntryList::iterator it = filters->begin(); it != filters->end(); it++) {

            entry = *it;

            if(!entry->hasValue()) conffile.entryException(entry, "specify file-filter (regex)");

            std::string filter_string = entry->getString();

            Regex* r = new Regex(filter_string, 1);

            if(!r->isValid()) {
                delete r;
                conffile.entryException(entry, "invalid file-filter regular expression");
            }

            file_filters.push_back(r);
        }
    }

    if((entry = gource_settings->getEntry("user-filter")) != 0) {

        ConfEntryList* filters = gource_settings->getEntries("user-filter");

        for(ConfEntryList::iterator it = filters->begin(); it != filters->end(); it++) {

            entry = *it;

            if(!entry->hasValue()) conffile.entryException(entry, "specify user-filter (regex)");

            std::string filter_string = entry->getString();

            Regex* r = new Regex(filter_string, 1);

            if(!r->isValid()) {
                delete r;
                conffile.entryException(entry, "invalid user-filter regular expression");
            }

            user_filters.push_back(r);
        }
    }

    //validate path
    if(gource_settings->hasValue("path")) {
        path = gource_settings->getString("path");
    }

    if(path == "-") {

        if(log_format.size() == 0) {
            throw ConfFileException("log-format required when reading from STDIN", "", 0);
        }

#ifdef _WIN32
        DWORD available_bytes;
        HANDLE stdin_handle = GetStdHandle(STD_INPUT_HANDLE);

        while(PeekNamedPipe(stdin_handle, 0, 0, 0,
            &available_bytes, 0) && available_bytes==0 && !std::cin.fail()) {
            SDL_Delay(100);
        }
#else
        while(std::cin.peek() == EOF && !std::cin.fail()) SDL_Delay(100);
#endif

        std::cin.clear();
    }

    //remove trailing slash and check if path is a directory
    if(path.size() &&
    (path[path.size()-1] == '\\' || path[path.size()-1] == '/')) {
        path = path.substr(0,path.size()-1);
    }

#ifdef _WIN32
    //on windows, pre-open console window if we think this is a directory the
    //user is trying to open, as system() commands will create a console window
    //if there isn't one anyway.

    bool isdir = false;

    if(path.size()>0) {
        struct stat fileinfo;
        int rc = stat(path.c_str(), &fileinfo);

        if(rc==0 && fileinfo.st_mode & S_IFDIR) isdir = true;
    }

    if(path.size()==0 || isdir) {
        SDLAppCreateWindowsConsole();
    }
#endif
}