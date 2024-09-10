    virtual void report(int level,
                        const char * /*fileId*/,
                        unsigned line, unsigned column, unsigned length,
                        const char *format, va_list ap)
    {
        if (level == Error) {
            ++errorCount;

            if (errorCount >= MAX_MESSAGE_COUNT)
                return; // ignore the error
        }

        QString message;
        message.vsprintf(format, ap);

        GoSource::DiagnosticMessage m(convertLevel(level), doc->fileName(),
                                      line, column, message, length);
        messages->append(m);
    }