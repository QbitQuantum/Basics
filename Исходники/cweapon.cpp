void Weapon::use(Direction dir)
{
    if (getOwner() && getOwner()->getObjectType() & Object::OBJECT_TYPE_CHARACTER)
    {
        Character* owner = (Character*)getOwner();

        m_dir = dir;
        show();

        float dx, dy;
        getDeltas(dx, dy);

        ObjectWeakPtrs objects;
        if (Simulator::get().listObjectsAt(
                    owner->getX() + dx,
                    owner->getY() + dy,
                    owner->getZ(),
                    &objects))
        {
            std::for_each(
                objects.begin(), objects.end(),
                [this, owner](const ObjectWeakPtr& o)
            {
                ObjectSharedPtr object = o.lock();
                if (object->getObjectType() & Object::OBJECT_TYPE_CHARACTER)
                {
                    int damage = Math::ceilRandom(m_damage);

                    Character* target = (Character*)object.get();

                    Math::clamp(damage, 0, target->getHp());
                    target->onReceiveHit(owner, damage);
                    owner->onGiveHit(target, damage);
                }
            });
        }
    }
}