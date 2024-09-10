float AudioParamTimeline::valuesForTimeRangeImpl(
    double startTime,
    double endTime,
    float defaultValue,
    float* values,
    unsigned numberOfValues,
    double sampleRate,
    double controlRate)
{
    ASSERT(values);
    if (!values)
        return defaultValue;

    // Return default value if there are no events matching the desired time range.
    if (!m_events.size() || endTime <= m_events[0].time()) {
        for (unsigned i = 0; i < numberOfValues; ++i)
            values[i] = defaultValue;
        return defaultValue;
    }

    // Maintain a running time and index for writing the values buffer.
    double currentTime = startTime;
    unsigned writeIndex = 0;

    // If first event is after startTime then fill initial part of values buffer with defaultValue
    // until we reach the first event time.
    double firstEventTime = m_events[0].time();
    if (firstEventTime > startTime) {
        double fillToTime = min(endTime, firstEventTime);
        unsigned fillToFrame = AudioUtilities::timeToSampleFrame(fillToTime - startTime, sampleRate);
        fillToFrame = min(fillToFrame, numberOfValues);
        for (; writeIndex < fillToFrame; ++writeIndex)
            values[writeIndex] = defaultValue;

        currentTime = fillToTime;
    }

    float value = defaultValue;

    // Go through each event and render the value buffer where the times overlap,
    // stopping when we've rendered all the requested values.
    // FIXME: could try to optimize by avoiding having to iterate starting from the very first event
    // and keeping track of a "current" event index.
    int n = m_events.size();
    for (int i = 0; i < n && writeIndex < numberOfValues; ++i) {
        ParamEvent& event = m_events[i];
        ParamEvent* nextEvent = i < n - 1 ? &(m_events[i + 1]) : 0;

        // Wait until we get a more recent event.
        if (nextEvent && nextEvent->time() < currentTime)
            continue;

        float value1 = event.value();
        double time1 = event.time();
        float value2 = nextEvent ? nextEvent->value() : value1;
        double time2 = nextEvent ? nextEvent->time() : endTime + 1;

        double deltaTime = time2 - time1;
        float k = deltaTime > 0 ? 1 / deltaTime : 0;
        double sampleFrameTimeIncr = 1 / sampleRate;

        double fillToTime = min(endTime, time2);
        unsigned fillToFrame = AudioUtilities::timeToSampleFrame(fillToTime - startTime, sampleRate);
        fillToFrame = min(fillToFrame, numberOfValues);

        ParamEvent::Type nextEventType = nextEvent ? static_cast<ParamEvent::Type>(nextEvent->type()) : ParamEvent::LastType /* unknown */;

        // First handle linear and exponential ramps which require looking ahead to the next event.
        if (nextEventType == ParamEvent::LinearRampToValue) {
            for (; writeIndex < fillToFrame; ++writeIndex) {
                float x = (currentTime - time1) * k;
                value = (1 - x) * value1 + x * value2;
                values[writeIndex] = value;
                currentTime += sampleFrameTimeIncr;
            }
        } else if (nextEventType == ParamEvent::ExponentialRampToValue) {
            if (value1 <= 0 || value2 <= 0) {
                // Handle negative values error case by propagating previous value.
                for (; writeIndex < fillToFrame; ++writeIndex)
                    values[writeIndex] = value;
            } else {
                float numSampleFrames = deltaTime * sampleRate;
                // The value goes exponentially from value1 to value2 in a duration of deltaTime seconds (corresponding to numSampleFrames).
                // Compute the per-sample multiplier.
                float multiplier = powf(value2 / value1, 1 / numSampleFrames);

                // Set the starting value of the exponential ramp. This is the same as multiplier ^
                // AudioUtilities::timeToSampleFrame(currentTime - time1, sampleRate), but is more
                // accurate, especially if multiplier is close to 1.
                value = value1 * powf(value2 / value1,
                                      AudioUtilities::timeToSampleFrame(currentTime - time1, sampleRate) / numSampleFrames);

                for (; writeIndex < fillToFrame; ++writeIndex) {
                    values[writeIndex] = value;
                    value *= multiplier;
                    currentTime += sampleFrameTimeIncr;
                }
            }
        } else {
            // Handle event types not requiring looking ahead to the next event.
            switch (event.type()) {
            case ParamEvent::SetValue:
            case ParamEvent::LinearRampToValue:
            case ParamEvent::ExponentialRampToValue:
            {
                currentTime = fillToTime;

                // Simply stay at a constant value.
                value = event.value();
                for (; writeIndex < fillToFrame; ++writeIndex)
                    values[writeIndex] = value;

                break;
            }

            case ParamEvent::SetTarget:
            {
                currentTime = fillToTime;

                // Exponential approach to target value with given time constant.
                float target = event.value();
                float timeConstant = event.timeConstant();
                float discreteTimeConstant = static_cast<float>(AudioUtilities::discreteTimeConstantForSampleRate(timeConstant, controlRate));

                for (; writeIndex < fillToFrame; ++writeIndex) {
                    values[writeIndex] = value;
                    value += (target - value) * discreteTimeConstant;
                }

                break;
            }

            case ParamEvent::SetValueCurve:
            {
                Float32Array* curve = event.curve();
                float* curveData = curve ? curve->data() : 0;
                unsigned numberOfCurvePoints = curve ? curve->length() : 0;

                // Curve events have duration, so don't just use next event time.
                float duration = event.duration();
                float durationFrames = duration * sampleRate;
                float curvePointsPerFrame = static_cast<float>(numberOfCurvePoints) / durationFrames;

                if (!curve || !curveData || !numberOfCurvePoints || duration <= 0 || sampleRate <= 0) {
                    // Error condition - simply propagate previous value.
                    currentTime = fillToTime;
                    for (; writeIndex < fillToFrame; ++writeIndex)
                        values[writeIndex] = value;
                    break;
                }

                // Save old values and recalculate information based on the curve's duration
                // instead of the next event time.
                unsigned nextEventFillToFrame = fillToFrame;
                float nextEventFillToTime = fillToTime;
                fillToTime = min(endTime, time1 + duration);
                fillToFrame = AudioUtilities::timeToSampleFrame(fillToTime - startTime, sampleRate);
                fillToFrame = min(fillToFrame, numberOfValues);

                // Index into the curve data using a floating-point value.
                // We're scaling the number of curve points by the duration (see curvePointsPerFrame).
                float curveVirtualIndex = 0;
                if (time1 < currentTime) {
                    // Index somewhere in the middle of the curve data.
                    // Don't use timeToSampleFrame() since we want the exact floating-point frame.
                    float frameOffset = (currentTime - time1) * sampleRate;
                    curveVirtualIndex = curvePointsPerFrame * frameOffset;
                }

                // Render the stretched curve data using nearest neighbor sampling.
                // Oversampled curve data can be provided if smoothness is desired.
                for (; writeIndex < fillToFrame; ++writeIndex) {
                    // Ideally we'd use round() from MathExtras, but we're in a tight loop here
                    // and we're trading off precision for extra speed.
                    unsigned curveIndex = static_cast<unsigned>(0.5 + curveVirtualIndex);

                    curveVirtualIndex += curvePointsPerFrame;

                    // Bounds check.
                    if (curveIndex < numberOfCurvePoints)
                        value = curveData[curveIndex];

                    values[writeIndex] = value;
                }

                // If there's any time left after the duration of this event and the start
                // of the next, then just propagate the last value.
                for (; writeIndex < nextEventFillToFrame; ++writeIndex)
                    values[writeIndex] = value;

                // Re-adjust current time
                currentTime = nextEventFillToTime;

                break;
            }
            }
        }
    }

    // If there's any time left after processing the last event then just propagate the last value
    // to the end of the values buffer.
    for (; writeIndex < numberOfValues; ++writeIndex)
        values[writeIndex] = value;

    return value;
}