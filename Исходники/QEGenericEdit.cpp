//------------------------------------------------------------------------------
// The user has 'finished editing' such as pressed return/enter or moved
// focus from the object.
// Note, it doesn't matter if the user presses return and both this function
// AND userReturnPressed() is called since setText is called in each to clear
// the 'isModified' flag. So, the first called will perform the write, the
// second (if any) will do nothing.
//
void QEGenericEdit::userEditingFinished()
{
    // If not connected, do nothing
    if( !isConnected )
    {
        return;
    }

    // Do nothing if the user is still effectivly working with the widget (just moved to a dialog box)
    // Any signals received while messageDialogPresent is true should be ignored.
    // A signal occurs after the 'write failed' dialog closes, so a it sets
    // writeFailMessageDialogPresent to allow this code to ignore the signal.
    if( messageDialogPresent || writeFailMessageDialogPresent )
    {
        if( !messageDialogPresent )
        {
            writeFailMessageDialogPresent = false;
            setFocus();
        }
        return;
    }

    // If no changes were made by the user, do nothing
    if( !isModified() || !writeOnFinish )
    {
        return;
    }

    // Get the variable to write to
    qcaobject::QCaObject *qca = getQcaItem(0);

    // If a QCa object is present (if there is a variable to write to)
    // and the object is set up to write when the user changes focus away from the object
    // and the text has actually changed
    // then write the value
    if( qca && writeOnLoseFocus )
    {
       // Note: getValue is a dispatching hook procedure.
       writeValue( qca, getValue () );
    }

    // If, for what ever reason, the value has been changed by the user but not but not written
    // check with the user what to do about it.
    else
    {
        messageDialogPresent = true;
        int confirm = QMessageBox::warning( this, "Value changed", "You altered a value but didn't write it.\nDo you want to write this value?",
                                            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::No );
        messageDialogPresent = false;

        switch( confirm )
        {
            // Write the value
            case QMessageBox::Yes:
                if( qca ) {
                   // Note: getValue is a dispatching hook procedure.
                   writeValue( qca, getValue () );
                }
                break;

            // Abort the write, revert to latest value
            case QMessageBox::No:
                setValue( lastValue );       // Note, also clears 'isModified' flag
                                             // setValue  is dispatching hook function
                break;

            // Don't write the value, move back to the field being edited
            case QMessageBox::Cancel:
                setFocus();
                break;
        }
    }
}