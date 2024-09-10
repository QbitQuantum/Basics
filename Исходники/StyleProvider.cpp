Style StyleProvider::forElement(const Element& element, int levelOfDetails) const
{
    StyleBuilder builder(pimpl_->stringTable, pimpl_->filters, levelOfDetails);
    element.accept(builder);
    return std::move(builder.build());
}