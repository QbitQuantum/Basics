void DropShadower::updateShadows()
{
    if (reentrant || owner == nullptr)
        return;

    ComponentPeer* const peer = owner->getPeer();
    const bool isOwnerVisible = owner->isVisible() && (peer == nullptr || ! peer->isMinimised());

    const bool createShadowWindows  = shadowWindows.size() == 0
                                         && owner->getWidth() > 0
                                         && owner->getHeight() > 0
                                         && isOwnerVisible
                                         && (Desktop::canUseSemiTransparentWindows()
                                              || owner->getParentComponent() != nullptr);

    {
        const ScopedValueSetter<bool> setter (reentrant, true, false);

        const int shadowEdge = jmax (xOffset, yOffset) + (int) blurRadius;

        if (createShadowWindows)
        {
            // keep a cached version of the image to save doing the gaussian too often
            String imageId;
            imageId << shadowEdge << ',' << xOffset << ',' << yOffset << ',' << alpha;

            const int hash = imageId.hashCode();

            Image bigIm (ImageCache::getFromHashCode (hash));

            if (bigIm.isNull())
            {
                bigIm = Image (Image::ARGB, shadowEdge * 5, shadowEdge * 5, true);

                Graphics bigG (bigIm);
                bigG.setColour (Colours::black.withAlpha (alpha));
                bigG.fillRect (shadowEdge + xOffset,
                               shadowEdge + yOffset,
                               bigIm.getWidth() - (shadowEdge * 2),
                               bigIm.getHeight() - (shadowEdge * 2));

                ImageConvolutionKernel blurKernel (roundToInt (blurRadius * 2.0f));
                blurKernel.createGaussianBlur (blurRadius);

                blurKernel.applyToImage (bigIm, bigIm,
                                         Rectangle<int> (xOffset, yOffset,
                                                         bigIm.getWidth(), bigIm.getHeight()));

                ImageCache::addImageToCache (bigIm, hash);
            }

            const int iw = bigIm.getWidth();
            const int ih = bigIm.getHeight();
            const int shadowEdge2 = shadowEdge * 2;

            setShadowImage (bigIm, 0, shadowEdge, shadowEdge2, 0, 0);
            setShadowImage (bigIm, 1, shadowEdge, shadowEdge2, 0, ih - shadowEdge2);
            setShadowImage (bigIm, 2, shadowEdge, shadowEdge, 0, shadowEdge2);
            setShadowImage (bigIm, 3, shadowEdge, shadowEdge2, iw - shadowEdge, 0);
            setShadowImage (bigIm, 4, shadowEdge, shadowEdge2, iw - shadowEdge, ih - shadowEdge2);
            setShadowImage (bigIm, 5, shadowEdge, shadowEdge, iw - shadowEdge, shadowEdge2);
            setShadowImage (bigIm, 6, shadowEdge, shadowEdge, shadowEdge, 0);
            setShadowImage (bigIm, 7, shadowEdge, shadowEdge, iw - shadowEdge2, 0);
            setShadowImage (bigIm, 8, shadowEdge, shadowEdge, shadowEdge2, 0);
            setShadowImage (bigIm, 9, shadowEdge, shadowEdge, shadowEdge, ih - shadowEdge);
            setShadowImage (bigIm, 10, shadowEdge, shadowEdge, iw - shadowEdge2, ih - shadowEdge);
            setShadowImage (bigIm, 11, shadowEdge, shadowEdge, shadowEdge2, ih - shadowEdge);

            for (int i = 0; i < 4; ++i)
                shadowWindows.add (new ShadowWindow (*owner, i, shadowImageSections));
        }

        if (shadowWindows.size() >= 4)
        {
            const int x = owner->getX();
            const int y = owner->getY() - shadowEdge;
            const int w = owner->getWidth();
            const int h = owner->getHeight() + shadowEdge + shadowEdge;

            for (int i = shadowWindows.size(); --i >= 0;)
            {
                // there seem to be rare situations where the dropshadower may be deleted by
                // callbacks during this loop, so use a weak ref to watch out for this..
                WeakReference<Component> sw (shadowWindows[i]);

                if (sw != nullptr)
                    sw->setAlwaysOnTop (owner->isAlwaysOnTop());

                if (sw != nullptr)
                    sw->setVisible (isOwnerVisible);

                if (sw != nullptr)
                {
                    switch (i)
                    {
                        case 0: sw->setBounds (x - shadowEdge, y, shadowEdge, h); break;
                        case 1: sw->setBounds (x + w, y, shadowEdge, h); break;
                        case 2: sw->setBounds (x, y, w, shadowEdge); break;
                        case 3: sw->setBounds (x, owner->getBottom(), w, shadowEdge); break;
                        default: break;
                    }
                }

                if (sw == nullptr)
                    return;
            }
        }
    }

    if (createShadowWindows)
        bringShadowWindowsToFront();
}