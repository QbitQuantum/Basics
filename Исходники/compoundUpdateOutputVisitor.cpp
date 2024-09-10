void CompoundUpdateOutputVisitor::_updateFrames(Compound* compound)
{
    const Frames& outputFrames = compound->getOutputFrames();
    if (outputFrames.empty())
        compound->unsetInheritTask(fabric::TASK_READBACK);

    const Channel* channel = compound->getChannel();
    if (!compound->testInheritTask(fabric::TASK_READBACK) || !channel)
        return;

    for (FramesCIter i = outputFrames.begin(); i != outputFrames.end(); ++i)
    {
        //----- Check uniqueness of output frame name
        Frame* frame = *i;
        const std::string& name = frame->getName();

        if (_outputFrames.find(name) != _outputFrames.end())
        {
            LBWARN << "Multiple output frames of the same name are unsupported"
                   << ", ignoring output frame " << name << std::endl;
            frame->unsetData();
            continue;
        }

        //----- compute readback area
        const Viewport& frameVP = frame->getViewport();
        const PixelViewport& inheritPVP = compound->getInheritPixelViewport();
        PixelViewport framePVP(inheritPVP);
        framePVP.apply(frameVP);

        if (!framePVP.hasArea()) // output frame has no pixels
        {
            LBINFO << "Skipping output frame " << name << ", no pixels"
                   << std::endl;
            frame->unsetData();
            continue;
        }

        //----- Create new frame datas
        // * one frame data used for each eye pass
        // * data is set only on master frame data (will copy to all others)
        frame->cycleData(_frameNumber, compound);
        FrameData* frameData = frame->getMasterData();
        LBASSERT(frameData);

        LBLOG(LOG_ASSEMBLY)
            << lunchbox::disableFlush << "Output frame \"" << name << "\" id "
            << frame->getID() << " v" << frame->getVersion() + 1 << " data id "
            << frameData->getID() << " v" << frameData->getVersion() + 1
            << " on channel \"" << channel->getName() << "\" tile pos "
            << framePVP.x << ", " << framePVP.y;

        //----- Set frame data parameters:
        // 1) offset is position wrt destination view, used only by input frames
        const bool tiled = !compound->getInputTileQueues().empty();
        frameData->setOffset(tiled ? Vector2i(0, 0)
                                   : Vector2i(framePVP.x, framePVP.y));

        // 2) pvp is area within channel
        framePVP.x = static_cast<int32_t>(frameVP.x * inheritPVP.w);
        framePVP.y = static_cast<int32_t>(frameVP.y * inheritPVP.h);
        frameData->setPixelViewport(framePVP);

        // 3) image buffers and storage type
        const Frame::Buffer buffers = frame->getBuffers();

        frameData->setType(frame->getType());
        frameData->setBuffers(buffers == Frame::Buffer::undefined
                                  ? compound->getInheritBuffers()
                                  : buffers);

        // 4) (source) render context
        frameData->setContext(compound->setupRenderContext(EYE_CYCLOP));

        //----- Set frame parameters:
        // 1) offset is position wrt window, i.e., the channel position
        if (compound->getInheritChannel() == channel)
            frame->setOffset(Vector2i(inheritPVP.x, inheritPVP.y));
        else
        {
            const PixelViewport& nativePVP = channel->getPixelViewport();
            frame->setOffset(Vector2i(nativePVP.x, nativePVP.y));
        }

        // 2) zoom
        _updateZoom(compound, frame);

        //----- Commit
        frame->commitData();

        _outputFrames[name] = frame;
        LBLOG(LOG_ASSEMBLY)
            << " buffers " << frameData->getBuffers() << " read area "
            << framePVP << " readback " << frame->getZoom() << " assemble "
            << frameData->getZoom() << lunchbox::enableFlush << std::endl;
    }
}