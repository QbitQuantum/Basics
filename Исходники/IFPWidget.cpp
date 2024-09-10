void IFPWidget::displayFrame(int fnum)
{
	IFPAnimation* anim = anims[ui.animList->currentRow()];

	IFPAnimation::ObjectIterator it = anim->getObjectBegin();
	advance(it, ui.objList->currentRow());
	IFPObject* obj = *it;

	IFPObject::FrameIterator fit = obj->getFrameBegin();
	advance(fit, fnum);
	IFPRotFrame* frame = *fit;

	Quaternion rot = frame->getRotation();
	ui.frameRotLabel->setText(tr("%1, %2, %3, %4").arg(rot.getX()).arg(rot.getY()).arg(rot.getZ())
			.arg(rot.getW()));

	ui.frameTimeLabel->setText(QString("%1").arg(frame->getTime()));

	if (obj->getFrameType() == IFPObject::RotTransFrame) {
		IFPRotTransFrame* rtframe = (IFPRotTransFrame*) frame;
		Vector3 trans = rtframe->getTranslation();

		ui.frameTransLabel->setText(tr("%1, %2, %3").arg(trans.getX()).arg(trans.getY()).arg(trans.getZ()));
		ui.frameScaleLabel->setText(tr("-"));
	} else if (obj->getFrameType() == IFPObject::RotTransScaleFrame) {
		IFPRotTransScaleFrame* rtsframe = (IFPRotTransScaleFrame*) frame;
		Vector3 trans = rtsframe->getTranslation();
		Vector3 scale = rtsframe->getScale();

		ui.frameTransLabel->setText(tr("%1, %2, %3").arg(trans.getX()).arg(trans.getY()).arg(trans.getZ()));
		ui.frameScaleLabel->setText(tr("%1, %2, %3").arg(scale.getX()).arg(scale.getY()).arg(scale.getZ()));
	} else {
		ui.frameTransLabel->setText(tr("-"));
		ui.frameScaleLabel->setText(tr("-"));
	}
}