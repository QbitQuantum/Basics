    void visit(TemplateInstance *ti)
    {
    #if 0
        printf("TemplateInstance::mangle() %p %s", ti, ti->toChars());
        if (ti->parent)
            printf("  parent = %s %s", ti->parent->kind(), ti->parent->toChars());
        printf("\n");
    #endif

        OutBuffer buf;
        if (!ti->tempdecl)
            ti->error("is not defined");
        else
            mangleParent(&buf, ti);

        ti->getIdent();
        const char *id = ti->ident ? ti->ident->toChars() : ti->toChars();
        buf.printf("%llu%s", (ulonglong)strlen(id), id);
        id = buf.extractString();

        //printf("TemplateInstance::mangle() %s = %s\n", ti->toChars(), ti->id);
        result = id;
    }