AutoPtr<IBitmap> CWallpaperManager::GenerateBitmap(
    /* [in] */ IContext* context,
    /* [in] */ IBitmap* bm,
    /* [in] */ Int32 width,
    /* [in] */ Int32 height)
{
    if (bm == NULL) {
        return NULL;
    }

    AutoPtr<IWindowManager> wm;
    ASSERT_SUCCEEDED(context->GetSystemService(IContext::WINDOW_SERVICE,
            (IInterface**)&wm));
    AutoPtr<IDisplayMetrics> metrics;
    ASSERT_SUCCEEDED(CDisplayMetrics::New((IDisplayMetrics**)&metrics));
    AutoPtr<IDisplay> display;
    ASSERT_SUCCEEDED(wm->GetDefaultDisplay((IDisplay**)&display));
    ASSERT_SUCCEEDED(display->GetMetrics(metrics));
    Int32 dpi;
    metrics->GetNoncompatDensityDpi(&dpi);
    bm->SetDensity(dpi);

    Int32 w, h;
    if (width <= 0 || height <= 0
            || ((bm->GetWidth(&w), w == width)
                    && (bm->GetHeight(&h), h == height))) {
        return bm;
    }

    // This is the final bitmap we want to return.
    // try {
    AutoPtr<IBitmapFactory> factory;
    ASSERT_SUCCEEDED(CBitmapFactory::AcquireSingleton((IBitmapFactory**)&factory));
    AutoPtr<IBitmap> newbm;
    ECode ec = factory->CreateBitmap(width, height,
            Elastos::Droid::Graphics::BitmapConfig_ARGB_8888, (IBitmap**)&newbm);
    if (ec == (ECode)E_OUT_OF_MEMORY_ERROR) {
        Slogger::W(TAG, "Can't generate default bitmap");
        return bm;
    }
    newbm->SetDensity(dpi);

    AutoPtr<ICanvas> c;
    ASSERT_SUCCEEDED(CCanvas::New(newbm, (ICanvas**)&c));
    AutoPtr<IRect> targetRect;
    ASSERT_SUCCEEDED(CRect::New((IRect**)&targetRect));
    Int32 targetRight, targetBottom;
    bm->GetWidth(&targetRight);
    bm->GetHeight(&targetBottom);
    targetRect->SetRight(targetRight);
    targetRect->SetBottom(targetBottom);

    Int32 deltaw = width - targetRight;
    Int32 deltah = height - targetBottom;

    if (deltaw > 0 || deltah > 0) {
        // We need to scale up so it covers the entire area.
        Float scale;
        if (deltaw > deltah) {
            scale = width / (Float)targetRight;
        }
        else {
            scale = height / (Float)targetBottom;
        }
        targetRight = (Int32)(Float)targetRight * scale;
        targetBottom = (Int32)(Float)targetBottom * scale;
        targetRect->SetRight(targetRight);
        targetRect->SetBottom(targetBottom);
        deltaw = width - targetRight;
        deltah = height - targetBottom;
    }

    targetRect->Offset(deltaw/2, deltah/2);

    AutoPtr<IPaint> paint;
    ASSERT_SUCCEEDED(CPaint::New((IPaint**)&paint));
    paint->SetFilterBitmap(TRUE);
    AutoPtr<IPorterDuffXfermode> mode;
    ASSERT_SUCCEEDED(CPorterDuffXfermode::New(Elastos::Droid::Graphics::PorterDuffMode_SRC,
            (IPorterDuffXfermode**)&mode));
    paint->SetXfermode((IXfermode*)mode.Get());
    c->DrawBitmap(bm, NULL, targetRect, paint);

    bm->Recycle();
    c->SetBitmap(NULL);
    return newbm;
    // } catch (OutOfMemoryError e) {
    //     Log.w(TAG, "Can't generate default bitmap", e);
    //     return bm;
    // }
}