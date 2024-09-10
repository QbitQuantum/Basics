void SoundEffects::HandleSoundFinished(StringHash eventType, VariantMap& eventData)
{
    using namespace SoundFinished;

    Node* soundNode = static_cast<Node*>(eventData[P_NODE].GetPtr());
    if (soundNode)
        soundNode->Remove();
}