void SMILTimeContainer::updateAnimations(SMILTime elapsed, bool seekToTime)
{
    SMILTime earliestFireTime = SMILTime::unresolved();

#ifndef NDEBUG
    // This boolean will catch any attempts to schedule/unschedule scheduledAnimations during this critical section.
    // Similarly, any elements removed will unschedule themselves, so this will catch modification of animationsToApply.
    m_preventScheduledAnimationsChanges = true;
#endif

    if (m_documentOrderIndexesDirty)
        updateDocumentOrderIndexes();

    Vector<RefPtr<SVGSMILElement> >  animationsToApply;
    GroupedAnimationsMap::iterator end = m_scheduledAnimations.end();
    for (GroupedAnimationsMap::iterator it = m_scheduledAnimations.begin(); it != end; ++it) {
        AnimationsVector* scheduled = it->value.get();

        // Sort according to priority. Elements with later begin time have higher priority.
        // In case of a tie, document order decides.
        // FIXME: This should also consider timing relationships between the elements. Dependents
        // have higher priority.
        std::sort(scheduled->begin(), scheduled->end(), PriorityCompare(elapsed));

        SVGSMILElement* resultElement = 0;
        unsigned size = scheduled->size();
        for (unsigned n = 0; n < size; n++) {
            SVGSMILElement* animation = scheduled->at(n);
            ASSERT(animation->timeContainer() == this);
            ASSERT(animation->targetElement());
            ASSERT(animation->hasValidAttributeName());

            // Results are accumulated to the first animation that animates and contributes to a particular element/attribute pair.
            // FIXME: we should ensure that resultElement is of an appropriate type.
            if (!resultElement) {
                if (!animation->hasValidAttributeType())
                    continue;
                resultElement = animation;
            }

            // This will calculate the contribution from the animation and add it to the resultsElement.
            if (!animation->progress(elapsed, resultElement, seekToTime) && resultElement == animation)
                resultElement = 0;

            SMILTime nextFireTime = animation->nextProgressTime();
            if (nextFireTime.isFinite())
                earliestFireTime = min(nextFireTime, earliestFireTime);
        }

        if (resultElement)
            animationsToApply.append(resultElement);
    }

    std::sort(animationsToApply.begin(), animationsToApply.end(), PriorityCompare(elapsed));

    unsigned animationsToApplySize = animationsToApply.size();
    if (!animationsToApplySize) {
#ifndef NDEBUG
        m_preventScheduledAnimationsChanges = false;
#endif
        scheduleAnimationFrame(earliestFireTime);
        return;
    }

    // Apply results to target elements.
    for (unsigned i = 0; i < animationsToApplySize; ++i)
        animationsToApply[i]->applyResultsToTarget();

#ifndef NDEBUG
    m_preventScheduledAnimationsChanges = false;
#endif

    scheduleAnimationFrame(earliestFireTime);

    for (unsigned i = 0; i < animationsToApplySize; ++i) {
        if (animationsToApply[i]->inDocument() && animationsToApply[i]->isSVGDiscardElement()) {
            RefPtr<SVGSMILElement> animDiscard = animationsToApply[i];
            RefPtr<SVGElement> targetElement = animDiscard->targetElement();
            if (targetElement && targetElement->inDocument()) {
                targetElement->remove(IGNORE_EXCEPTION);
                ASSERT(!targetElement->inDocument());
            }

            if (animDiscard->inDocument()) {
                animDiscard->remove(IGNORE_EXCEPTION);
                ASSERT(!animDiscard->inDocument());
            }
        }
    }
}