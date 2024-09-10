void SimpleWithRectangleLabel::editLabel() {
    setFocus();
    label_->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    label_->setTextInteractionFlags(Qt::TextEditorInteraction);
    label_->setFocus();
}