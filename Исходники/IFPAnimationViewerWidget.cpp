void IFPAnimationViewerWidget::updateFrameDisplay()
{
	if (!displayedFrame)
		return;

	AnimationBone* bone = NULL;

	if (currentAnim)
		bone = currentAnim->getBoneForFrame(displayedFrame);

	renderWidget->setCurrentBone(displayedFrame->getName());
	renderWidget->updateDisplay();

	if (bone) {
		AnimationFrame* f1;
		AnimationFrame* f2;
		float t;

		bone->getFrames(currentTime, f1, f2, t);

		AnimationFrame* f = bone->getInterpolatedFrame(currentTime);

		ui.ipFactorLabel->setText(QString("%1").arg(t));

		Quaternion f1r = f1->getRotation();
		Vector3 f1t = f1->getTranslation();
		Vector3 f1s = f1->getScale();
		ui.f1RotationLabel->setText(tr("(%1, %2, %3, %4)")
				.arg(f1r.getW()).arg(f1r.getX()).arg(f1r.getY()).arg(f1r.getZ()));
		ui.f1TranslationLabel->setText(tr("(%1, %2, %3)")
				.arg(f1t.getX()).arg(f1t.getY()).arg(f1t.getZ()));
		ui.f1ScaleLabel->setText(tr("(%1, %2, %3)")
				.arg(f1s.getX()).arg(f1s.getY()).arg(f1s.getZ()));
		ui.f1TimeLabel->setText(QString("%1").arg(f1->getStart()));

		Quaternion f2r = f2->getRotation();
		Vector3 f2t = f2->getTranslation();
		Vector3 f2s = f2->getScale();
		ui.f2RotationLabel->setText(tr("(%1, %2, %3, %4)")
				.arg(f2r.getW()).arg(f2r.getX()).arg(f2r.getY()).arg(f2r.getZ()));
		ui.f2TranslationLabel->setText(tr("(%1, %2, %3)")
				.arg(f2t.getX()).arg(f2t.getY()).arg(f2t.getZ()));
		ui.f2ScaleLabel->setText(tr("(%1, %2, %3)")
				.arg(f2s.getX()).arg(f2s.getY()).arg(f2s.getZ()));
		ui.f2TimeLabel->setText(QString("%1").arg(f2->getStart()));

		Quaternion ifr = f->getRotation();
		Vector3 ift = f->getTranslation();
		Vector3 ifs = f->getScale();
		ui.ipRotationLabel->setText(tr("(%1, %2, %3, %4)")
				.arg(ifr.getW()).arg(ifr.getX()).arg(ifr.getY()).arg(ifr.getZ()));
		ui.ipTranslationLabel->setText(tr("(%1, %2, %3)")
				.arg(ift.getX()).arg(ift.getY()).arg(ift.getZ()));
		ui.ipScaleLabel->setText(tr("(%1, %2, %3)")
				.arg(ifs.getX()).arg(ifs.getY()).arg(ifs.getZ()));
		ui.ipTimeLabel->setText(QString("%1").arg(f->getStart()));
	} else {
		ui.ipFactorLabel->setText(tr("-"));

		ui.f1RotationLabel->setText(tr("-"));
		ui.f1TranslationLabel->setText(tr("-"));
		ui.f1ScaleLabel->setText(tr("-"));
		ui.f1TimeLabel->setText(tr("-"));

		ui.f2RotationLabel->setText(tr("-"));
		ui.f2TranslationLabel->setText(tr("-"));
		ui.f2ScaleLabel->setText(tr("-"));
		ui.f2TimeLabel->setText(tr("-"));

		ui.ipRotationLabel->setText(tr("-"));
		ui.ipTranslationLabel->setText(tr("-"));
		ui.ipScaleLabel->setText(tr("-"));
		ui.ipTimeLabel->setText(tr("-"));
	}
}