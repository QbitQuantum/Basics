std::unique_ptr<UConverter, UConverterDeleter> make_uconv(const std::string& encoding) {
    icu::ErrorCode ec{};
    UConverter* conv_ptr = ucnv_open(encoding.c_str(), ec);
    if (!ec.isSuccess()) throw IcuUtilsException(TRACEMSG(std::string() +
            "Error creating converter for encoding: [" + encoding + "],"
            " error: [" + ec.errorName() + "]"));
    return std::unique_ptr<UConverter, UConverterDeleter>{conv_ptr, UConverterDeleter{}};
}