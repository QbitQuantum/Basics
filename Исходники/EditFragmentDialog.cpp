void EditFragmentDialog::accept()
{
    QByteArray lTermType = lBluntButton->isChecked() ? OVERHANG_TYPE_BLUNT : OVERHANG_TYPE_STICKY;
    dnaFragment.setLeftTermType(lTermType);

    QByteArray rTermType = rBluntButton->isChecked() ? OVERHANG_TYPE_BLUNT : OVERHANG_TYPE_STICKY;
    dnaFragment.setRightTermType(rTermType);

    if (lCustomOverhangBox->isChecked() && lStickyButton->isChecked()) {
        QLineEdit* lCustomOverhangEdit = lDirectRadioButton->isChecked() ? lDirectOverhangEdit : lComplOverhangEdit;
        QString leftOverhang = lCustomOverhangEdit->text();

        if (leftOverhang.isEmpty()) {
            QMessageBox::warning(this, windowTitle(), tr("Left overhang is empty. Please enter the overhang or set blunt left end."));
            return;
        }
        if (!isValidOverhang(leftOverhang)) {
            QMessageBox::warning(this, windowTitle(), tr("Invalid left overhang: unsupported alphabet!"));
            lCustomOverhangEdit->setFocus();
            lCustomOverhangEdit->setSelection(0, leftOverhang.length());
            return;
        }

        QByteArray bLeftOverhang = leftOverhang.toUpper().toLatin1();
        if ( lComplRadioButton->isChecked() ) {
            transl->translate(bLeftOverhang.data(), bLeftOverhang.size());
        }
        dnaFragment.setLeftOverhang(bLeftOverhang);
        dnaFragment.setLeftOverhangStrand(lDirectRadioButton->isChecked());

    }

    if (rCustomOverhangBox->isChecked() && rStickyButton->isChecked()) {
        QLineEdit* rCustomOverhangEdit = rDirectRadioButton->isChecked() ? rDirectOverhangEdit : rComplOverhangEdit;
        QString rightOverhang = rCustomOverhangEdit->text();

        if (rightOverhang.isEmpty()) {
            QMessageBox::warning(this, windowTitle(), tr("Right overhang is empty. Please enter the overhang or set blunt right end."));
            return;
        }
        if (!isValidOverhang(rightOverhang)) {
            QMessageBox::warning(this, windowTitle(), tr("Invalid right overhang: unsupported alphabet!"));
            rCustomOverhangEdit->setFocus();
            rCustomOverhangEdit->setSelection(0, rightOverhang.length());
            return;
        }

        QByteArray bRightOverhang = rightOverhang.toUpper().toLatin1();
        if ( rComplRadioButton->isChecked() ) {
            transl->translate(bRightOverhang.data(), bRightOverhang.size());
        }
        dnaFragment.setRightOverhang(bRightOverhang);
        dnaFragment.setRightOverhangStrand(rDirectRadioButton->isChecked());
    }

    QDialog::accept();

}