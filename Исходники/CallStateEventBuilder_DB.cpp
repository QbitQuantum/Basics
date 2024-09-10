/// Copies the element into the provided UtlString
bool  CallStateEventBuilder_DB::finishElement(UtlString& event)
/**<
 * @returns
 * - true if the returned element is validly constructed
 * - false if not (a caller error)
 */
{
    bool isComplete = mEventComplete;
    event.remove(0);

    if (isComplete)
    {
        event.append(mCurrentEvent);
        event.append(mCallInfo);
        event.append(mContactElement);
        event.append(mReferElement);
        event.append(mFailureElement);
        event.append(mRequestUri);
        event.append(mReferences);
        event.append(mCallerInternal);
        event.append(mCalleeRoute);
        event.append(mBranchId);
        event.append(mViaCount);
        event.append(");");

        reset();
    }

    return isComplete;
}