Foam::tmp<Foam::pointField> Foam::sixDoFRigidBodyMotion::transform
(
    const pointField& initialPoints,
    const scalarField& scale
) const
{
    // Calculate the transformation septerion from the initial state
    septernion s
    (
        centreOfRotation() - initialCentreOfRotation(),
        quaternion(Q().T() & initialQ())
    );

    tmp<pointField> tpoints(new pointField(initialPoints));
    pointField& points = tpoints.ref();

    forAll(points, pointi)
    {
        // Move non-stationary points
        if (scale[pointi] > SMALL)
        {
            // Use solid-body motion where scale = 1
            if (scale[pointi] > 1 - SMALL)
            {
                points[pointi] = transform(initialPoints[pointi]);
            }
            // Slerp septernion interpolation
            else
            {
                septernion ss(slerp(septernion::I, s, scale[pointi]));

                points[pointi] =
                    initialCentreOfRotation()
                  + ss.invTransformPoint
                    (
                        initialPoints[pointi]
                      - initialCentreOfRotation()
                    );
            }
        }
    }

    return tpoints;
}