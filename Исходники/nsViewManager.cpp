void
nsViewManager::ProcessPendingUpdatesForView(nsView* aView,
                                            bool aFlushDirtyRegion)
{
  NS_ASSERTION(IsRootVM(), "Updates will be missed");
  if (!aView) {
    return;
  }

  nsCOMPtr<nsIPresShell> rootShell(mPresShell);
  AutoTArray<nsCOMPtr<nsIWidget>, 1> widgets;
  aView->GetViewManager()->ProcessPendingUpdatesRecurse(aView, widgets);
  for (uint32_t i = 0; i < widgets.Length(); ++i) {
    nsView* view = nsView::GetViewFor(widgets[i]);
    if (view) {
      if (view->mNeedsWindowPropertiesSync) {
        view->mNeedsWindowPropertiesSync = false;
        if (nsViewManager* vm = view->GetViewManager()) {
          if (nsIPresShell* ps = vm->GetPresShell()) {
            ps->SyncWindowProperties(view);
          }
        }
      }
    }
    view = nsView::GetViewFor(widgets[i]);
    if (view) {
      view->ResetWidgetBounds(false, true);
    }
  }
  if (rootShell->GetViewManager() != this) {
    return; // presentation might have been torn down
  }
  if (aFlushDirtyRegion) {
    nsAutoScriptBlocker scriptBlocker;
    SetPainting(true);
    for (uint32_t i = 0; i < widgets.Length(); ++i) {
      nsIWidget* widget = widgets[i];
      nsView* view = nsView::GetViewFor(widget);
      if (view) {
        view->GetViewManager()->ProcessPendingUpdatesPaint(widget);
      }
    }
    SetPainting(false);
  }
}