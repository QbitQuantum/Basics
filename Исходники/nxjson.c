static char* parse_value(nx_json* parent, const char* key, char* p, nx_json_unicode_encoder encoder) {
  nx_json* js;
  while (1) {
    switch (*p) {
      case '\0':
        NX_JSON_REPORT_ERROR("unexpected end of text", p);
        return 0; // error
      case ' ': case '\t': case '\n': case '\r':
      case ',':
        // skip
        p++;
        break;
      case '{':
        js=create_json(NX_JSON_OBJECT, key, parent);
        p++;
        while (1) {
          const char* new_key;
          p=parse_key(&new_key, p, encoder);
          if (!p) return 0; // error
          if (*p=='}') return p+1; // end of object
          p=parse_value(js, new_key, p, encoder);
          if (!p) return 0; // error
        }
      case '[':
        js=create_json(NX_JSON_ARRAY, key, parent);
        p++;
        while (1) {
          p=parse_value(js, 0, p, encoder);
          if (!p) return 0; // error
          if (*p==']') return p+1; // end of array
        }
      case ']':
        return p;
      case '"':
        p++;
        js=create_json(NX_JSON_STRING, key, parent);
        js->text_value=unescape_string(p, &p, encoder);
        if (!js->text_value) return 0; // propagate error
        return p;
      case '-': case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        {
          js=create_json(NX_JSON_INTEGER, key, parent);
          char* pe;
          js->int_value=strtol(p, &pe, 0);
          if (pe==p) {
            NX_JSON_REPORT_ERROR("invalid number", p);
            return 0; // error
          }
          if (*pe=='.' || *pe=='e' || *pe=='E') { // double value
            js->type=NX_JSON_DOUBLE;
            js->dbl_value=strtod(p, &pe);
            if (pe==p) {
              NX_JSON_REPORT_ERROR("invalid number", p);
              return 0; // error
            }
          }
          else {
            js->dbl_value=js->int_value;
          }
          return pe;
        }
      case 't':
        if (!strncmp(p, "true", 4)) {
          js=create_json(NX_JSON_BOOL, key, parent);
          js->int_value=1;
          return p+4;
        }
        NX_JSON_REPORT_ERROR("unexpected chars", p);
        return 0; // error
      case 'f':
        if (!strncmp(p, "false", 5)) {
          js=create_json(NX_JSON_BOOL, key, parent);
          js->int_value=0;
          return p+5;
        }
        NX_JSON_REPORT_ERROR("unexpected chars", p);
        return 0; // error
      case 'n':
        if (!strncmp(p, "null", 4)) {
          create_json(NX_JSON_NULL, key, parent);
          return p+4;
        }
        NX_JSON_REPORT_ERROR("unexpected chars", p);
        return 0; // error
      case '/': // comment
        if (p[1]=='/') { // line comment
          char* ps=p;
          p=strchr(p+2, '\n');
          if (!p) {
            NX_JSON_REPORT_ERROR("endless comment", ps);
            return 0; // error
          }
          p++;
        }
        else if (p[1]=='*') { // block comment
          p=skip_block_comment(p+2);
          if (!p) return 0;
        }
        else {
          NX_JSON_REPORT_ERROR("unexpected chars", p);
          return 0; // error
        }
        break;
      default:
        NX_JSON_REPORT_ERROR("unexpected chars", p);
        return 0; // error
    }
  }
}