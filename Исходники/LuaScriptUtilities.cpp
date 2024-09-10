void LuaScriptUtilities::SetLineStartEnd(
    Ogre::SceneNode* line,
    const Ogre::Vector3& start,
    const Ogre::Vector3& end)
{
    Ogre::Vector3 lineVector = end - start;

    Ogre::Quaternion lineRotation =
        Ogre::Vector3::UNIT_Z.getRotationTo(lineVector.normalisedCopy());

    line->setOrientation(lineRotation *
                         Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X));
    line->setPosition(start);
    line->setScale(0.01f, lineVector.length(), 0.01f);
}