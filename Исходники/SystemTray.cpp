void SystemTray::updateToolTip()
{
//	return; /////////////////////////////////////////////////////

	Basket *basket = Global::bnpView->currentBasket();
	if (!basket)
		return;

	if (basket->icon().isEmpty() || basket->icon() == "basket" || ! Settings::showIconInSystray())
		setPixmap(basket->isLocked() ? m_lockedIconPixmap : m_iconPixmap);
	else {
		// Code that comes from JuK:
		QPixmap bgPix = loadIcon("basket");
		QPixmap fgPix = SmallIcon(basket->icon());

		QImage bgImage = bgPix.convertToImage(); // Probably 22x22
		QImage fgImage = fgPix.convertToImage(); // Should be 16x16
		QImage lockOverlayImage = loadIcon("lockoverlay").convertToImage();

		KIconEffect::semiTransparent(bgImage);
		copyImage(bgImage, fgImage, (bgImage.width() - fgImage.width()) / 2,
                  (bgImage.height() - fgImage.height()) / 2);
		if (basket->isLocked())
			KIconEffect::overlay(bgImage, lockOverlayImage);

		bgPix.convertFromImage(bgImage);
		setPixmap(bgPix);
	}

	//QTimer::singleShot( Container::c_delayTooltipTime, this, SLOT(updateToolTipDelayed()) );
	// No need to delay: it's be called when notes are changed:
	updateToolTipDelayed();
}