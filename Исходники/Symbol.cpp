void
Symbol::dump(js::GenericPrinter& out)
{
    if (isWellKnownSymbol()) {
        // All the well-known symbol names are ASCII.
        description_->dumpCharsNoNewline(out);
    } else if (code_ == SymbolCode::InSymbolRegistry || code_ == SymbolCode::UniqueSymbol) {
        out.printf(code_ == SymbolCode::InSymbolRegistry ? "Symbol.for(" : "Symbol(");

        if (description_)
            description_->dumpCharsNoNewline(out);
        else
            out.printf("undefined");

        out.putChar(')');

        if (code_ == SymbolCode::UniqueSymbol)
            out.printf("@%p", (void*) this);
    } else {
        out.printf("<Invalid Symbol code=%u>", unsigned(code_));
    }
}