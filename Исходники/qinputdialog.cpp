void QInputDialog::setType( Type t )
{
    QWidget *input = 0;
    switch ( t ) {
    case LineEdit:
	input = d->lineEdit;
	break;
    case SpinBox:
	input = d->spinBox;
	break;
    case ComboBox:
	input = d->comboBox;
	break;
    case EditableComboBox:
	input = d->editComboBox;
	break;
    default:
#if defined(QT_CHECK_STATE)
	qWarning( "QInputDialog::setType: Invalid type" );
#endif
	break;
    }
    if ( input ) {
	d->stack->raiseWidget( input );
	d->stack->setFixedHeight( input->sizeHint().height() );
	input->setFocus();
#ifndef QT_NO_ACCEL
	d->label->setBuddy( input );
#endif
    }

    d->type = t;
}