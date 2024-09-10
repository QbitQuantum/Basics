float AudioMixer::gainForSource(const PositionalAudioStream& streamToAdd,
                                const AvatarAudioStream& listeningNodeStream, const glm::vec3& relativePosition, bool isEcho) {
    float gain = 1.0f;

    float distanceBetween = glm::length(relativePosition);

    if (distanceBetween < EPSILON) {
        distanceBetween = EPSILON;
    }

    if (streamToAdd.getType() == PositionalAudioStream::Injector) {
        gain *= reinterpret_cast<const InjectedAudioStream*>(&streamToAdd)->getAttenuationRatio();
    }

    if (!isEcho && (streamToAdd.getType() == PositionalAudioStream::Microphone)) {
        //  source is another avatar, apply fixed off-axis attenuation to make them quieter as they turn away from listener
        glm::vec3 rotatedListenerPosition = glm::inverse(streamToAdd.getOrientation()) * relativePosition;

        float angleOfDelivery = glm::angle(glm::vec3(0.0f, 0.0f, -1.0f),
                                           glm::normalize(rotatedListenerPosition));

        const float MAX_OFF_AXIS_ATTENUATION = 0.2f;
        const float OFF_AXIS_ATTENUATION_FORMULA_STEP = (1 - MAX_OFF_AXIS_ATTENUATION) / 2.0f;

        float offAxisCoefficient = MAX_OFF_AXIS_ATTENUATION +
        (OFF_AXIS_ATTENUATION_FORMULA_STEP * (angleOfDelivery / PI_OVER_TWO));

        // multiply the current attenuation coefficient by the calculated off axis coefficient
        gain *= offAxisCoefficient;
    }

    float attenuationPerDoublingInDistance = _attenuationPerDoublingInDistance;
    for (int i = 0; i < _zonesSettings.length(); ++i) {
        if (_audioZones[_zonesSettings[i].source].contains(streamToAdd.getPosition()) &&
            _audioZones[_zonesSettings[i].listener].contains(listeningNodeStream.getPosition())) {
            attenuationPerDoublingInDistance = _zonesSettings[i].coefficient;
            break;
        }
    }

    if (distanceBetween >= ATTENUATION_BEGINS_AT_DISTANCE) {

        // translate the zone setting to gain per log2(distance)
        float g = 1.0f - attenuationPerDoublingInDistance;
        g = (g < EPSILON) ? EPSILON : g;
        g = (g > 1.0f) ? 1.0f : g;

        // calculate the distance coefficient using the distance to this node
        float distanceCoefficient = exp2f(log2f(g) * log2f(distanceBetween/ATTENUATION_BEGINS_AT_DISTANCE));

        // multiply the current attenuation coefficient by the distance coefficient
        gain *= distanceCoefficient;
    }

    return gain;
}