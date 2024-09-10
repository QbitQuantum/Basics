void MaterialAssignmentEditorWindow::append_row(
    QVBoxLayout*        parent,
    QLayout*            row_layout)
{
    QFrame* row = new QFrame();
    row->setProperty("hasFrame", true);
    row->setLayout(row_layout);
    parent->addWidget(row);
}