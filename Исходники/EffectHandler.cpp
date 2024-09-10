irr::video::ITexture* EffectHandler::generateRandomVectorTexture(const irr::core::dimension2du& dimensions,
        const irr::core::stringc& name)
{
    IImage* tmpImage = driver->createImage(irr::video::ECF_A8R8G8B8, dimensions);

    srand(device->getTimer()->getRealTime());

    for (u32 x = 0; x < dimensions.Width; ++x)
    {
        for (u32 y = 0; y < dimensions.Height; ++y)
        {
            vector3df randVec;

            // Reject vectors outside the unit sphere to get a uniform distribution.
            do
            {
                randVec = vector3df((f32)rand() / (f32)RAND_MAX, (f32)rand() / (f32)RAND_MAX, (f32)rand() / (f32)RAND_MAX);
            }
            while (randVec.getLengthSQ() > 1.0f);

            const SColorf randCol(randVec.X, randVec.Y, randVec.Z);
            tmpImage->setPixel(x, y, randCol.toSColor());
        }
    }

    ITexture* randTexture = driver->addTexture(name, tmpImage);

    tmpImage->drop();

    return randTexture;
}