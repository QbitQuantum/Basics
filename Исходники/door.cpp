    void Door::OnUpdate()
    {
        // TODO: move this
        static const float MoveSpeed = 50.0f;

        auto gameObject = _gameObject.lock();
        if (gameObject)
        {
            Vector3 toTarget = _targetPosition - gameObject->GetTransform().GetPosition();
            if (toTarget.LengthSquared() > Math::Epsilon)
            {
                float dist = toTarget.Length();
                Vector3 dir = Vector3::Normalize(toTarget);

                float movementDist = MoveSpeed * gameObject->GetGameWorld()->GetTime().deltaTime;
                if (movementDist > dist)
                {
                    movementDist = dist;
                }

                gameObject->GetTransform().SetPosition(gameObject->GetTransform().GetPosition() + dir * movementDist);
            }
        }

        // Always try to close the door, unless overridden by OnActivate()
        _targetPosition = _closedPosition;
    }