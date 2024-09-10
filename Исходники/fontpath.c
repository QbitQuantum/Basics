static int CALLBACK EnumFamilyNamesW(
  ENUMLOGFONTEXW *lpelfe,    /* pointer to logical-font data */
  NEWTEXTMETRICEX *lpntme,  /* pointer to physical-font data */
  int FontType,             /* type of font */
  LPARAM lParam )           /* application-defined data */
{
    GdiFontMapInfo *fmi = (GdiFontMapInfo*)lParam;
    JNIEnv *env = fmi->env;
    jstring familyLC;
    size_t slen;
    LOGFONTW lfw;

    /* Both Vista and XP return DEVICE_FONTTYPE for OTF fonts */
    if (FontType != TRUETYPE_FONTTYPE && FontType != DEVICE_FONTTYPE) {
        return 1;
    }
/*     wprintf(L"FAMILY=%s charset=%d FULL=%s\n", */
/*          lpelfe->elfLogFont.lfFaceName, */
/*          lpelfe->elfLogFont.lfCharSet, */
/*          lpelfe->elfFullName); */
/*     fflush(stdout); */

    /* Windows lists fonts which have a vmtx (vertical metrics) table twice.
     * Once using their normal name, and again preceded by '@'. These appear
     * in font lists in some windows apps, such as wordpad. We don't want
     * these so we skip any font where the first character is '@'
     */
    if (lpelfe->elfLogFont.lfFaceName[0] == L'@') {
            return 1;
    }
    slen = wcslen(lpelfe->elfLogFont.lfFaceName);
    fmi->family = (*env)->NewString(env,lpelfe->elfLogFont.lfFaceName, (jsize)slen);
    if (fmi->family == NULL) {
        (*env)->ExceptionClear(env);
        return 1;
    }
    familyLC = (*env)->CallObjectMethod(env, fmi->family,
                                        fmi->toLowerCaseMID, fmi->locale);
    /* check if already seen this family with a different charset */
    if ((*env)->CallBooleanMethod(env,fmi->familyToFontListMap,
                                  fmi->containsKeyMID, familyLC)) {
        return 1;
    }
    fmi->list = (*env)->NewObject(env,
                                  fmi->arrayListClass, fmi->arrayListCtr, 4);
    if (fmi->list == NULL) {
        (*env)->ExceptionClear(env);
        return 1;
    }
    (*env)->CallObjectMethod(env, fmi->familyToFontListMap,
                             fmi->putMID, familyLC, fmi->list);

    memset(&lfw, 0, sizeof(lfw));
    wcscpy(lfw.lfFaceName, lpelfe->elfLogFont.lfFaceName);
    lfw.lfCharSet = lpelfe->elfLogFont.lfCharSet;
    EnumFontFamiliesExW(screenDC, &lfw,
                        (FONTENUMPROCW)EnumFontFacesInFamilyProcW,
                        lParam, 0L);
    return 1;
}