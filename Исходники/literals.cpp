ValueHolderPtr parseIntLiteral(ModulePtr module, IntLiteral *x)
{
    CompilerState* cst = module->cst;
    TypePtr defaultType = module->attrDefaultIntegerType.ptr();
    if (defaultType == NULL)
        defaultType = cst->int32Type;

    char *ptr = const_cast<char *>(x->value.c_str());
    char *end = ptr;
    int base = ishex(ptr) ? 16 : 10;
    ValueHolderPtr vh;
    if (typeSuffix(x->suffix, defaultType, "ss", cst->int8Type)) {
        long y = strtol(ptr, &end, base);
        if (*end != 0)
            error("invalid int8 literal");
        if ((errno == ERANGE) || (y < SCHAR_MIN) || (y > SCHAR_MAX))
            error("int8 literal out of range");
        vh = new ValueHolder(cst->int8Type);
        *((char *)vh->buf) = (char)y;
    }
    else if (typeSuffix(x->suffix, defaultType, "s", cst->int16Type)) {
        long y = strtol(ptr, &end, base);
        if (*end != 0)
            error("invalid int16 literal");
        if ((errno == ERANGE) || (y < SHRT_MIN) || (y > SHRT_MAX))
            error("int16 literal out of range");
        vh = new ValueHolder(cst->int16Type);
        *((short *)vh->buf) = (short)y;
    }
    else if (typeSuffix(x->suffix, defaultType, "i", cst->int32Type)) {
        long y = strtol(ptr, &end, base);
        if (*end != 0)
            error("invalid int32 literal");
        if (errno == ERANGE || (y < INT_MIN) || (y > INT_MAX))
            error("int32 literal out of range");
        vh = new ValueHolder(cst->int32Type);
        *((int *)vh->buf) = (int)y;
    }
    else if (typeSuffix(x->suffix, defaultType, "l", cst->int64Type)) {
        long long y = strtoll(ptr, &end, base);
        if (*end != 0)
            error("invalid int64 literal");
        if (errno == ERANGE)
            error("int64 literal out of range");
        vh = new ValueHolder(cst->int64Type);
        *((long long *)vh->buf) = y;
    }
    else if (typeSuffix(x->suffix, defaultType, "ll", cst->int128Type)) {
        long long y = strtoll(ptr, &end, base);
        if (*end != 0)
            error("invalid int128 literal");
        if (errno == ERANGE)
            error("int128 literal out of range");
        vh = new ValueHolder(cst->int128Type);
        *((clay_int128 *)vh->buf) = y;
    }
    else if (typeSuffix(x->suffix, defaultType, "uss", cst->uint8Type)) {
        unsigned long y = strtoul(ptr, &end, base);
        if (*end != 0)
            error("invalid uint8 literal");
        if ((errno == ERANGE) || (y > UCHAR_MAX))
            error("uint8 literal out of range");
        vh = new ValueHolder(cst->uint8Type);
        *((unsigned char *)vh->buf) = (unsigned char)y;
    }
    else if (typeSuffix(x->suffix, defaultType, "us", cst->uint16Type)) {
        unsigned long y = strtoul(ptr, &end, base);
        if (*end != 0)
            error("invalid uint16 literal");
        if ((errno == ERANGE) || (y > USHRT_MAX))
            error("uint16 literal out of range");
        vh = new ValueHolder(cst->uint16Type);
        *((unsigned short *)vh->buf) = (unsigned short)y;
    }
    else if (typeSuffix(x->suffix, defaultType, "u", cst->uint32Type)) {
        unsigned long y = strtoul(ptr, &end, base);
        if (*end != 0)
            error("invalid uint32 literal");
        if (errno == ERANGE)
            error("uint32 literal out of range");
        vh = new ValueHolder(cst->uint32Type);
        *((unsigned int *)vh->buf) = (unsigned int)y;
    }
    else if (typeSuffix(x->suffix, defaultType, "ul", cst->uint64Type)) {
        unsigned long long y = strtoull(ptr, &end, base);
        if (*end != 0)
            error("invalid uint64 literal");
        if (errno == ERANGE)
            error("uint64 literal out of range");
        vh = new ValueHolder(cst->uint64Type);
        *((unsigned long long *)vh->buf) = y;
    }
    else if (typeSuffix(x->suffix, defaultType, "ull", cst->uint128Type)) {
        unsigned long long y = strtoull(ptr, &end, base);
        if (*end != 0)
            error("invalid uint128 literal");
        if (errno == ERANGE)
            error("uint128 literal out of range");
        vh = new ValueHolder(cst->uint128Type);
        *((clay_uint128 *)vh->buf) = y;
    }
    else if (x->suffix == "f") {
        float y = (float)clay_strtod(ptr, &end);
        if (*end != 0)
            error("invalid float32 literal");
        if (errno == ERANGE)
            error("float32 literal out of range");
        vh = new ValueHolder(cst->float32Type);
        *((float *)vh->buf) = y;
    }
    else if (x->suffix == "ff") {
        double y = clay_strtod(ptr, &end);
        if (*end != 0)
            error("invalid float64 literal");
        if (errno == ERANGE)
            error("float64 literal out of range");
        vh = new ValueHolder(cst->float64Type);
        *((double *)vh->buf) = y;
    }
    else if (x->suffix == "fl") {
        long double y = clay_strtold(ptr, &end);
        if (*end != 0)
            error("invalid float80 literal");
        if (errno == ERANGE)
            error("float80 literal out of range");
        vh = new ValueHolder(cst->float80Type);
        *((long double *)vh->buf) = y;
    }
    else if (x->suffix == "fj") {
        float y = (float)clay_strtod(ptr, &end);
        if (*end != 0)
            error("invalid imag32 literal");
        if (errno == ERANGE)
            error("imag32 literal out of range");
        vh = new ValueHolder(cst->imag32Type);
        *((float *)vh->buf) = y;
    }
    else if (x->suffix == "j" || x->suffix == "ffj") {
        double y = clay_strtod(ptr, &end);
        if (*end != 0)
            error("invalid imag64 literal");
        if (errno == ERANGE)
            error("imag64 literal out of range");
        vh = new ValueHolder(cst->imag64Type);
        *((double *)vh->buf) = y;
    }
    else if (x->suffix == "lj" || x->suffix == "flj") {
        long double y = clay_strtold(ptr, &end);
        if (*end != 0)
            error("invalid imag80 literal");
        if (errno == ERANGE)
            error("imag80 literal out of range");
        vh = new ValueHolder(cst->imag80Type);
        *((long double *)vh->buf) = y;
    }
    else {
        error("invalid literal suffix: " + x->suffix);
    }
    return vh;
}