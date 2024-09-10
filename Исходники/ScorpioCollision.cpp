 void removeCollider(Collider* collider)
 {
     PS_ColliderSet::removeCollider(collider->_getImplementation());
     mCollider.remove(collider);
 }