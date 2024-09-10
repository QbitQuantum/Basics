void CImage::free() {
  assert(this);
  if (!(screenLayers->game.hasBeenRefreshed))
    scbw::refreshScreen(this->screenPosition.x,
                        this->screenPosition.y,
                        this->screenPosition.x + this->grpSize.right,
                        this->screenPosition.y + this->grpSize.bottom
                        );

  CSprite* const parent = this->parentSprite;
  const CListExtern<CImage, &CImage::link>
    imageList(parent->imageHead, parent->imageTail);

  imageList.unlink(this);
  this->grpOffset = NULL;

  unusedImages.insertAfterHead(this);
}