void SketcherValidation::on_delConstrExtr_clicked()
{
    int reply;
    reply =  QMessageBox::question(this,
                        tr("Delete constraints to external geom."),
                        tr("You are about to delete ALL constraints that deal with external geometry. This is useful to rescue a sketch with broken/changed links to external geometry. Are you sure you want to delete the constraints?"),
                        QMessageBox::No|QMessageBox::Yes,QMessageBox::No);
    if(reply!=QMessageBox::Yes) return;

    App::Document* doc = sketch->getDocument();
    doc->openTransaction("Delete constraints");

    sketch->delConstraintsToExternal();

    doc->commitTransaction();

    QMessageBox::warning(this, tr("Delete constraints to external geom."),
                         tr("All constraints that deal with external geometry were deleted."));
}