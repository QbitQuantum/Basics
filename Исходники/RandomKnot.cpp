void
RandomKnot::prepareAnimation(Position extent, bool xRepeat, bool yRepeat)
{
    // Find a random position within the window where the knot will be visible.
    const GLfloat knotWidth = 2.0 * extent.x;
    const GLfloat knotHeight = 2.0 * extent.y;
    if (knotWidth < mWindowWidth && knotHeight < mWindowHeight) {
        mBasePosition =
            Position(randomFloat(mWindowWidth - knotWidth),
                     randomFloat(mWindowHeight - knotHeight))
            + extent;
    } else {
        mBasePosition = Position(randomFloat() * mWindowWidth,
                                 randomFloat() * mWindowHeight);
    }

    // Give the knot a random speed, direction, angle and spin.
    mSpeed = randomFloat(mPrefs.minSpeed(), mPrefs.maxSpeed()) + 0.1;

    GLfloat dir;
    if (randomFloat() < mPrefs.skewProbability()) {
        dir = randomFloat(0.0, M_PI * 2.0);

        if (xRepeat) {
            mAngle = fmod(dir + M_PI_2, M_PI * 2.0);
        } else if (yRepeat) {
            mAngle = dir;
        } else {
            mAngle = randomFloat(0.0, M_PI * 2.0);
        }

    } else {
        int quad;
        if (xRepeat) {
            quad = 2 * randomInteger(2) + 1;
        } else if (yRepeat) {
            quad = 2 * randomInteger(2);
        } else {
            quad = randomInteger(4);
        }
        dir = quad * M_PI_2;
        mAngle = 0.0;
    }
    mDirection = Position(cos(dir), sin(dir));

    if (randomFloat() < mPrefs.spinProbability()) {
        mSpin = randomFloat(mPrefs.minSpin(), mPrefs.maxSpin())
            * ((randomFloat() < 0.5) ? 1.0 : -1.0)
            / 180.0 * M_PI;
    } else {
        mSpin = 0.0;
    }

    // Calculate the starting and stopping times, i.e., the time at which
    // the knot's bounding circle is tangent to the window's bounding circle.
    //
    // - project window midpoint to point P0 on line of movement at time T0.
    // - use Pythagoras to compute distance from P0 to center of knot
    // - calculate T0 - distance and T0 + distance
    const Position midPosition(mWindowWidth * 0.5, mWindowHeight * 0.5);
    const GLfloat t0 = (midPosition - mBasePosition) * mDirection;
    const Position p0 = mBasePosition + t0 * mDirection;

    const GLfloat hyp = norm(midPosition) + norm(extent);
    const GLfloat cat = norm(midPosition - p0);
    const GLfloat distance = sqrt(hyp * hyp - cat * cat);

    mTime    = t0 - distance;
    mMaxTime = t0 + distance;

    // Adjust the spin rate so the angle is consistent at start and stop.
    GLfloat iterations = floor((mMaxTime - mTime) / mSpeed);
    mSpin = floor(mSpin / M_PI * iterations) * M_PI / iterations;
}