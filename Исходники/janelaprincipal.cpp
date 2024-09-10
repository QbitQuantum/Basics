void janelaPrincipal::copiarAquivos(QFile &origem, QFile &destino)
{

    qint64 nCopySize = origem.size();
    ui->progressBarGeral->setMaximum(nCopySize);
    if(!(origem.open(QFile::ReadOnly) && destino.open(QFile::ReadWrite))){
        return;
    }


  qDebug() << QString::number(nCopySize)+" o tamanho do arquivo";
  //dialog->show();

     for (qint64 i = 0; i < nCopySize; i += 1024*1024) {
         if(iscopy){
         destino.write(origem.read(i)); // write a byte
         destino.seek(i);  // move to next byte to read
         origem.seek(i); // move to next byte to write
         ui->progressBarGeral->setValue(i);
    }else {
             destino.remove();
             break;
         }

         // ui->progressBarGeral->;
     }
     ui->progressBarGeral->setVisible(false);
     ui->progressBarGeral->setValue(0);
      modeldir->refresh();
}