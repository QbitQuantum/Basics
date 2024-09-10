int main(void){
    size_t length;

    plan(7);

    ok(SUCCEEDED(StringCbLengthA("", 1, &length)),
            "Calculate length of empty string.");
    is_int(0, length,
            "Value for length of empty string.");

    ok(SUCCEEDED(StringCbLengthA("test", 5, &length)),
            "Calculate length of short string.");
    is_int(4, length,
            "Value for length of short string.");
    
    ok(SUCCEEDED(StringCbLengthA("test\0test", 10, &length)),
            "Calculate length of string with embedded null character.");
    is_int(4, length,
            "Value for length of string with embedded null character.");
    
    ok(StringCbLengthA("too long", 8, &length) ==
            STRSAFE_E_INVALID_PARAMETER,
            "Make sure error is thrown if null termination is not found.");

    return 0;
}