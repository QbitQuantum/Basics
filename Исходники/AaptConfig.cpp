bool parse(const String8& str, ConfigDescription* out) {
    Vector<String8> parts = AaptUtil::splitAndLowerCase(str, '-');

    ConfigDescription config;
    AaptLocaleValue locale;
    ssize_t index = 0;
    ssize_t localeIndex = 0;
    const ssize_t N = parts.size();
    const char* part = parts[index].string();

    if (str.length() == 0) {
        goto success;
    }

    if (parseMcc(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseMnc(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    // Locale spans a few '-' separators, so we let it
    // control the index.
    localeIndex = locale.initFromDirName(parts, index);
    if (localeIndex < 0) {
        return false;
    } else if (localeIndex > index) {
        locale.writeTo(&config);
        index = localeIndex;
        if (index >= N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseLayoutDirection(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseSmallestScreenWidthDp(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseScreenWidthDp(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseScreenHeightDp(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseScreenLayoutSize(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseScreenLayoutLong(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseScreenRound(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseOrientation(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseUiModeType(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseUiModeNight(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseDensity(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseTouchscreen(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseKeysHidden(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseKeyboard(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseNavHidden(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseNavigation(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseScreenSize(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    if (parseVersion(part, &config)) {
        index++;
        if (index == N) {
            goto success;
        }
        part = parts[index].string();
    }

    // Unrecognized.
    return false;

success:
    if (out != NULL) {
        applyVersionForCompatibility(&config);
        *out = config;
    }
    return true;
}