void CharacterController::checkCollision(MeshCollider* collider)
{
  Vector3 pos = getGameObject()->getTransform()->getPosition();

  Mesh* mesh = collider->getMesh();
  std::vector<Vector3>* vertices = mesh->getVertices();

  // We basically want to set the mesh to the origin, including its rotation.
  // If we rotate the mesh, then we need to make sure we rotate the characters bounds too
  // so that the angle between the mesh and character remains the same.
  // If we set position to 0, 0, then we need to make the characters bounds box move the same way
  // (minus the mesh's position) so that it doesn't get closer.

  Matrix4x4 mat = Matrix4x4::getTrs(collider->getGameObject()->getTransform()->getPosition(),
                          collider->getGameObject()->getTransform()->getRotation(),
                          Vector3(1, 1, 1));
  mat = mat.inverse();

  Vector3 relPos = mat * pos;
  Vector3 extents = bounds.extents;
  extents.y = extents.y / 2.0f; // Set to 20.0f for a large step

  //**********************************************
  Collision collision;
  //collision.relativeVelocity = frameMoveSpeed;

  for(int v = 0; v < vertices->size(); v+=3)
  {
    Vector3 a = vertices->at(v);
    Vector3 b = vertices->at(v+1);
    Vector3 c = vertices->at(v+2);

    if(colliding(relPos, extents, a, b, c) == true)
    {
      ContactPoint contact;

      contact.normal = findNormal(a, b, c);
      contact.thisCollider = this;
      contact.otherCollider = collider;
      contact.a = a;
      contact.b = b;
      contact.c = c;

      collision.contacts.push_back(contact);
    }
  }

  Matrix4x4 rotMat = Matrix4x4::getIdentity();
  rotMat = rotMat.rotate(collider->getGameObject()->getTransform()->getRotation() * -1.0f);

  if(collision.contacts.size() > 0)
  {
    //relPos = handleCollision(collision, relPos, extents);
    //relPos = relPos + (rotMat * handleCollision(collision, relPos, extents));
    relPos = relPos + handleCollision(collision, relPos, extents);
  }
  //*******************************************

  ///////////////////////////////////
  Collision stepCollision;
  Vector3 stepExtents = bounds.extents;
  stepExtents.x = stepExtents.x / 2.0f;
  stepExtents.z = stepExtents.z / 2.0f;
  stepExtents.y = stepExtents.y + 0.01f;

  for(int v = 0; v < vertices->size(); v+=3)
  {
    Vector3 a = vertices->at(v);
    Vector3 b = vertices->at(v+1);
    Vector3 c = vertices->at(v+2);

    if(colliding(relPos, stepExtents, a, b, c) == true)
    {
      ContactPoint contact;

      contact.normal = findNormal(a, b, c);
      contact.thisCollider = this;
      contact.otherCollider = collider;
      contact.a = a;
      contact.b = b;
      contact.c = c;

      stepCollision.contacts.push_back(contact);
    }
  }

  stepExtents.y = stepExtents.y - 0.01f;

  if(stepCollision.contacts.size() > 0)
  {
    grounded = true;
    relPos = relPos + (rotMat * handleStep(stepCollision, relPos, stepExtents));
  }
  else
  {
    //grounded = false;
  }
  ///////////////////////////////////

  mat = mat.inverse();
  getGameObject()->getTransform()->setPosition(mat * relPos);
}