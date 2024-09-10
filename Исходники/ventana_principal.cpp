void Ventana_Principal::on_bt_buscar_3_clicked()
{
    Pestana *actual = (Pestana*)ui->tabWidget->currentWidget();

    if(actual != NULL){

        QTextEdit *editor = actual->textedit();

        int fw1 = editor->fontWeight();
        QColor gris1 = QColor("red");
        editor->setFontWeight(QFont::DemiBold);
        editor->setTextColor(QColor(gris1));
        editor->insertPlainText("hola");
        editor->setFontWeight(fw1);
        editor->setTextColor(gris1);
    }
    //this->AnalisisJSLT();

}