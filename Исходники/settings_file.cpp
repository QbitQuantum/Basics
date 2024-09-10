static void json_line_str_list(FILE *f, int indent, const char *key, const List<ByteBuffer> &value) {
    do_indent(f, indent);
    fprintf(f, "%s: ", key);
    json_line_indent(f, &indent, "[");
    for (int i = 0; i < value.length(); i += 1) {
        do_indent(f, indent);
        json_inline_str(f, value.at(i));
        fprintf(f, ",\n");
    }
    json_line_outdent(f, &indent, "],\n");
}