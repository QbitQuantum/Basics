bool DHudpEncoder::initClib(QString rawFn)
{
    qDebug() << "DHudpEncoder::initClib()";
     if ( preNC() == cTRUE ){
         qDebug() << "\t load: \"muldiv.tab\" succeeded.";
     }else{
         qDebug() << "\t load: \"muldiv.tab\" failed.";
         _fcloseall( );
     }

     //NC params
     i_cb = (NCCB *)malloc(sizeof(NCCB));
     if( i_cb == NULL){
         qDebug() << "\t malloc NCCB failed";
         exit(-1);
     }else {
         this->setRawFile(rawFn);
         this->setEncodedFile("Out.wmv");

         //init NC
         i_blockNum = this->getRawFileBlockNum();
         qDebug() << "\t raw file block num" << i_blockNum;

         if( cFALSE == initNC(i_cb,
                            i_rawFile.fileName().toAscii().data(),
                            i_blockSize,
                            i_blockNum,
                            i_d)){
             qDebug() << "\t initNC() failed";
             _fcloseall( );
         }
     }
     i_isInitOk = true;
     qDebug() << "\t initNC() ok";
     return true;
}