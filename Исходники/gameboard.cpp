void GameBoard::Menu()
{
    QDialog *menu = new QDialog;
    QLabel *texto = new QLabel;
    QLabel *title = new QLabel("<b><big>Atalhos</big></b>");

    QFile *config = new QFile("/home/vinicius/svn/unball/estrategia/visualization/Visualization Last Version/Visualization_last/Tabela.txt"); //Colocar o diretório ao qual se encontra o arquivo Tabela.txt

    if(!config->open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream mOut(config);
    QString mTexto = mOut.readAll();


    texto->setText(mTexto);

    QVBoxLayout *lay =new QVBoxLayout;
    lay->addWidget(title);
    lay->addWidget(texto);

    menu->setLayout(lay);
    menu->show();

    config->flush();
    mOut.flush();
    config->close();

}