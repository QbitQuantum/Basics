bool QtKCaptureBuffer::present(const QVideoFrame &frame)
//qtmultimedia\src\plugins\directshow\camera\dscamerasession.cpp
{
	static int cnt = 0;		
	if(!this->m_doCapture) return false;
	
	m_mutexA.lock();
	QVideoFrame tFrame = frame;	
    if(tFrame.map(QAbstractVideoBuffer::ReadOnly))
    {	
		this->m_doCapture = false;
		if(this->m_widthScale == 0) this->m_widthScale = frame.width();
		switch(this->m_mirrorSetting)
		{
			case mirrorVertical:
				this->m_lastFrame = QImage(frame.bits(), frame.width(), frame.height(), frame.bytesPerLine(), getQImageFormat(tFrame.pixelFormat())).mirrored(0, 1).scaledToWidth(this->m_widthScale, (Qt::TransformationMode)this->m_scaleMode);
				break;

			case mirrorHorizontal:
				this->m_lastFrame = QImage(frame.bits(), frame.width(), frame.height(), frame.bytesPerLine(), getQImageFormat(tFrame.pixelFormat())).mirrored(1, 0).scaledToWidth(this->m_widthScale, (Qt::TransformationMode)this->m_scaleMode);
				break;

			case mirrorAll:
				this->m_lastFrame = QImage(frame.bits(), frame.width(), frame.height(), frame.bytesPerLine(), getQImageFormat(tFrame.pixelFormat())).mirrored(1, 1).scaledToWidth(this->m_widthScale, (Qt::TransformationMode)this->m_scaleMode);
				break;

			case mirrorNone:			
			default:
			this->m_lastFrame = QImage(frame.bits(), frame.width(), frame.height(), frame.bytesPerLine(), getQImageFormat(tFrame.pixelFormat())).scaledToWidth(this->m_widthScale, (Qt::TransformationMode)this->m_scaleMode);
			break;
		}
		
        tFrame.unmap();
		m_mutexA.unlock();	
		
		emit imageCaptured(cnt++, this->m_lastFrame);				
		return true;

	}
	m_mutexA.unlock();
    return false;
}