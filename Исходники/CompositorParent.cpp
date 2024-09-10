void
CompositorParent::InitializeLayerManager(const nsTArray<LayersBackend>& aBackendHints)
{
  NS_ASSERTION(!mLayerManager, "Already initialised mLayerManager");

  for (size_t i = 0; i < aBackendHints.Length(); ++i) {
    RefPtr<LayerManagerComposite> layerManager;
    if (aBackendHints[i] == LAYERS_OPENGL) {
      layerManager =
        new LayerManagerComposite(new CompositorOGL(mWidget,
                                                    mEGLSurfaceSize.width,
                                                    mEGLSurfaceSize.height,
                                                    mUseExternalSurfaceSize));
    } else if (aBackendHints[i] == LAYERS_BASIC) {
      layerManager =
        new LayerManagerComposite(new BasicCompositor(mWidget));
#ifdef XP_WIN
    } else if (aBackendHints[i] == LAYERS_D3D11) {
      layerManager =
        new LayerManagerComposite(new CompositorD3D11(mWidget));
    } else if (aBackendHints[i] == LAYERS_D3D9) {
      layerManager =
        new LayerManagerComposite(new CompositorD3D9(mWidget));
#endif
    }

    if (!layerManager) {
      continue;
    }

    layerManager->SetCompositorID(mCompositorID);

    if (layerManager->Initialize()) {
      mLayerManager = layerManager;
      return;
    }
  }
}