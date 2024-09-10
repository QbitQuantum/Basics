template<> void TUNDRACORE_API Attribute<Transform>::Interpolate(IAttribute* start, IAttribute* end, float t, AttributeChange::Type change)
{
    Attribute<Transform>* startTrans = dynamic_cast<Attribute<Transform>*>(start);
    Attribute<Transform>* endTrans = dynamic_cast<Attribute<Transform>*>(end);
    if (startTrans && endTrans)
    {
        const Transform& startValue = startTrans->Get();
        const Transform& endValue = endTrans->Get();
        Transform newTrans;
        newTrans.pos = Lerp(startValue.pos, endValue.pos, t);
        newTrans.SetOrientation(Slerp(startValue.Orientation(), endValue.Orientation(), t));
        newTrans.scale = Lerp(startValue.scale, endValue.scale, t);
        Set(newTrans, change);
    }
}