void
VRDisplayPresentation::CreateLayers()
{
  VRManagerChild *manager = VRManagerChild::Get();
  if (!manager) {
    // This should not happen, but let's log it and avoid a crash in case
    // of regression.
    NS_WARNING("VRManagerChild::Get returned null!");
    return;
  }

  unsigned int iLayer=0;
  for (dom::VRLayer& layer : mDOMLayers) {
    dom::HTMLCanvasElement* canvasElement = layer.mSource;
    if (!canvasElement) {
      /// XXX In the future we will support WebVR in WebWorkers here
      continue;
    }

    Rect leftBounds(0.0, 0.0, 0.5, 1.0);
    if (layer.mLeftBounds.Length() == 4) {
      leftBounds.SetRect(layer.mLeftBounds[0],
                         layer.mLeftBounds[1],
                         layer.mLeftBounds[2],
                         layer.mLeftBounds[3]);
    } else if (layer.mLeftBounds.Length() != 0) {
      /**
       * We ignore layers with an incorrect number of values.
       * In the future, VRDisplay.requestPresent may throw in
       * this case.  See https://github.com/w3c/webvr/issues/71
       */
      continue;
    }

    Rect rightBounds(0.5, 0.0, 0.5, 1.0);
    if (layer.mRightBounds.Length() == 4) {
      rightBounds.SetRect(layer.mRightBounds[0], 
                          layer.mRightBounds[1],
                          layer.mRightBounds[2],
                          layer.mRightBounds[3]);
    } else if (layer.mRightBounds.Length() != 0) {
      /**
       * We ignore layers with an incorrect number of values.
       * In the future, VRDisplay.requestPresent may throw in
       * this case.  See https://github.com/w3c/webvr/issues/71
       */
      continue;
    }

    nsCOMPtr<nsIEventTarget> target;
    nsIDocument* doc;
    doc = canvasElement->OwnerDoc();
    if (doc) {
      target = doc->EventTargetFor(TaskCategory::Other);
    }

    if (mLayers.Length() <= iLayer) {
      // Not enough layers, let's add one
      RefPtr<VRLayerChild> vrLayer =
        static_cast<VRLayerChild*>(manager->CreateVRLayer(mDisplayClient->GetDisplayInfo().GetDisplayID(),
                                                          target, mGroup));
      if (!vrLayer) {
        NS_WARNING("CreateVRLayer returned null!");
        continue;
      }
      vrLayer->Initialize(canvasElement, leftBounds, rightBounds);
      mLayers.AppendElement(vrLayer);
    } else {
      // We already have a layer, let's update it
      mLayers[iLayer]->Initialize(canvasElement, leftBounds, rightBounds);
    }
    iLayer++;
  }

  // Truncate any excess layers that weren't included in the updated list
  mLayers.SetLength(iLayer);
}