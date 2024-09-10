bool ASessionDescription::getDurationUs(int64_t *durationUs) const {
    *durationUs = 0;

    CHECK(mIsValid);

    AString value;
    if (!findAttribute(0, "a=range", &value)) {
        return false;
    }

#ifndef ANDROID_DEFAULT_CODE 
    if (strncmp(value.c_str(), "npt=", 4) && strncmp(value.c_str(), "npt:", 4)) {
#else
    if (strncmp(value.c_str(), "npt=", 4)) {
#endif // #ifndef ANDROID_DEFAULT_CODE
        return false;
    }

    float from, to;
    if (!parseNTPRange(value.c_str() + 4, &from, &to)) {
        return false;
    }

    *durationUs = (int64_t)((to - from) * 1E6);

    return true;
}

// static
void ASessionDescription::ParseFormatDesc(
        const char *desc, int32_t *timescale, int32_t *numChannels) {
    const char *slash1 = strchr(desc, '/');
    CHECK(slash1 != NULL);

    const char *s = slash1 + 1;
    char *end;
    unsigned long x = strtoul(s, &end, 10);
    CHECK_GT(end, s);
    CHECK(*end == '\0' || *end == '/');

    *timescale = x;
    *numChannels = 1;

    if (*end == '/') {
        s = end + 1;
        unsigned long x = strtoul(s, &end, 10);
        CHECK_GT(end, s);
        CHECK_EQ(*end, '\0');

        *numChannels = x;
    }
}

// static
bool ASessionDescription::parseNTPRange(
        const char *s, float *npt1, float *npt2) {
    if (s[0] == '-') {
        return false;  // no start time available.
    }

    if (!strncmp("now", s, 3)) {
        return false;  // no absolute start time available
    }

    char *end;
    *npt1 = strtof(s, &end);

    if (end == s || *end != '-') {
        // Failed to parse float or trailing "dash".
        return false;
    }

    s = end + 1;  // skip the dash.

    if (!strncmp("now", s, 3)) {
        return false;  // no absolute end time available
    }

    *npt2 = strtof(s, &end);
	
#ifndef ANDROID_DEFAULT_CODE
	//We support range string as "Range: npt=1.0000-"
	return true;
#else
	if (end == s || *end != '\0') {
		return false;
	}
	return *npt2 > *npt1;
#endif
}

#ifndef ANDROID_DEFAULT_CODE 
bool ASessionDescription::getBitrate(size_t index, int32_t* bitrate) const {
    char key[] = "b=AS";
    AString value;
    if (!findAttribute(index, key, &value))
        return false;
    int32_t b = atoi(value.c_str());
    b *= 1000;
    if (b < 0)
        return false;
    *bitrate = b;
    return true;
}