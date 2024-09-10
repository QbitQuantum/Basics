void CompoundUpdateInputVisitor::_updateFrames( Compound* compound )
{
    const Channel* channel = compound->getChannel();
    if( !compound->testInheritTask( fabric::TASK_ASSEMBLE ) || !channel )
        return;

    const Frames& inputFrames = compound->getInputFrames();
    if( inputFrames.empty( ))
    {
        compound->unsetInheritTask( fabric::TASK_ASSEMBLE );
        return;
    }

    for( FramesCIter i = inputFrames.begin(); i != inputFrames.end(); ++i )
    {
        //----- Find corresponding output frame
        Frame* frame = *i;
        const std::string& name = frame->getName();

        Compound::FrameMap::const_iterator j = _outputFrames.find( name );

        if( j == _outputFrames.end( ))
        {
            LBVERB << "Can't find matching output frame, ignoring input frame "
                   << name << std::endl;
            frame->unsetData();
            continue;
        }

        //----- Set frame parameters:
        // 1) Frame offset
        Frame* outputFrame = j->second;
        const Channel* iChannel = compound->getInheritChannel();
        Vector2i frameOffset = outputFrame->getMasterData()->getOffset() +
                               frame->getNativeOffset();

        if( outputFrame->getCompound()->getInheritChannel() != iChannel )
            frameOffset = frame->getNativeOffset();
        else if( channel != iChannel )
        {
            // compute delta offset between source and destination, since the
            // channel's native origin (as opposed to destination) is used.
            const Viewport& frameVP = frame->getViewport();
            const PixelViewport& inheritPVP=compound->getInheritPixelViewport();
            PixelViewport framePVP( inheritPVP );

            framePVP.apply( frameVP );
            frameOffset.x() -= framePVP.x;
            frameOffset.y() -= framePVP.y;

            const PixelViewport& iChannelPVP = iChannel->getPixelViewport();
            frameOffset.x() -= iChannelPVP.x;
            frameOffset.y() -= iChannelPVP.y;
        }
        frame->setOffset( frameOffset );

        // 2) zoom
        _updateZoom( compound, frame, outputFrame );

        // 3) TODO input frames are moved using the offset. The pvp signifies
        //    the pixels to be used from the frame data.
        //framePVP.x = static_cast< int32_t >( frameVP.x * inheritPVP.w );
        //framePVP.y = static_cast< int32_t >( frameVP.y * inheritPVP.h );
        //frame->setInheritPixelViewport( framePVP );
        //----- Link input frame to output frame (connects frame data)
        outputFrame->addInputFrame( frame, compound );

        for( unsigned k = 0; k < NUM_EYES; ++k )
        {
            const Eye eye = Eye( 1<<k );
            if( compound->isInheritActive( eye ) &&  // eye pass used
                outputFrame->hasData( eye ))         // output data for eye pass
            {
                frame->commit();
                LBLOG( LOG_ASSEMBLY )
                    << "Input frame  \"" << name << "\" on channel \""
                    << channel->getName() << "\" id " << frame->getID() << " v"
                    << frame->getVersion() << "\" tile pos "
                    << frame->getOffset() << ' ' << frame->getZoom()
                    << std::endl;
                break;
            }
        }
    }
}