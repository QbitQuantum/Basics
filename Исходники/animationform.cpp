// ドロップ時のスロット
// レイヤ追加
void AnimationForm::slot_dropedImage( QRectF rect, QPoint pos, int imageIndex )
{
	CObjectModel *pModel = m_pEditData->getObjectModel() ;
	int frameNum  = ui->label_frame->value() ;
	QModelIndex index = ui->treeView->currentIndex() ;

	if ( !index.isValid() ) {
		qWarning() << "slot_dropedImage current index invalid 0" ;
		return ;
	}

	ObjectItem *pObjItem = pModel->getObject(index) ;
	if ( !pObjItem ) {
		qWarning() << "slot_dropedImage current obj 0" ;
		return ;
	}

	if ( !m_pSetting->getLayerHierarchy() ) {
		index = pObjItem->getIndex() ;
	}

	pos -= QPoint((m_pSetting->getAnmWindowW()/2), (m_pSetting->getAnmWindowH()/2)) ;	// GLWidgetのローカルポスに変換

	ObjectItem *pItem = pModel->getItemFromIndex(index) ;
	bool valid ;
	QMatrix4x4 mat = pItem->getDisplayMatrix(frameNum, &valid) ;
	if ( valid ) {
		QMatrix4x4 inv = mat.inverted(&valid) ;
		if ( valid ) {
			pos = inv.map(pos) ;
		}
	}

	index = m_pEditData->cmd_addItem(QString("Layer %1").arg(pObjItem->childCount()), index) ;
	ui->treeView->setCurrentIndex(index) ;
//	m_pEditData->setSelIndex(index) ;

	// ツリービューに追加
    FrameData frameData ;
	frameData.pos_x = pos.x() ;
	frameData.pos_y = pos.y() ;
	frameData.pos_z = 0 ;
	frameData.rot_x =
	frameData.rot_y =
	frameData.rot_z = 0 ;
	frameData.center_x = (rect.width()) / 2 ;
	frameData.center_y = (rect.height()) / 2 ;
	frameData.frame = frameNum ;
	frameData.fScaleX = frameData.fScaleY = 1.0f ;
	frameData.setRect(rect);
	frameData.nImage = imageIndex ;
	frameData.bUVAnime = false ;
	frameData.rgba[0] =
	frameData.rgba[1] =
	frameData.rgba[2] =
	frameData.rgba[3] = 255 ;

	QList<QWidget *> updateWidget ;
	updateWidget << m_pGlWidget ;
	updateWidget << m_pDataMarker ;

	m_pEditData->cmd_addFrameData(index, frameData, updateWidget) ;
}