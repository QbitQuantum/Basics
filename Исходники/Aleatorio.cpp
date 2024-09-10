void Aleatorio::DeleteIndex(){

    QFile file; //borramos los ficheros
    file.setFileName(Path + "/index.dat");
    file.remove();
    file.setFileName(Path + "/radit.txt");
    file.remove();
    file.close();

 }