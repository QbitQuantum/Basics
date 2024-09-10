static bool GetModuleSpecInfoFromUUIDDictionary(CFDictionaryRef uuid_dict,
                                                ModuleSpec &module_spec) {
  Log *log = lldb_private::GetLogIfAllCategoriesSet(LIBLLDB_LOG_HOST);
  bool success = false;
  if (uuid_dict != NULL && CFGetTypeID(uuid_dict) == CFDictionaryGetTypeID()) {
    std::string str;
    CFStringRef cf_str;
    CFDictionaryRef cf_dict;

    cf_str = (CFStringRef)CFDictionaryGetValue(
        (CFDictionaryRef)uuid_dict, CFSTR("DBGSymbolRichExecutable"));
    if (cf_str && CFGetTypeID(cf_str) == CFStringGetTypeID()) {
      if (CFCString::FileSystemRepresentation(cf_str, str)) {
        module_spec.GetFileSpec().SetFile(str.c_str(), FileSpec::Style::native);
        FileSystem::Instance().Resolve(module_spec.GetFileSpec());
        if (log) {
          log->Printf(
              "From dsymForUUID plist: Symbol rich executable is at '%s'",
              str.c_str());
        }
      }
    }

    cf_str = (CFStringRef)CFDictionaryGetValue((CFDictionaryRef)uuid_dict,
                                               CFSTR("DBGDSYMPath"));
    if (cf_str && CFGetTypeID(cf_str) == CFStringGetTypeID()) {
      if (CFCString::FileSystemRepresentation(cf_str, str)) {
        module_spec.GetSymbolFileSpec().SetFile(str.c_str(),
                                                FileSpec::Style::native);
        FileSystem::Instance().Resolve(module_spec.GetFileSpec());
        success = true;
        if (log) {
          log->Printf("From dsymForUUID plist: dSYM is at '%s'", str.c_str());
        }
      }
    }

    cf_str = (CFStringRef)CFDictionaryGetValue((CFDictionaryRef)uuid_dict,
                                               CFSTR("DBGArchitecture"));
    if (cf_str && CFGetTypeID(cf_str) == CFStringGetTypeID()) {
      if (CFCString::FileSystemRepresentation(cf_str, str))
        module_spec.GetArchitecture().SetTriple(str.c_str());
    }

    std::string DBGBuildSourcePath;
    std::string DBGSourcePath;

    // If DBGVersion 1 or DBGVersion missing, ignore DBGSourcePathRemapping.
    // If DBGVersion 2, strip last two components of path remappings from
    //                  entries to fix an issue with a specific set of
    //                  DBGSourcePathRemapping entries that lldb worked
    //                  with.
    // If DBGVersion 3, trust & use the source path remappings as-is.
    //
    cf_dict = (CFDictionaryRef)CFDictionaryGetValue(
        (CFDictionaryRef)uuid_dict, CFSTR("DBGSourcePathRemapping"));
    if (cf_dict && CFGetTypeID(cf_dict) == CFDictionaryGetTypeID()) {
      // If we see DBGVersion with a value of 2 or higher, this is a new style
      // DBGSourcePathRemapping dictionary
      bool new_style_source_remapping_dictionary = false;
      bool do_truncate_remapping_names = false;
      std::string original_DBGSourcePath_value = DBGSourcePath;
      cf_str = (CFStringRef)CFDictionaryGetValue((CFDictionaryRef)uuid_dict,
                                                 CFSTR("DBGVersion"));
      if (cf_str && CFGetTypeID(cf_str) == CFStringGetTypeID()) {
        std::string version;
        CFCString::FileSystemRepresentation(cf_str, version);
        if (!version.empty() && isdigit(version[0])) {
          int version_number = atoi(version.c_str());
          if (version_number > 1) {
            new_style_source_remapping_dictionary = true;
          }
          if (version_number == 2) {
            do_truncate_remapping_names = true;
          }
        }
      }

      CFIndex kv_pair_count = CFDictionaryGetCount((CFDictionaryRef)uuid_dict);
      if (kv_pair_count > 0) {
        CFStringRef *keys =
            (CFStringRef *)malloc(kv_pair_count * sizeof(CFStringRef));
        CFStringRef *values =
            (CFStringRef *)malloc(kv_pair_count * sizeof(CFStringRef));
        if (keys != nullptr && values != nullptr) {
          CFDictionaryGetKeysAndValues((CFDictionaryRef)uuid_dict,
                                       (const void **)keys,
                                       (const void **)values);
        }
        for (CFIndex i = 0; i < kv_pair_count; i++) {
          DBGBuildSourcePath.clear();
          DBGSourcePath.clear();
          if (keys[i] && CFGetTypeID(keys[i]) == CFStringGetTypeID()) {
            CFCString::FileSystemRepresentation(keys[i], DBGBuildSourcePath);
          }
          if (values[i] && CFGetTypeID(values[i]) == CFStringGetTypeID()) {
            CFCString::FileSystemRepresentation(values[i], DBGSourcePath);
          }
          if (!DBGBuildSourcePath.empty() && !DBGSourcePath.empty()) {
            // In the "old style" DBGSourcePathRemapping dictionary, the
            // DBGSourcePath values (the "values" half of key-value path pairs)
            // were wrong.  Ignore them and use the universal DBGSourcePath
            // string from earlier.
            if (new_style_source_remapping_dictionary &&
                !original_DBGSourcePath_value.empty()) {
              DBGSourcePath = original_DBGSourcePath_value;
            }
            if (DBGSourcePath[0] == '~') {
              FileSpec resolved_source_path(DBGSourcePath.c_str());
              FileSystem::Instance().Resolve(resolved_source_path);
              DBGSourcePath = resolved_source_path.GetPath();
            }
            // With version 2 of DBGSourcePathRemapping, we can chop off the
            // last two filename parts from the source remapping and get a more
            // general source remapping that still works. Add this as another
            // option in addition to the full source path remap.
            module_spec.GetSourceMappingList().Append(
                ConstString(DBGBuildSourcePath.c_str()),
                ConstString(DBGSourcePath.c_str()), true);
            if (do_truncate_remapping_names) {
              FileSpec build_path(DBGBuildSourcePath.c_str());
              FileSpec source_path(DBGSourcePath.c_str());
              build_path.RemoveLastPathComponent();
              build_path.RemoveLastPathComponent();
              source_path.RemoveLastPathComponent();
              source_path.RemoveLastPathComponent();
              module_spec.GetSourceMappingList().Append(
                  ConstString(build_path.GetPath().c_str()),
                  ConstString(source_path.GetPath().c_str()), true);
            }
          }
        }
        if (keys)
          free(keys);
        if (values)
          free(values);
      }
    }

    // If we have a DBGBuildSourcePath + DBGSourcePath pair, append them to the
    // source remappings list.

    cf_str = (CFStringRef)CFDictionaryGetValue((CFDictionaryRef)uuid_dict,
                                               CFSTR("DBGBuildSourcePath"));
    if (cf_str && CFGetTypeID(cf_str) == CFStringGetTypeID()) {
      CFCString::FileSystemRepresentation(cf_str, DBGBuildSourcePath);
    }

    cf_str = (CFStringRef)CFDictionaryGetValue((CFDictionaryRef)uuid_dict,
                                               CFSTR("DBGSourcePath"));
    if (cf_str && CFGetTypeID(cf_str) == CFStringGetTypeID()) {
      CFCString::FileSystemRepresentation(cf_str, DBGSourcePath);
    }

    if (!DBGBuildSourcePath.empty() && !DBGSourcePath.empty()) {
      if (DBGSourcePath[0] == '~') {
        FileSpec resolved_source_path(DBGSourcePath.c_str());
        FileSystem::Instance().Resolve(resolved_source_path);
        DBGSourcePath = resolved_source_path.GetPath();
      }
      module_spec.GetSourceMappingList().Append(
          ConstString(DBGBuildSourcePath.c_str()),
          ConstString(DBGSourcePath.c_str()), true);
    }
  }
  return success;
}