PassRefPtr<StringImpl> RenderTextFragment::originalText() const
{
    Node* e = node();
    RefPtr<StringImpl> result = ((e && e->isTextNode()) ? static_cast<Text*>(e)->dataImpl() : contentString());
    if (result && (start() > 0 || start() < result->length()))
        result = result->substring(start(), end());
    return result.release();
}