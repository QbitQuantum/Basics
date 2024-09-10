Inst ExtManager::parseExtInstMnemo(Scanner& scanner, Brigantine& bw, int* vx) const
{
    assert(scanner.peek().kind() == EExtInstName);

    // Parse mnemo prefix adding suffices until there is an extension which can handle it.
    // This prefix has the form <vendor>_<extension>

    string prefix = scanner.scan().text();
    while (!isMnemoPrefix(prefix) && scanner.peek().kind() == EExtInstSuff) 
    {
        prefix += scanner.scan().text();
    }

    // Parse remaining part of instruction mnemo (typically in the form <opcode>_<suff>)

    if (const Extension* e = getByPrefix(prefix)) return e->parseInstMnemo(prefix, scanner, bw, vx);

    // Enabled extensions failed to parse this mnemo.
    // Search for a disabled extension which might have handled it
    const char* s = 0;
    for (unsigned i = 0; i < size(); ++i)
    {
        if (!isEnabled[i] && (s = extension[i]->matchInstMnemo(prefix)) != 0)
        {
            scanner.syntaxError(string("Instruction \"") + s + "\" cannot be used (extension \"" + extension[i]->getName() + "\" is not enabled)");
            return Inst();
        }
    }

    // Extensions (including disabled) cannot handle this mnemo

    if (!hasEnabled()) scanner.scan(); // show offending token
    scanner.syntaxError("Undefined instruction");

    return Inst();
}