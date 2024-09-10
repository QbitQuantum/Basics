void QFormulatorEditWidget::mousePressEvent( QMouseEvent *e )
{
	if( e->button() == Qt::LeftButton )
	{
		PointFde ptf( e->x(), e->y() );
		RectFde rcf = clientRect();
		CFmlDrawEngineQt::DPtoLPEx( ptf, scale(), scale() );
		CFmlDrawEngineQt::DPtoLPEx( rcf, scale(), scale() );

		if( rootNode()->PtInSelection( rcf, ptf ) == 0 )
		{
			editCopy(); // to enable interoperating with Other Applications

			CFrameNode *pFrameNode = rootNode()->RemoveOrCopySelection( 0 );
			if( pFrameNode )
			{
				CRootNode *pRootNode = new CRootNode( this );
				// zero marginds when inserting from a server
				pRootNode->setIndents( 0, 0, 0, 0 );
				pRootNode->Insert( pFrameNode );
				QPixmap pixmap;
				if( ::isOption_Perfomance_CopyImage() )
					pixmap = drawSelection2QPixmap( true );
				QImage pixImg = pixmap.toImage();
				QMimeData *mimeData = CFormulatorDoc::copyToMimeData( pRootNode, pixmap.isNull() ? 0 : &pixImg );
				if( mimeData )
				{
					QDrag *drag = new QDrag( this );
					drag->setMimeData( mimeData );
					if( !pixmap.isNull() )
					{
						const int dragPixmapMaxSize = 256;
						if( qMax(pixmap.width(), pixmap.height()) > dragPixmapMaxSize )
							drag->setPixmap( pixmap.width() > pixmap.height() ? pixmap.scaledToWidth( dragPixmapMaxSize ) : pixmap.scaledToHeight( dragPixmapMaxSize ) );
						else
							drag->setPixmap( pixmap );
					}
					drag->setHotSpot( QPoint(0, 0) );

					clearRemovedSelection();
					Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::MoveAction);
					if( dropAction == Qt::MoveAction && isRemovedSelection() == 0 )
					{
						CFrameNode *pRemovedFrame = rootNode()->RemoveOrCopySelection( 1 );
						if( pRemovedFrame )
						{
							delete pRemovedFrame;
							setRemovedSelection();
						}
						if( !hasFocus() ) setFocus();
						updateViewDocument();
					}
				}

				delete pRootNode;
				delete pFrameNode;
			}
		}
		else if( rootNode()->MoveCaret( rcf, ptf, e->modifiers() & Qt::ShiftModifier ) == 0 )
		{
			updateFormulatorWidget();
		}

		//cbFireEvent( FORMULIB_CALLBACK_LMOUSECLICK, nFlags, MAKEWPARAM( point.x(), point.y() ) );
	}
	else if( e->button() == Qt::RightButton )
	{
		//cbFireEvent( FORMULIB_CALLBACK_RMOUSECLICK, nFlags, MAKEWPARAM( point.x(), point.y() ) );
	}
}