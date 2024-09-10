ECode CGestureStore::RemoveGesture(
    /* [in] */  const String& entryName,
    /* [in] */  IGesture *gesture)
{
    AutoPtr<GestureList> gestures;
    HashMap<String, AutoPtr<GestureList> >::Iterator iter;
    for (iter = mNamedGestures.Begin(); iter != mNamedGestures.End(); ++iter) {
        if ((iter->mFirst).Equals(entryName) ) {
            gestures = iter->mSecond;
        }
    }
    if (gestures == NULL) {
        return NOERROR;
    }

    gestures->Remove(gesture);

    // if there are no more samples, remove the entry automatically
    if (gestures->IsEmpty()) {
        mNamedGestures.Erase(entryName);
    }
    Int64 id;
    gesture->GetID(&id);
    mClassifier->RemoveInstance(id);

    mChanged = TRUE;
    return NOERROR;
}