static int utf8_codepoint_is_left_to_right(UChar32 c) {
    return (u_charDirection(c) == U_LEFT_TO_RIGHT);
}