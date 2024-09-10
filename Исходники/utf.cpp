std::string foldcase(const std::string& str)
{
    return transform(str, [](uint32_t cp)
                     {
                         return u_foldCase(static_cast<UChar32>(cp),
                                           U_FOLD_CASE_DEFAULT);
                     });
}