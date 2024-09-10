/* static */ already_AddRefed<MediaStreamAudioDestinationNode>
MediaStreamAudioDestinationNode::Create(AudioContext& aAudioContext,
                                        const AudioNodeOptions& aOptions,
                                        ErrorResult& aRv)
{
  if (aAudioContext.IsOffline()) {
    aRv.Throw(NS_ERROR_DOM_NOT_SUPPORTED_ERR);
    return nullptr;
  }

  if (aAudioContext.CheckClosed(aRv)) {
    return nullptr;
  }

  RefPtr<MediaStreamAudioDestinationNode> audioNode =
    new MediaStreamAudioDestinationNode(&aAudioContext);

  audioNode->Initialize(aOptions, aRv);
  if (NS_WARN_IF(aRv.Failed())) {
    return nullptr;
  }

  return audioNode.forget();
}