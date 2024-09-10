PARROT_EXPORT
void
string_set_data_directory(PARROT_INTERP, ARGIN(const char *dir))
{
    ASSERT_ARGS(string_set_data_directory)
#if PARROT_HAS_ICU
    u_setDataDirectory(dir);

    /* Since u_setDataDirectory doesn't have a result code, we'll spot
       check that everything is okay by making sure that '9' had decimal
       value 9. Using 57 rather than '9' so that the encoding of this
       source code file isn't an issue.... (Don't want to get bitten by
       EBCDIC.) */

    if (!u_isdigit(57) || (u_charDigitValue(57) != 9))
        Parrot_ex_throw_from_c_args(interp, NULL, EXCEPTION_ICU_ERROR,
            "string_set_data_directory: ICU data files not found"
            "(apparently) for directory [%s]", dir);
#else
    UNUSED(dir);

    Parrot_ex_throw_from_c_args(interp, NULL, EXCEPTION_ICU_ERROR,
        "string_set_data_directory: parrot compiled without ICU support");
#endif
}