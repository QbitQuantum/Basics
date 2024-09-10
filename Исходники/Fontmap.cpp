const LEFontInstance *FontMap::getScriptFont(le_int32 scriptCode, LEErrorCode &status)
{
    if (LE_FAILURE(status)) {
        return NULL;
    }

    if (scriptCode <= -1 || scriptCode >= scriptCodeCount) {
        status = LE_ILLEGAL_ARGUMENT_ERROR;
        return NULL;
    }


    le_int32 fontIndex = fFontIndices[scriptCode];

    if (fontIndex < 0) {
        sprintf(errorMessage, "No font was set for script %s", uscript_getName((UScriptCode) scriptCode));
        fGUISupport->postErrorMessage(errorMessage, "Font Map Error");
        status = LE_FONT_FILE_NOT_FOUND_ERROR;
        return NULL;
    }

    if (fFontInstances[fontIndex] == NULL) {
        fFontInstances[fontIndex] = openFont(fFontNames[fontIndex], fPointSize, status);

        if (LE_FAILURE(status)) {
            sprintf(errorMessage, "Could not open font file %s", fFontNames[fontIndex]);
            fGUISupport->postErrorMessage(errorMessage, "Font Map Error");
            return NULL;
        }
    }

    return fFontInstances[fontIndex];
}