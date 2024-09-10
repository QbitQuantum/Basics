WBEntity* WBCompEldFrobber::FindTargetFrobbable() const {
  if (m_FrobDisabled) {
    return nullptr;
  }

  InputSystem* const pInputSystem = GetFramework()->GetInputSystem();
  STATIC_HASHED_STRING(Frob);
  if (pInputSystem->IsSuppressed(sFrob)) {
    return nullptr;
  }

  const Array<WBCompEldFrobbable*>* const pFrobbablesArrays =
      WBComponentArrays::GetComponents<WBCompEldFrobbable>();
  if (!pFrobbablesArrays) {
    return nullptr;
  }

  WBEntity* const pEntity = GetEntity();
  DEVASSERT(pEntity);

  WBCompEldTransform* const pTransform =
      pEntity->GetTransformComponent<WBCompEldTransform>();
  DEVASSERT(pTransform);

  WBCompEldCamera* const pCamera = GET_WBCOMP(pEntity, EldCamera);

  const Vector StartOffset =
      pCamera ? pCamera->GetViewTranslationOffset(WBCompEldCamera::EVM_All)
              : Vector();
  const Vector StartLocation = pTransform->GetLocation() + StartOffset;
  const Vector Direction = pTransform->GetOrientation().ToVector();
  const Vector EndLocation = StartLocation + Direction * m_FrobDistance;
  const Segment FrobTraceSegment = Segment(StartLocation, EndLocation);

  // First, trace against world and collidables as a baseline for our trace
  // distance.
  CollisionInfo CollidableInfo;
  CollidableInfo.m_CollideWorld = true;
  CollidableInfo.m_CollideEntities = true;
  CollidableInfo.m_UserFlags = EECF_EntityCollision;

  GetWorld()->Trace(FrobTraceSegment, CollidableInfo);
  const float CollidableT = CollidableInfo.m_HitT;

  const Array<WBCompEldFrobbable*>& Frobbables = *pFrobbablesArrays;

  WBEntity* pNearestEntity = nullptr;
  float NearestT = 0.0f;

  const uint NumFrobbables = Frobbables.Size();
  for (uint FrobbableIndex = 0; FrobbableIndex < NumFrobbables;
       ++FrobbableIndex) {
    WBCompEldFrobbable* const pFrobbable = Frobbables[FrobbableIndex];
    ASSERT(pFrobbable);

    if (!pFrobbable->IsFrobbable()) {
      continue;
    }

    WBEntity* const pFrobbableEntity = pFrobbable->GetEntity();
    ASSERT(pFrobbableEntity);

    if (pFrobbableEntity->IsDestroyed()) {
      continue;
    }

    const AABB FrobbableBox = pFrobbable->GetBound();

    CollisionInfo Info;
    if (FrobTraceSegment.Intersects(FrobbableBox, &Info)) {
      if (Info.m_HitT <=
          CollidableT)  // Check if trace was blocked by some collision
      {
        if (Info.m_HitT < NearestT || pNearestEntity == nullptr) {
          pNearestEntity = pFrobbableEntity;
          NearestT = Info.m_HitT;
        }
      }
    }
  }

  return pNearestEntity;
}