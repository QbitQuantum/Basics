Frame* ActionTimelineCache::loadEventFrameWithFlatBuffers(const flatbuffers::EventFrame *flatbuffers)
{
    EventFrame* frame = EventFrame::create();
    
    std::string event = flatbuffers->value()->c_str();
    
    if (event != "")
        frame->setEvent(event);    
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}