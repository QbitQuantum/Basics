SV*
V8Context::object2blessed(Handle<Object> obj) {
    char package[128];

    snprintf(
        package,
        128,
        "%s%s::N%d",
        bless_prefix.c_str(),
        *String::AsciiValue(obj->Get(String::New("__perlPackage"))->ToString()),
        number
    );

    HV *stash = gv_stashpv(package, 0);

    if (!stash) {
        Local<Object> prototype = obj->GetPrototype()->ToObject();

        stash = gv_stashpv(package, GV_ADD);

        Local<Array> properties = prototype->GetPropertyNames();
        for (int i = 0; i < properties->Length(); i++) {
            Local<String> name = properties->Get(i)->ToString();
            Local<Value> property = prototype->Get(name);

            if (!property->IsFunction())
                continue;

            Local<Function> fn = Local<Function>::Cast(property);

            CV *code = newXS(NULL, v8method, __FILE__);
            V8ObjectData *data = new V8FunctionData(this, fn, (SV*)code);

            GV* gv = (GV*)*hv_fetch(stash, *String::AsciiValue(name), name->Length(), TRUE);
            gv_init(gv, stash, *String::AsciiValue(name), name->Length(), GV_ADDMULTI); /* vivify */
            my_gv_setsv(aTHX_ gv, (SV*)code);
        }
    }

    SV* rv = newSV(0);
    SV* sv = newSVrv(rv, package);
    V8ObjectData *data = new V8ObjectData(this, obj, sv);
    sv_setiv(sv, PTR2IV(data));

    return rv;
}