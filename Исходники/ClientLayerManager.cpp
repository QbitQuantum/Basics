void
ClientLayerManager::ForwardTransaction()
{
  mPhase = PHASE_FORWARD;

  // forward this transaction's changeset to our LayerManagerComposite
  AutoInfallibleTArray<EditReply, 10> replies;
  if (HasShadowManager() && ShadowLayerForwarder::EndTransaction(&replies)) {
    for (nsTArray<EditReply>::size_type i = 0; i < replies.Length(); ++i) {
      const EditReply& reply = replies[i];

      switch (reply.type()) {
      case EditReply::TOpContentBufferSwap: {
        MOZ_LAYERS_LOG(("[LayersForwarder] DoubleBufferSwap"));

        const OpContentBufferSwap& obs = reply.get_OpContentBufferSwap();

        CompositableChild* compositableChild =
          static_cast<CompositableChild*>(obs.compositableChild());
        ContentClientRemote* contentClient =
          static_cast<ContentClientRemote*>(compositableChild->GetCompositableClient());
        MOZ_ASSERT(contentClient);

        contentClient->SwapBuffers(obs.frontUpdatedRegion());

        break;
      }
      case EditReply::TOpTextureSwap: {
        MOZ_LAYERS_LOG(("[LayersForwarder] TextureSwap"));

        const OpTextureSwap& ots = reply.get_OpTextureSwap();

        CompositableChild* compositableChild =
          static_cast<CompositableChild*>(ots.compositableChild());
        MOZ_ASSERT(compositableChild);

        compositableChild->GetCompositableClient()
          ->SetDescriptorFromReply(ots.textureId(), ots.image());
        break;
      }
      case EditReply::TReplyTextureRemoved: {
        // XXX - to manage reuse of gralloc buffers, we'll need to add some
        // glue code here to find the TextureClient and invoke a callback to
        // let the camera know that the gralloc buffer is not used anymore on
        // the compositor side and that it can reuse it.
        break;
      }

      default:
        NS_RUNTIMEABORT("not reached");
      }
    }
  } else if (HasShadowManager()) {
    NS_WARNING("failed to forward Layers transaction");
  }

  mPhase = PHASE_NONE;

  // this may result in Layers being deleted, which results in
  // PLayer::Send__delete__() and DeallocShmem()
  mKeepAlive.Clear();
}