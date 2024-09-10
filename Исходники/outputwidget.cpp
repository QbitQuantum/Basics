void OutputWidget::eventuallyDoFocus()
{
    QWidget* widget = currentWidget();
    if( focusOnSelect->isChecked() && !widget->hasFocus() ) {
        widget->setFocus( Qt::OtherFocusReason );
    }
}