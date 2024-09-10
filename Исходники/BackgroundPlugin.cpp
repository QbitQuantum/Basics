void BackgroundPlugin::test_bitmap_transparency(const ANPEvent* evt) {
    NPP instance = this->inst();

    // check default & set transparent
    if (!mFinishedStageOne) {

        gLogI.log(kDebug_ANPLogType, "BEGIN: testing bitmap transparency");

        //check to make sure it is not transparent
        if (evt->data.draw.data.bitmap.format == kRGBA_8888_ANPBitmapFormat) {
            gLogI.log(kError_ANPLogType, "bitmap default format is transparent");
        }

        //make it transparent (any non-null value will set it to true)
        bool value = true;
        NPError err = browser->setvalue(instance, NPPVpluginTransparentBool, &value);
        if (err != NPERR_NO_ERROR) {
            gLogI.log(kError_ANPLogType, "Error setting transparency.");
        }

        mFinishedStageOne = true;
        browser->invalidaterect(instance, NULL);
    }
    // check transparent & set opaque
    else if (!mFinishedStageTwo) {

        //check to make sure it is transparent
        if (evt->data.draw.data.bitmap.format != kRGBA_8888_ANPBitmapFormat) {
            gLogI.log(kError_ANPLogType, "bitmap did not change to transparent format");
        }

        //make it opaque
        NPError err = browser->setvalue(instance, NPPVpluginTransparentBool, NULL);
        if (err != NPERR_NO_ERROR) {
            gLogI.log(kError_ANPLogType, "Error setting transparency.");
        }

        mFinishedStageTwo = true;
    }
    // check opaque
    else if (!mFinishedStageThree) {

        //check to make sure it is not transparent
        if (evt->data.draw.data.bitmap.format == kRGBA_8888_ANPBitmapFormat) {
            gLogI.log(kError_ANPLogType, "bitmap default format is transparent");
        }

        gLogI.log(kDebug_ANPLogType, "END: testing bitmap transparency");

        mFinishedStageThree = true;
    }
}