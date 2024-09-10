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
        module_spec.GetFileSpec().SetFile(str.c_str(), true);
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
        module_spec.GetSymbolFileSpec().SetFile(str.c_str(), true);
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
        FileSpec resolved_source_path(DBGSourcePath.c_str(), true);
        DBGSourcePath = resolved_source_path.GetPath();
      }
      module_spec.GetSourceMappingList().Append(
          ConstString(DBGBuildSourcePath.c_str()),
          ConstString(DBGSourcePath.c_str()), true);
    }

    cf_dict = (CFDictionaryRef)CFDictionaryGetValue(
        (CFDictionaryRef)uuid_dict, CFSTR("DBGSourcePathRemapping"));
    if (cf_dict && CFGetTypeID(cf_dict) == CFDictionaryGetTypeID()) {
      // If we see DBGVersion with a value of 2 or higher, this is a new style
      // DBGSourcePathRemapping dictionary
      bool new_style_source_remapping_dictionary = false;
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
            // DBGSourcePath values
            // (the "values" half of key-value path pairs) were wrong.  Ignore
            // them and use the
            // universal DBGSourcePath string from earlier.
            if (new_style_source_remapping_dictionary == true &&
                !original_DBGSourcePath_value.empty()) {
              DBGSourcePath = original_DBGSourcePath_value;
            }
            if (DBGSourcePath[0] == '~') {
              FileSpec resolved_source_path(DBGSourcePath.c_str(), true);
              DBGSourcePath = resolved_source_path.GetPath();
            }
            module_spec.GetSourceMappingList().Append(
                ConstString(DBGBuildSourcePath.c_str()),
                ConstString(DBGSourcePath.c_str()), true);
          }
        }
        if (keys)
          free(keys);
        if (values)
          free(values);
      }
    }
  }
  return success;
}