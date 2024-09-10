void CSprite::setPosition(u16 x, u16 y) {
	assert(this);
	if (this->position.x == x && this->position.y == y) return;

	const int oldTileY = CLAMP(this->position.y / 32, 0, mapTileSize->height - 1);
	const int newTileY = CLAMP(y / 32, 0, mapTileSize->height - 1);

	this->position.x = x;
	this->position.y = y;

	if (oldTileY != newTileY) {
		const CListExtern<CSprite, &CSprite::link>
			spritesOnOldTileRow(spritesOnTileRow->heads[oldTileY],
				spritesOnTileRow->tails[oldTileY]),
			spritesOnNewTileRow(spritesOnTileRow->heads[newTileY],
				spritesOnTileRow->tails[newTileY]);

		spritesOnOldTileRow.unlink(this);
		spritesOnNewTileRow.insertAfterHead(this);
	}

	for (CImage *i = this->images.head; i; i = i->link.next)
		i->flags |= 1;
}