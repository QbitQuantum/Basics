void FieldCharacter::UpdateDirection(Vector2 directionVector)
{
    directionVector = directionVector.Normalize();

    // We'll snap the player's direction vector according to
    // the nearest direction for which we have an animation.
    double angleToHorizontal = acos(directionVector.GetX());

    // acos() only returns values from 0 to pi,
    // so to get the full circle we need to check
    // whether we're in the bottom two quandrants,
    // and change the angle to account for this if so.
    if (directionVector.GetY() > 0)
    {
        angleToHorizontal = 2 * M_PI - angleToHorizontal;
    }

    if (angleToHorizontal <= M_PI / 8 || angleToHorizontal > M_PI * 15 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionSide);
        SetDirection(CharacterDirectionRight);
    }
    else if (angleToHorizontal > M_PI / 8 && angleToHorizontal <= M_PI * 3 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionDiagonalUp);
        SetDirection(CharacterDirectionRight);
    }
    else if (angleToHorizontal > 3 * M_PI / 8 && angleToHorizontal <= M_PI * 5 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionUp);
    }
    else if (angleToHorizontal > 5 * M_PI / 8 && angleToHorizontal <= M_PI * 7 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionDiagonalUp);
        SetDirection(CharacterDirectionLeft);
    }
    else if (angleToHorizontal > 7 * M_PI / 8 && angleToHorizontal <= M_PI * 9 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionSide);
        SetDirection(CharacterDirectionLeft);
    }
    else if (angleToHorizontal > 9 * M_PI / 8 && angleToHorizontal <= M_PI * 11 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionDiagonalDown);
        SetDirection(CharacterDirectionLeft);
    }
    else if (angleToHorizontal > 11 * M_PI / 8 && angleToHorizontal <= M_PI * 13 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionDown);
    }
    else if (angleToHorizontal > 13 * M_PI / 8 && angleToHorizontal <= M_PI * 15 / 8)
    {
        SetSpriteDirection(FieldCharacterDirectionDiagonalDown);
        SetDirection(CharacterDirectionRight);
    }
}