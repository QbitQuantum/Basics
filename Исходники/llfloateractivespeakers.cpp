void LLSpeakerMgr::update(BOOL resort_ok)
{
    if (!gVoiceClient)
    {
        return;
    }

    LLColor4 speaking_color = gSavedSettings.getColor4("SpeakingColor");
    LLColor4 overdriven_color = gSavedSettings.getColor4("OverdrivenColor");

    if(resort_ok) // only allow list changes when user is not interacting with it
    {
        updateSpeakerList();
    }

    // update status of all current speakers
    BOOL voice_channel_active = (!mVoiceChannel && gVoiceClient->inProximalChannel()) || (mVoiceChannel && mVoiceChannel->isActive());
    for (speaker_map_t::iterator speaker_it = mSpeakers.begin(); speaker_it != mSpeakers.end();)
    {
        LLUUID speaker_id = speaker_it->first;
        LLSpeaker* speakerp = speaker_it->second;

        speaker_map_t::iterator  cur_speaker_it = speaker_it++;

        if (voice_channel_active && gVoiceClient->getVoiceEnabled(speaker_id))
        {
            speakerp->mSpeechVolume = gVoiceClient->getCurrentPower(speaker_id);
            BOOL moderator_muted_voice = gVoiceClient->getIsModeratorMuted(speaker_id);
            if (moderator_muted_voice != speakerp->mModeratorMutedVoice)
            {
                speakerp->mModeratorMutedVoice = moderator_muted_voice;
                speakerp->fireEvent(new LLSpeakerVoiceModerationEvent(speakerp));
            }

            if (gVoiceClient->getOnMuteList(speaker_id) || speakerp->mModeratorMutedVoice)
            {
                speakerp->mStatus = LLSpeaker::STATUS_MUTED;
            }
            else if (gVoiceClient->getIsSpeaking(speaker_id))
            {
                // reset inactivity expiration
                if (speakerp->mStatus != LLSpeaker::STATUS_SPEAKING)
                {
                    speakerp->mLastSpokeTime = mSpeechTimer.getElapsedTimeF32();
                    speakerp->mHasSpoken = TRUE;
                }
                speakerp->mStatus = LLSpeaker::STATUS_SPEAKING;
                // interpolate between active color and full speaking color based on power of speech output
                speakerp->mDotColor = speaking_color;
                if (speakerp->mSpeechVolume > LLVoiceClient::OVERDRIVEN_POWER_LEVEL)
                {
                    speakerp->mDotColor = overdriven_color;
                }
            }
            else
            {
                speakerp->mSpeechVolume = 0.f;
                speakerp->mDotColor = ACTIVE_COLOR;

                if (speakerp->mHasSpoken)
                {
                    // have spoken once, not currently speaking
                    speakerp->mStatus = LLSpeaker::STATUS_HAS_SPOKEN;
                }
                else
                {
                    // default state for being in voice channel
                    speakerp->mStatus = LLSpeaker::STATUS_VOICE_ACTIVE;
                }
            }
        }
        // speaker no longer registered in voice channel, demote to text only
        else if (speakerp->mStatus != LLSpeaker::STATUS_NOT_IN_CHANNEL)
        {
            if(speakerp->mType == LLSpeaker::SPEAKER_EXTERNAL)
            {
                // external speakers should be timed out when they leave the voice channel (since they only exist via SLVoice)
                speakerp->mStatus = LLSpeaker::STATUS_NOT_IN_CHANNEL;
            }
            else
            {
                speakerp->mStatus = LLSpeaker::STATUS_TEXT_ONLY;
                speakerp->mSpeechVolume = 0.f;
                speakerp->mDotColor = ACTIVE_COLOR;
            }
        }
    }

    if(resort_ok)  // only allow list changes when user is not interacting with it
    {
        // sort by status then time last spoken
        std::sort(mSpeakersSorted.begin(), mSpeakersSorted.end(), LLSortRecentSpeakers());
    }

    // for recent speakers who are not currently speaking, show "recent" color dot for most recent
    // fading to "active" color

    S32 recent_speaker_count = 0;
    S32 sort_index = 0;
    speaker_list_t::iterator sorted_speaker_it;
    for(sorted_speaker_it = mSpeakersSorted.begin();
            sorted_speaker_it != mSpeakersSorted.end(); )
    {
        LLPointer<LLSpeaker> speakerp = *sorted_speaker_it;

        // color code recent speakers who are not currently speaking
        if (speakerp->mStatus == LLSpeaker::STATUS_HAS_SPOKEN)
        {
            speakerp->mDotColor = lerp(speaking_color, ACTIVE_COLOR, clamp_rescale((F32)recent_speaker_count, -2.f, 3.f, 0.f, 1.f));
            recent_speaker_count++;
        }

        // stuff sort ordinal into speaker so the ui can sort by this value
        speakerp->mSortIndex = sort_index++;

        // remove speakers that have been gone too long
        if (speakerp->mStatus == LLSpeaker::STATUS_NOT_IN_CHANNEL && speakerp->mActivityTimer.hasExpired())
        {
            fireEvent(new LLSpeakerListChangeEvent(this, speakerp->mID), "remove");

            mSpeakers.erase(speakerp->mID);
            sorted_speaker_it = mSpeakersSorted.erase(sorted_speaker_it);
        }
        else
        {
            ++sorted_speaker_it;
        }
    }
}