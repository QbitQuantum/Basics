void DlgInputDialogImp::setType( DlgInputDialogImp::Type t )
{
    inputtype = t;

    QWidget *input = 0;
    switch (inputtype)
    {
    case LineEdit:
        input = lineEdit;
        break;
    case SpinBox:
        input = spinBox;
        break;
    case UIntBox:
        input = uIntSpinBox;
        break;
    case FloatSpinBox:
        input = floatSpinBox;
        break;
    case ComboBox:
        input = comboBox;
        break;
    default:
        break;
    }

    if (input) {
        stack->setCurrentWidget(input->parentWidget());
        stack->setFixedHeight( input->sizeHint().height() );
        input->setFocus();
        label->setBuddy( input );
    }
}