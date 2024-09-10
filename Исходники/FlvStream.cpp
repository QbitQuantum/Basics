HRESULT FlvStream::RuntimeClassInitialize(IMFMediaSourceExt *pSource, IMFStreamDescriptor *pSD)
{
  source = pSource;//出现互相引用的情况，所以不addref
  stream_descriptor = pSD;
  assert(pSource != NULL && pSD != NULL);

  // Create the media event queue.
  return MFCreateEventQueue(&event_queue);
}