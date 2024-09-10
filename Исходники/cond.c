// Helper for printing dependency information
void printDepsConditional(Scope *sc, DVCondition* condition, const char* depType)
{
    if (!global.params.moduleDeps || global.params.moduleDepsFile)
        return;
    OutBuffer *ob = global.params.moduleDeps;
    Module* imod = sc ? (sc->instantiatingModule ? sc->instantiatingModule : sc->module) : condition->mod;
    if (!imod)
        return;
    ob->writestring(depType);
    ob->writestring(imod->toPrettyChars());
    ob->writestring(" (");
    escapePath(ob, imod->srcfile->toChars());
    ob->writestring(") : ");
    if (condition->ident)
        ob->printf("%s\n", condition->ident->toChars());
    else
        ob->printf("%d\n", condition->level);
}