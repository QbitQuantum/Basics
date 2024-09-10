bool ViewProviderThickness::setEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default ) {
        Gui::TaskView::TaskDialog *dlg = Gui::Control().activeDialog();
        TaskThickness* thicknessDlg = qobject_cast<TaskThickness*>(dlg);
        if (thicknessDlg && thicknessDlg->getObject() != this->getObject())
            thicknessDlg = 0; // another pad left open its task panel
        if (dlg && !thicknessDlg) {
            if (dlg->canClose())
                Gui::Control().closeDialog();
            else
                return false;
        }

        // clear the selection (convenience)
        Gui::Selection().clearSelection();

        // start the edit dialog
        if (thicknessDlg)
            Gui::Control().showDialog(thicknessDlg);
        else
            Gui::Control().showDialog(new TaskThickness(static_cast<Part::Thickness*>(getObject())));

        return true;
    }
    else {
        return ViewProviderPart::setEdit(ModNum);
    }
}