void
WinCompositorWidget::CreateTransparentSurface(const gfx::IntSize& aSize)
{
  MOZ_ASSERT(!mTransparentSurface && !mMemoryDC);
  RefPtr<gfxWindowsSurface> surface = new gfxWindowsSurface(aSize, SurfaceFormat::A8R8G8B8_UINT32);
  mTransparentSurface = surface;
  mMemoryDC = surface->GetDC();
}