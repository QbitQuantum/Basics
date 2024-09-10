/**
 * Add/modify an entry in the parameter map for the given component
 * to update its position. The component is const
 * as the move doesn't actually change the object
 * @param comp A reference to the component to move
 * @param pmap A reference to the ParameterMap that will hold the new position
 * @param pos The new position
 * @param positionType Defines how the given position should be interpreted @see
 * TransformType enumeration
 */
void moveComponent(const IComponent &comp, ParameterMap &pmap,
                   const Kernel::V3D &pos, const TransformType positionType) {
    //
    // This behaviour was copied from how MoveInstrumentComponent worked
    //

    // First set it to the new absolute position
    V3D newPos = pos;
    switch (positionType) {
    case Absolute: // Do nothing
        break;
    case Relative:
        newPos += comp.getPos();
        break;
    default:
        throw std::invalid_argument("moveComponent -  Unknown positionType: " +
                                    boost::lexical_cast<std::string>(positionType));
    }

    // Then find the corresponding relative position
    auto parent = comp.getParent();
    if (parent) {
        newPos -= parent->getPos();
        Quat rot = parent->getRotation();
        rot.inverse();
        rot.rotate(newPos);
    }

    // Add a parameter for the new position
    pmap.addV3D(comp.getComponentID(), "pos", newPos);
}