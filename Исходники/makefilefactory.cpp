bool MakefileFactory::apply(const QStringList& commandLineArguments, Options **outopt)
{
    if (m_makefile)
        clear();

    Options *options = new Options;
    if (outopt)
        *outopt = options;
    MacroTable *macroTable = new MacroTable;
    macroTable->setEnvironment(m_environment);

    QString filename;
    if (!options->readCommandLineArguments(commandLineArguments, filename, m_activeTargets, *macroTable)) {
        m_errorType = CommandLineError;
        return false;
    }
    if (options->showUsageAndExit || options->showVersionAndExit)
        return true;

    if (!options->stderrFile.isEmpty()) {
        // Try to open the file for writing.
        const wchar_t *wszFileName = reinterpret_cast<const wchar_t*>(options->stderrFile.utf16());
        FILE *f = _wfopen(wszFileName, L"w");
        if (!f) {
            m_errorString = QLatin1String("Cannot open stderr file for writing.");
            m_errorType = IOError;
            return false;
        }
        fclose(f);
        if (!_wfreopen(wszFileName, L"w", stderr)) {
            m_errorString = QLatin1String("Cannot reopen stderr handle for writing.");
            m_errorType = IOError;
            return false;
        }
    }

    options->fullAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());

    readEnvironment(m_environment, macroTable, options->overrideEnvVarMacros);
    if (!options->ignorePredefinedRulesAndMacros) {
        macroTable->setMacroValue("MAKE", encloseInDoubleQuotesIfNeeded(options->fullAppPath));
        macroTable->setMacroValue("MAKEDIR", encloseInDoubleQuotesIfNeeded(QDir::currentPath()));
        macroTable->setMacroValue("AS", "ml");       // Macro Assembler
        macroTable->setMacroValue("ASFLAGS", QString());
        macroTable->setMacroValue("BC", "bc");       // Basic Compiler
        macroTable->setMacroValue("BCFLAGS", QString());
        macroTable->setMacroValue("CC", "cl");       // C Compiler
        macroTable->setMacroValue("CCFLAGS", QString());
        macroTable->setMacroValue("COBOL", "cobol"); // COBOL Compiler
        macroTable->setMacroValue("COBOLFLAGS", QString());
        macroTable->setMacroValue("CPP", "cl");      // C++ Compiler
        macroTable->setMacroValue("CPPFLAGS", QString());
        macroTable->setMacroValue("CXX", "cl");      // C++ Compiler
        macroTable->setMacroValue("CXXFLAGS", QString());
        macroTable->setMacroValue("FOR", "fl");      // FORTRAN Compiler
        macroTable->setMacroValue("FORFLAGS", QString());
        macroTable->setMacroValue("PASCAL", "pl");   // Pascal Compiler
        macroTable->setMacroValue("PASCALFLAGS", QString());
        macroTable->setMacroValue("RC", "rc");       // Resource Compiler
        macroTable->setMacroValue("RCFLAGS", QString());
    }

    try {
        m_makefile = new Makefile(filename);
        m_makefile->setOptions(options);
        m_makefile->setMacroTable(macroTable);
        Preprocessor preprocessor;
        preprocessor.setMacroTable(macroTable);
        preprocessor.openFile(filename);
        Parser parser;
        parser.apply(&preprocessor, m_makefile, m_activeTargets);
    } catch (Exception &e) {
        m_errorType = ParserError;
        m_errorString = e.toString();
    }

    return m_errorType == NoError;
}