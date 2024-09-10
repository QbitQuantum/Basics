void Notepad::showNotepadContextMenu(const QPoint &pt)
{
    // Set Notepad popup menu
    QMenu *menu = ui->notepadTextEdit->createStandardContextMenu();
    QTextCursor cur = ui->notepadTextEdit->textCursor();
    QAction* first = menu->actions().at(0);

    if (cur.hasSelection()) {
        // Get selected text
        //this->main->add_debug_output("Selected text: " + cur.selectedText());
        this->addr = cur.selectedText();
    } else {
        // Get word under the cursor
        cur.select( QTextCursor::WordUnderCursor);
        //this->main->add_debug_output("Word: " + cur.selectedText());
        this->addr = cur.selectedText();
    }
    ui->actionDisassmble_bytes->setText( "Disassemble bytes at: " + this->addr);
    ui->actionDisassmble_function->setText( "Disassemble function at: " + this->addr);
    ui->actionHexdump_bytes->setText( "Hexdump bytes at: " + this->addr);
    ui->actionCompact_Hexdump->setText( "Compact Hexdump at: " + this->addr);
    ui->actionHexdump_function->setText( "Hexdump function at: " + this->addr);
    menu->insertAction(first, ui->actionDisassmble_bytes);
    menu->insertAction(first, ui->actionDisassmble_function);
    menu->insertAction(first, ui->actionHexdump_bytes);
    menu->insertAction(first, ui->actionCompact_Hexdump);
    menu->insertAction(first, ui->actionHexdump_function);
    menu->insertSeparator(first);
    ui->notepadTextEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
    menu->exec(ui->notepadTextEdit->mapToGlobal(pt));
    delete menu;
    ui->notepadTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);
}