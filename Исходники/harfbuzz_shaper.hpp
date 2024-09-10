static inline hb_script_t _icu_script_to_script(UScriptCode script)
{
    if (script == USCRIPT_INVALID_CODE) return HB_SCRIPT_INVALID;
        return hb_script_from_string(uscript_getShortName(script), -1);
}