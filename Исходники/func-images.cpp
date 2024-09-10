template <typename T> void
ImagesClass<T>::setImplementation(int i)
{
    char str[100];
    clMath::BlasBase *base = clMath::BlasBase::getInstance();


    if (i != I_IMAGES) {
        if (base->useImages()) {
            base->removeScratchImages();
        }
        base->setUseImages(false);
    }

#if WIN32
    if (i == I_DEFAULT) {
        sprintf (str, "%s=", metod.env);
    }
    else {
        sprintf (str, "%s=%i",metod.env, i);
    }
    _putenv(str);
#else
    if (i == I_DEFAULT) {
        str[0] = '\0';
    }
    else {
        sprintf (str, "%i", i);
    }

    setenv(metod.env, str, 1);
#endif

    if (i == I_IMAGES) {
        base->setUseImages(true);
        if (base->useImages()) {
            if (base->addScratchImages()) {
                std::cerr << ">> FATAL ERROR, CANNOT CREATE SCRATCH IMAGES!"
                          << std::endl
                          << ">> Test skipped." << ::std::endl;
                SUCCEED();
            }
        }
   }

}