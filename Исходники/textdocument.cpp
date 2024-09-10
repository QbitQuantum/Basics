TextDocument::TextDocument(Id id)
    : d(new TextDocumentPrivate)
{
    connect(&d->m_document, &QTextDocument::modificationChanged,
            this, &TextDocument::modificationChanged);
    connect(&d->m_document, &QTextDocument::contentsChanged,
            this, &Core::IDocument::contentsChanged);
    connect(&d->m_document, &QTextDocument::contentsChange,
            this, &TextDocument::contentsChangedWithPosition);

    // set new document layout
    QTextOption opt = d->m_document.defaultTextOption();
    opt.setTextDirection(Qt::LeftToRight);
    opt.setFlags(opt.flags() | QTextOption::IncludeTrailingSpaces
            | QTextOption::AddSpaceForLineAndParagraphSeparators
            );
    d->m_document.setDefaultTextOption(opt);
    d->m_document.setDocumentLayout(new TextDocumentLayout(&d->m_document));

    if (id.isValid())
        setId(id);

    setSuspendAllowed(true);
}