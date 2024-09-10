void
TiledTextureImage::GetUpdateRegion(nsIntRegion& aForRegion)
{
    if (mTextureState != Valid) {
        // if the texture hasn't been initialized yet, or something important
        // changed, we need to recreate our backing surface and force the
        // client to paint everything
        aForRegion = IntRect(IntPoint(0, 0), mSize);
        return;
    }

    nsIntRegion newRegion;

    // We need to query each texture with the region it will be drawing and
    // set aForRegion to be the combination of all of these regions
    for (unsigned i = 0; i < mImages.Length(); i++) {
        int xPos = (i % mColumns) * mTileSize;
        int yPos = (i / mColumns) * mTileSize;
        IntRect imageRect = IntRect(IntPoint(xPos,yPos),
                                        mImages[i]->GetSize());

        if (aForRegion.Intersects(imageRect)) {
            // Make a copy of the region
            nsIntRegion subRegion;
            subRegion.And(aForRegion, imageRect);
            // Translate it into tile-space
            subRegion.MoveBy(-xPos, -yPos);
            // Query region
            mImages[i]->GetUpdateRegion(subRegion);
            // Translate back
            subRegion.MoveBy(xPos, yPos);
            // Add to the accumulated region
            newRegion.Or(newRegion, subRegion);
        }
    }

    aForRegion = newRegion;
}