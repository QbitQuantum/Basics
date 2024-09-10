    bool CheckString(CatalogItemPtr item, const wxString& source, const wxString& translation) override
    {
        const UChar32 s_last = source.Last();
        const UChar32 t_last = translation.Last();
        const bool s_punct = u_ispunct(s_last);
        const bool t_punct = u_ispunct(t_last);

        if (u_getIntPropertyValue(s_last, UCHAR_BIDI_PAIRED_BRACKET_TYPE) == U_BPT_CLOSE ||
            u_getIntPropertyValue(t_last, UCHAR_BIDI_PAIRED_BRACKET_TYPE) == U_BPT_CLOSE)
        {
            // too many reordering related false positives for brackets
            // e.g. "your {site} account" -> "váš účet na {site}"
            if ((wchar_t)u_getBidiPairedBracket(s_last) != (wchar_t)source[0])
            {
                return false;
            }
            else
            {
                // OTOH, it's desirable to check strings fully enclosed in brackets like "(unsaved)"
                if (source.find_first_of((wchar_t)s_last, 1) != source.size() - 1)
                {
                    // it's more complicated, possibly something like "your {foo} on {bar}"
                    return false;
                }
            }
        }

        if (u_hasBinaryProperty(s_last, UCHAR_QUOTATION_MARK) || (!s_punct && u_hasBinaryProperty(t_last, UCHAR_QUOTATION_MARK)))
        {
            // quoted fragments can move around, e.g., so ignore quotes in reporting:
            //      >> Invalid value for ‘{fieldName}’​ field
            //      >> Valor inválido para el campo ‘{fieldName}’
            // TODO: count quote characters to check if used correctly in translation; don't check position
            return false;
        }

        if (s_punct && !t_punct)
        {
            item->SetIssue(CatalogItem::Issue::Warning,
                           wxString::Format(_(L"The translation should end with “%s”."), wxString(wxUniChar(s_last))));
            return true;
        }
        else if (!s_punct && t_punct)
        {
            item->SetIssue(CatalogItem::Issue::Warning,
                           wxString::Format(_(L"The translation should not end with “%s”."), wxString(wxUniChar(t_last))));
            return true;
        }
        else if (s_punct && t_punct && s_last != t_last)
        {
            if (t_last == L'…' && source.EndsWith("..."))
            {
                // as a special case, allow translating ... (3 dots) as … (ellipsis)
            }
            else if (u_hasBinaryProperty(s_last, UCHAR_QUOTATION_MARK) && u_hasBinaryProperty(t_last, UCHAR_QUOTATION_MARK))
            {
                // don't check for correct quotes for now, accept any quotations marks as equal
            }
            else if (IsEquivalent(s_last, t_last))
            {
                // some characters are mostly equivalent and we shouldn't warn about them
            }
            else
            {
                item->SetIssue(CatalogItem::Issue::Warning,
                               wxString::Format(_(L"The translation ends with “%s”, but the source text ends with “%s”."),
                                                wxString(wxUniChar(t_last)), wxString(wxUniChar(s_last))));
                return true;
            }
        }

        return false;
    }