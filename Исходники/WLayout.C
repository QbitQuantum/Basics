void WLayout::setParentWidget(WWidget *parent)
{
  if (!this->parent())
    setParent(parent);

  assert(!impl_);

  int c = count();
  for (int i = 0; i < c; ++i) {
    WLayoutItem *item = itemAt(i);
    if (item)
      item->setParentWidget(parent);
  }

  impl_ = parent->createLayoutItemImpl(this);

  if (hints_) {
    for (unsigned i = 0; i < hints_->size(); ++i)
      impl_->setHint((*hints_)[i].name, (*hints_)[i].value);
    delete hints_;
    hints_ = 0;
  }
}