void DocumentRendererParent::DrawToCanvas(const nsIntSize& aSize,
                                          const nsCString& aData)
{
    if (!mCanvas || !mCanvasContext)
        return;

    DrawTarget* drawTarget = mCanvasContext->GetDrawTarget();
    Rect rect(0, 0, aSize.width, aSize.height);
    MaybeSnapToDevicePixels(rect, *drawTarget, true);
    RefPtr<DataSourceSurface> dataSurface =
        Factory::CreateWrappingDataSourceSurface(reinterpret_cast<uint8_t*>(const_cast<nsCString&>(aData).BeginWriting()),
                                                 aSize.width * 4,
                                                 IntSize(aSize.width, aSize.height),
                                                 SurfaceFormat::B8G8R8A8);
    SurfacePattern pattern(dataSurface, ExtendMode::CLAMP);
    drawTarget->FillRect(rect, pattern);

    gfxRect damageRect = mCanvasContext->UserToDevice(ThebesRect(rect));
    mCanvas->Redraw(damageRect);
}