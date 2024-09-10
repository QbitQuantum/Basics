bool KGameMouseIO::eventFilter( QObject *o, QEvent *e )
{
  if (!player())
  {
    return false;
  }
  //qCDebug(GAMES_PRIVATE_KGAME) << "KGameMouseIO" << this << QLatin1String( " " ) << e->type();

  // mouse action
  if ( e->type() == QEvent::MouseButtonPress ||
       e->type() == QEvent::MouseButtonRelease ||
       e->type() == QEvent::MouseButtonDblClick ||
       e->type() == QEvent::Wheel ||
       e->type() == QEvent::MouseMove ||
       e->type() == QEvent::GraphicsSceneMousePress ||
       e->type() == QEvent::GraphicsSceneMouseRelease ||
       e->type() == QEvent::GraphicsSceneMouseDoubleClick ||
       e->type() == QEvent::GraphicsSceneWheel ||
       e->type() == QEvent::GraphicsSceneMouseMove
       )
  {
     QMouseEvent *k = (QMouseEvent*)e;
     // qCDebug(GAMES_PRIVATE_KGAME) << "KGameMouseIO" << this;
     QByteArray buffer;
     QDataStream stream(&buffer,QIODevice::WriteOnly);
     bool eatevent=false;
     emit signalMouseEvent(this,stream,k,&eatevent);
//     qCDebug(GAMES_PRIVATE_KGAME) << "################# eatevent=" << eatevent;
     QDataStream msg(buffer);
     if (eatevent && sendInput(msg))
     {
       return eatevent;
     }
     return false; // do not eat otherwise
  }
  return QObject::eventFilter( o, e );    // standard event processing
}