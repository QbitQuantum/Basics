void
GradientStopsView::UpdateView()
{
  DrawTarget *dt = ui->dtWidget->GetDT();

  dt->FillRect(Rect(0, 0, 100000, 100000), ColorPattern(Color(0.5f, 0.5f, 0.5f, 1.0f)));

  RefPtr<GradientStops> stops = mTranslator->LookupGradientStops(mRefPtr);

  ui->listWidget->clear();
  if (!stops) {
    dt->Flush();
    ui->dtWidget->redraw();
    ui->listWidget->addItem("Dead");
    return;
  }

  IntSize dstSize = dt->GetSize();

  RefPtr<DrawTarget> tmpdt = dt->CreateSimilarDrawTarget(IntSize(20, 20), SurfaceFormat::B8G8R8X8);
  tmpdt->FillRect(Rect(0, 0, 10, 10), ColorPattern(Color(1.0f, 1.0f, 1.0f)));
  tmpdt->FillRect(Rect(10, 10, 10, 10), ColorPattern(Color(1.0f, 1.0f, 1.0f)));
  tmpdt->FillRect(Rect(10, 0, 10, 10), ColorPattern(Color(0.7f, 0.7f, 0.7f)));
  tmpdt->FillRect(Rect(0, 10, 10, 10), ColorPattern(Color(0.7f, 0.7f, 0.7f)));
  RefPtr<SourceSurface> src = tmpdt->Snapshot();
  tmpdt = NULL;

  Rect dstRect(0, 0, dstSize.width, dstSize.height);
  dt->FillRect(dstRect, SurfacePattern(src, ExtendMode::REPEAT));

  dt->FillRect(dstRect, LinearGradientPattern(Point(0, dstSize.height / 2), Point(dstSize.width, dstSize.height / 2), stops));

  dt->Flush();
  ui->dtWidget->redraw();
}