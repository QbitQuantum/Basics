void Import::semantic(Scope *sc)
{
    //printf("Import::semantic('%s')\n", toChars());

    // Load if not already done so
    if (!mod)
    {   load(sc);
        mod->importAll(0);
    }

    if (mod)
    {
#if 0
        if (mod->loc.linnum != 0)
        {   /* If the line number is not 0, then this is not
             * a 'root' module, i.e. it was not specified on the command line.
             */
            mod->importedFrom = sc->module->importedFrom;
            assert(mod->importedFrom);
        }
#endif

        // Modules need a list of each imported module
        //printf("%s imports %s\n", sc->module->toChars(), mod->toChars());
        sc->module->aimports.push(mod);

        if (!isstatic && !aliasId && !names.dim)
        {
            /* Default to private importing
             */
            enum PROT prot = sc->protection;
            if (!sc->explicitProtection)
                prot = PROTprivate;
            sc->scopesym->importScope(mod, prot);
        }

        mod->semantic();

        if (mod->needmoduleinfo)
            sc->module->needmoduleinfo = 1;

        sc = sc->push(mod);
        for (size_t i = 0; i < aliasdecls.dim; i++)
        {   Dsymbol *s = (Dsymbol *)aliasdecls.data[i];

            //printf("\tImport alias semantic('%s')\n", s->toChars());
            if (!mod->search(loc, (Identifier *)names.data[i], 0))
                error("%s not found", ((Identifier *)names.data[i])->toChars());

            s->semantic(sc);
        }
        sc = sc->pop();
    }

    if (global.params.moduleDeps != NULL)
    {
        /* The grammar of the file is:
         *      ImportDeclaration
         *          ::= BasicImportDeclaration [ " : " ImportBindList ] [ " -> "
         *      ModuleAliasIdentifier ] "\n"
         *
         *      BasicImportDeclaration
         *          ::= ModuleFullyQualifiedName " (" FilePath ") : " Protection
         *              " [ " static" ] : " ModuleFullyQualifiedName " (" FilePath ")"
         *
         *      FilePath
         *          - any string with '(', ')' and '\' escaped with the '\' character
         */

        OutBuffer *ob = global.params.moduleDeps;

        ob->writestring(sc->module->toPrettyChars());
        ob->writestring(" (");
        escapePath(ob, sc->module->srcfile->toChars());
        ob->writestring(") : ");

        ProtDeclaration::protectionToCBuffer(ob, sc->protection);
        if (isstatic)
            StorageClassDeclaration::stcToCBuffer(ob, STCstatic);
        ob->writestring(": ");

        if (packages)
        {
            for (size_t i = 0; i < packages->dim; i++)
            {
                Identifier *pid = (Identifier *)packages->data[i];
                ob->printf("%s.", pid->toChars());
            }
        }

        ob->writestring(id->toChars());
        ob->writestring(" (");
        if (mod)
            escapePath(ob, mod->srcfile->toChars());
        else
            ob->writestring("???");
        ob->writebyte(')');

        for (size_t i = 0; i < names.dim; i++)
        {
            if (i == 0)
                ob->writebyte(':');
            else
                ob->writebyte(',');

            Identifier *name = (Identifier *)names.data[i];
            Identifier *alias = (Identifier *)aliases.data[i];

            if (!alias)
            {
                ob->printf("%s", name->toChars());
                alias = name;
            }
            else
                ob->printf("%s=%s", alias->toChars(), name->toChars());
        }

        if (aliasId)
                ob->printf(" -> %s", aliasId->toChars());

        ob->writenl();
    }

    //printf("-Import::semantic('%s'), pkg = %p\n", toChars(), pkg);
}