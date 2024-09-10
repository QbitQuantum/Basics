bool CreatureSet::RegisterTextures(IVideoDriver* videoDriver,
                                   ResourceManager* resourceManager)
{
    bool result = false;

    //STEP 1: Build an atlas index of all the images needed for textures from the backing file.
    LOGI("Initializing tile images from file %s", _resourceName.c_str());

    ResourceBundle* spriteResourceBundle = resourceManager->GetResourceBundle(
            "Creatures");

    //WARNING: Early returns here!  I don't normally like this but the alternative is
    //huge if/else blocks.
    if (NULL == spriteResourceBundle)
    {
        LOGE("Could not find the 'Creatures' resource bundle in the resource manager.");
        return false;
    }

    if (NULL == videoDriver)
    {
        LOGE(
            "The video driver is null.  Since this is needed for creating images this is unrecoverable.");
        return false;
    }
    //END WARNING

    IImage* image = videoDriver->createImageFromFile(spriteResourceBundle->Find(
                        _resourceName));

    int totalSpriteCountScope = 0;

    if (NULL == image)
    {
        LOGE("Unable to load image associated with map png file.");
    }
    else
    {
        LOGD("Image size is %d x %d", image->getDimension().Width,
             image->getDimension().Height);

        //Tiles are identified by an atlas index which tells the system which image in a tilesheet
        //numbered starting from 0 in the upper left corner and proceeding width first belongs
        //to a tile.
        map<int, IImage*> spriteAtlasImageIndexMap;

        int spritesPerRow = image->getDimension().Width / spriteWidth;
        int spritesPerColumn = image->getDimension().Height / spriteHeight;

        const int totalSpriteCount = spritesPerRow * spritesPerColumn;
        totalSpriteCountScope = totalSpriteCount;

        int atlasIndex = 0;
        position2d<s32> position(0, 0);
        //TODO: Round up to the nearest power of two per image
        dimension2d<u32> dimensions(64, 64);

        //Indices for the tilesheets increase breatdth first then depth.
        for (int y = 0; y < spritesPerColumn; y++)
        {
            for (int x = 0; x < spritesPerRow; x++)
            {
                IImage* imageTile = videoDriver->createImage(image->getColorFormat(),
                                    dimensions);
                imageTile->fill(image->getPixel(0, 0));
                rect<s32> sourceRect(x * spriteWidth, y * spriteHeight, (x
                                     * spriteWidth) + spriteWidth, (y * spriteHeight) + spriteHeight);

                image->copyTo(imageTile, position, sourceRect);

                if (NULL != imageTile)
                {
                    LOGD(
                        "Image of sprite being associated with the atlasIndex %d is %d x %d",
                        atlasIndex, imageTile->getDimension().Width,
                        imageTile->getDimension().Height);
                    spriteAtlasImageIndexMap.set(atlasIndex, imageTile);
                }
                else
                {
                    LOGE("Unable to properly cut out a sprite at upper left (%d, %d)",
                         sourceRect.UpperLeftCorner.X, sourceRect.UpperLeftCorner.Y);
                }

                atlasIndex++;
            }
        }

        LOGD("Dropping no longer needed image.");
        image->drop();
        image = NULL;

        //STEP 2: Iterate over tiles in this set and fetch their image from the atlasIndexMap
        map<stringc, CreatureDefinition*>::Iterator spriteMapIterator =
            _creatures.getIterator();

        while (!spriteMapIterator.atEnd())
        {
            map<stringc, CreatureDefinition*>::Node* node =
                spriteMapIterator.getNode();
            CreatureDefinition* creatureDefinition = node->getValue();

            stringc textureName(_worldName);
            textureName.append("-");
            textureName.append(creatureDefinition->GetName());

            if (NULL == videoDriver->getTexture(textureName))
            {
                LOGI(
                    "Texture named %s is not registered with the driver.  Registering.",
                    textureName.c_str());

                //TODO: This is holdover from the code for pulling in more than
                //one map tile for a specific type. Replace with specific handling
                //should animations become necessary.  What follows is the
                //ORIGINAL comment from the HexTileSet texture builder.
                //Tiles can have a length greater than 0 which means
                //including the starting index x grab the next LENGTH tiles
                for (int i = 0; i < creatureDefinition->GetIndexLength(); i++)
                {
                    int spriteAtlasIndex = creatureDefinition->GetAtlasIndex() + i;

                    if (creatureDefinition->GetIndexLength() > 1)
                    {
                        char spriteIndex[5];
                        sprintf(spriteIndex, "%d", spriteAtlasIndex);
                        stringc incrTextureName(_worldName);
                        incrTextureName.append("-");
                        incrTextureName.append(creatureDefinition->GetName());
                        incrTextureName.append("-");
                        incrTextureName.append(spriteIndex);
                        incrTextureName.trim();

                        textureName = incrTextureName;
                    }

                    map<int, IImage*>::Node* node = spriteAtlasImageIndexMap.find(
                                                        spriteAtlasIndex);
                    if (NULL != node)
                    {
                        IImage* textureResource = node->getValue();
                        if (NULL != textureResource)
                        {
                            LOGI("Started registering %s.", textureName.c_str());
                            ITexture* createdTexture = videoDriver->addTexture(textureName,
                                                       textureResource);
                            LOGI("Finished registering %s.", textureName.c_str());
                        }
                        else
                        {
                            LOGE(
                                "The image created for texture named %s is null or corrupted.",
                                textureName.c_str());
                        }
                    }
                }
            }
            spriteMapIterator++;
        }

        //STEP 3: Clean up
        //For all entries remaining in the map, delete the image as they were unused.
        map<int, IImage*>::Iterator mapIterator =
            spriteAtlasImageIndexMap.getIterator();

        while (!mapIterator.atEnd())
        {
            map<int, IImage*>::Node* node = mapIterator.getNode();
            if (NULL != node && NULL != node->getValue())
            {
                node->getValue()->drop();
            }
            else
            {
                LOGE(
                    "An entry in the temporary map is null or the image contained therein is null.  This is a potential resource leak!");
            }
            mapIterator++;
        }
        spriteAtlasImageIndexMap.clear();

        LOGD("Sprite texture resource cleanup complete.");

        result = true;
    }

    return result;
}