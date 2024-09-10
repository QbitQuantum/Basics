void CT08::QGetData( int ch, int num, QVector<double> &data )
{
  int cnt = 0;
  data.clear();

  //  QString cmd = QString( "GSCRDX?%1%2%3%4%5" )
  int Num = num;
  if ( num > 9999 ) {
    Num = ceil( ((double)Num) / 1000. );
  } else {
    Num -= 1;     // データ個数は Num 個、なので読み出し番地指定は 0〜Num-1
  }
    
  QString cmd = QString( "GSCRDXH?%1%2%3%4%5" )
    .arg( ch,     2, 10, QChar( '0' ) )     // 指定チャンネル (ch) から
    .arg( ch,     2, 10, QChar( '0' ) )     // 指定チャンネル (ch) までの、要は ch だけの
    .arg( (int)1, 2, 10, QChar( '0' ) )     // タイマーも読み出して(0:w/o, 1:w timer)
    .arg( (int)0, 4, 10, QChar( '0' ) )     // 0 番目から
    .arg( Num,    4, 10, QChar( '0' ) );    // num 番目までのデータを読みだす
  if ( num > 9999 )
    cmd += "K";
  SendACmd( cmd );

  bool Finished = false;
  QTime eTime;
  eTime.start();  // measure total time to elapsed in the following loop 
  while(( cnt < num )&&( !Finished )) {
    qDebug() << "waitForReadyRead" << ss->bytesAvailable() << cnt << num;
    // ここでデータがなるべく多く受信バッファに溜るのを待つ。
    int oldLen = 0, newLen;
    if ( ! ss->waitForReadyRead( 50 ) ) {
      if ( eTime.elapsed() > 1000 )
	Finished = true;
    }
    while( ( newLen = ss->bytesAvailable() ) != oldLen ) {
      oldLen = newLen;
      ss->waitForReadyRead( 50 );
    }
    
    double time0 = 0;
    double time = 0;
    qDebug() << "in QGetData : num = " << num;
    while( ! ss->atEnd() ) {
      QString Rbuf = ss->readLine().simplified();
      if ( Rbuf == "EOF" ) {
	Finished = true;
	qDebug() << "normally break by EOF";
	break;
      }
      QStringList vals = Rbuf.remove( ' ' ).split( ',' );
      if ( vals.count() == 2 ) {
	time = (double)vals[1].toInt( NULL, 16 ) / 1e6;
	if ( cnt < num ) {   // The number of data is 'num'
	  if ( time != time0 ) {
	    data << (double)vals[0].toInt( NULL, 16 ) / ( time - time0 );
	    time0 = time;
	  }
	}
	cnt++;
      }
    }
    qDebug() << "in QGetData : data.count() = " << data.count();
  }
  qDebug() << "-----------------------";
}