SceneEntity::SceneEntity(const Entity& obj) : PhysicalObject(obj)
{
    name = obj.GetParent();
}