static VALUE get_value(const char* buffer, int* position, int type) {
    VALUE value;
    switch (type) {
    case 1:
        {
            double d;
            memcpy(&d, buffer + *position, 8);
            value = rb_float_new(d);
            *position += 8;
            break;
        }
    case 2:
    case 13:
        {
            int value_length;
            *position += 4;
            value_length = strlen(buffer + *position);
            value = STR_NEW(buffer + *position, value_length);
            *position += value_length + 1;
            break;
        }
    case 3:
        {
            int size;
            memcpy(&size, buffer + *position, 4);
            if (strcmp(buffer + *position + 5, "$ref") == 0) { // DBRef
                int offset = *position + 14;
                VALUE argv[2];
                int collection_length = strlen(buffer + offset);
                char id_type;

                argv[0] = STR_NEW(buffer + offset, collection_length);
                offset += collection_length + 1;
                id_type = buffer[offset];
                offset += 5;
                argv[1] = get_value(buffer, &offset, (int)id_type);
                value = rb_class_new_instance(2, argv, DBRef);
            } else {
                value = elements_to_hash(buffer + *position + 4, size - 5, 0);
            }
            *position += size;
            break;
        }
    case 4:
        {
            int size, end;
            memcpy(&size, buffer + *position, 4);
            end = *position + size - 1;
            *position += 4;

            value = rb_ary_new();
            while (*position < end) {
                int type = (int)buffer[(*position)++];
                int key_size = strlen(buffer + *position);
                VALUE to_append;

                *position += key_size + 1; // just skip the key, they're in order.
                to_append = get_value(buffer, position, type);
                rb_ary_push(value, to_append);
            }
            (*position)++;
            break;
        }
    case 5:
        {
            int length, subtype;
            VALUE data, st;
            VALUE argv[2];
            memcpy(&length, buffer + *position, 4);
            subtype = (unsigned char)buffer[*position + 4];
            if (subtype == 2) {
                data = rb_str_new(buffer + *position + 9, length - 4);
            } else {
                data = rb_str_new(buffer + *position + 5, length);
            }
            st = INT2FIX(subtype);
            argv[0] = data;
            argv[1] = st;
            value = rb_class_new_instance(2, argv, Binary);
            *position += length + 5;
            break;
        }
    case 6:
        {
            value = Qnil;
            break;
        }
    case 7:
        {
            VALUE str = rb_str_new(buffer + *position, 12);
            VALUE oid = rb_funcall(str, rb_intern("unpack"), 1, rb_str_new2("C*"));
            value = rb_class_new_instance(1, &oid, ObjectID);
            *position += 12;
            break;
        }
    case 8:
        {
            value = buffer[(*position)++] ? Qtrue : Qfalse;
            break;
        }
    case 9:
        {
            long long millis;
            VALUE seconds, microseconds;
            memcpy(&millis, buffer + *position, 8);
            seconds = INT2NUM(millis / 1000);
            microseconds = INT2NUM((millis % 1000) * 1000);

            value = rb_funcall(Time, rb_intern("at"), 2, seconds, microseconds);
            value = rb_funcall(value, rb_intern("utc"), 0);
            *position += 8;
            break;
        }
    case 10:
        {
            value = Qnil;
            break;
        }
    case 11:
        {
            int pattern_length = strlen(buffer + *position);
            VALUE pattern = STR_NEW(buffer + *position, pattern_length);
            int flags_length, flags = 0, i = 0;
            char extra[10];
            VALUE argv[3];
            *position += pattern_length + 1;

            flags_length = strlen(buffer + *position);
            extra[0] = 0;
            for (i = 0; i < flags_length; i++) {
                char flag = buffer[*position + i];
                if (flag == 'i') {
                    flags |= IGNORECASE;
                }
                else if (flag == 'm') {
                    flags |= MULTILINE;
                }
                else if (flag == 'x') {
                    flags |= EXTENDED;
                }
                else if (strlen(extra) < 9) {
                    strncat(extra, &flag, 1);
                }
            }
            argv[0] = pattern;
            argv[1] = INT2FIX(flags);
            argv[2] = rb_str_new2(extra);
            value = rb_class_new_instance(3, argv, RegexpOfHolding);
            *position += flags_length + 1;
            break;
        }
    case 12:
        {
            int collection_length;
            VALUE collection, str, oid, id, argv[2];
            *position += 4;
            collection_length = strlen(buffer + *position);
            collection = STR_NEW(buffer + *position, collection_length);
            *position += collection_length + 1;

            str = rb_str_new(buffer + *position, 12);
            oid = rb_funcall(str, rb_intern("unpack"), 1, rb_str_new2("C*"));
            id = rb_class_new_instance(1, &oid, ObjectID);
            *position += 12;

            argv[0] = collection;
            argv[1] = id;
            value = rb_class_new_instance(2, argv, DBRef);
            break;
        }
    case 14:
        {
            int value_length;
            memcpy(&value_length, buffer + *position, 4);
            value = ID2SYM(rb_intern(buffer + *position + 4));
            *position += value_length + 4;
            break;
        }
    case 15:
        {
            int code_length, scope_size;
            VALUE code, scope, argv[2];
            *position += 8;
            code_length = strlen(buffer + *position);
            code = STR_NEW(buffer + *position, code_length);
            *position += code_length + 1;

            memcpy(&scope_size, buffer + *position, 4);
            scope = elements_to_hash(buffer + *position + 4, scope_size - 5, 0);
            *position += scope_size;

            argv[0] = code;
            argv[1] = scope;
            value = rb_class_new_instance(2, argv, Code);
            break;
        }
    case 16:
        {
            int i;
            memcpy(&i, buffer + *position, 4);
            value = LL2NUM(i);
            *position += 4;
            break;
        }
    case 17:
        {
            int i;
            int j;
            memcpy(&i, buffer + *position, 4);
            memcpy(&j, buffer + *position + 4, 4);
            value = rb_ary_new3(2, LL2NUM(i), LL2NUM(j));
            *position += 8;
            break;
        }
    case 18:
        {
            long long ll;
            memcpy(&ll, buffer + *position, 8);
            value = LL2NUM(ll);
            *position += 8;
            break;
        }
    default:
        {
            rb_raise(rb_eTypeError, "no c decoder for this type yet (%d)", type);
            break;
        }
    }
    return value;
}