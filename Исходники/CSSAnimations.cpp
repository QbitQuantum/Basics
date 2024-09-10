void CSSAnimations::calculateAnimationUpdate(CSSAnimationUpdate* update, const Element* animatingElement, Element& element, const RenderStyle& style, RenderStyle* parentStyle, StyleResolver* resolver)
{
    const ActiveAnimations* activeAnimations = animatingElement ? animatingElement->activeAnimations() : nullptr;

#if !ENABLE(ASSERT)
    // If we're in an animation style change, no animations can have started, been cancelled or changed play state.
    // When ASSERT is enabled, we verify this optimization.
    if (activeAnimations && activeAnimations->isAnimationStyleChange())
        return;
#endif

    const CSSAnimationData* animationData = style.animations();
    const CSSAnimations* cssAnimations = activeAnimations ? &activeAnimations->cssAnimations() : nullptr;

    HashSet<AtomicString> inactive;
    if (cssAnimations) {
        for (const auto& entry : cssAnimations->m_animations)
            inactive.add(entry.key);
    }

    if (style.display() != NONE) {
        for (size_t i = 0; animationData && i < animationData->nameList().size(); ++i) {
            AtomicString animationName(animationData->nameList()[i]);
            if (animationName == CSSAnimationData::initialName())
                continue;

            bool isPaused = CSSTimingData::getRepeated(animationData->playStateList(), i) == AnimPlayStatePaused;

            // Keyframes and animation properties are snapshotted when the
            // animation starts, so we don't need to track changes to these,
            // with the exception of play-state.
            if (cssAnimations) {
                AnimationMap::const_iterator existing(cssAnimations->m_animations.find(animationName));
                if (existing != cssAnimations->m_animations.end()) {
                    inactive.remove(animationName);
                    AnimationPlayer* player = existing->value.get();
                    if (isPaused != player->paused()) {
                        ASSERT(!activeAnimations || !activeAnimations->isAnimationStyleChange());
                        update->toggleAnimationPaused(animationName);
                    }
                    continue;
                }
            }

            Timing timing = animationData->convertToTiming(i);
            RefPtr<TimingFunction> keyframeTimingFunction = timing.timingFunction;
            timing.timingFunction = Timing::defaults().timingFunction;
            AnimatableValueKeyframeVector resolvedKeyframes;
            resolveKeyframes(resolver, animatingElement, element, style, parentStyle, animationName, keyframeTimingFunction.get(), resolvedKeyframes);
            if (!resolvedKeyframes.isEmpty()) {
                ASSERT(!activeAnimations || !activeAnimations->isAnimationStyleChange());
                update->startAnimation(animationName, InertAnimation::create(AnimatableValueKeyframeEffectModel::create(resolvedKeyframes), timing, isPaused));
            }
        }
    }

    ASSERT(inactive.isEmpty() || cssAnimations);
    for (const AtomicString& animationName : inactive) {
        ASSERT(!activeAnimations || !activeAnimations->isAnimationStyleChange());
        update->cancelAnimation(animationName, *cssAnimations->m_animations.get(animationName));
    }
}