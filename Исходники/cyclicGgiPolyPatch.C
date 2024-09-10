void Foam::cyclicGgiPolyPatch::checkDefinition() const
{
    // A little bit of sanity check The rotation angle/axis is
    // specified in both the master and slave patch of the
    // cyclicGgi.  This is a pain, but the other alternatives
    // would be:
    //
    //   - Specify in only of the two patches boundary
    //   definition : - which one to chose?  - which default
    //   value to chose for the non-initialized value - Use a
    //   specific dictionary for this... Nope, too cumbersome.
    //
    // So, we impose that the boundary definition of both
    // patches must specify the same information If not, well,
    // we stop the simulation and ask for a fix.

    if (!active())
    {
        // No need to check anything, the shadow is not initialized properly.
        // This will happen with blockMesh when defining cyclicGGI patches.
        // Return quietly
        return;
    }

    if
    (
        (mag(rotationAngle()) - mag(cyclicShadow().rotationAngle())) > SMALL
     || cmptSum(rotationAxis() - cyclicShadow().rotationAxis()) > SMALL
    )
    {
        FatalErrorIn("void cyclicGgiPolyPatch::check() const")
            << "    Rotation angle for patch name           : "
            << name() << " is: " << rotationAngle()
            << " axis: " << rotationAxis() << nl
            << "    Rotation angle for shadow patch name: "
            << shadowName() << " is: "
            << cyclicShadow().rotationAngle() << " axis: "
            << cyclicShadow().rotationAxis() << nl
            << "    Both values need to be opposite in "
            << "the boundary file. "
            << abort(FatalError);
    }

    if
    (
        (mag(separationOffset() + cyclicShadow().separationOffset())) > SMALL
    )
    {
        FatalErrorIn("void cyclicGgiPolyPatch::check() const")
            << "Separation offset for patch name           : "
            << name() << " is: " << separationOffset()
            << "    Separation offset for shadow patch name: "
            << shadowName() << " is: "
            << cyclicShadow().separationOffset() << " axis: "
            << "    Both values need to be opposite in "
            << "the boundary file. "
            << abort(FatalError);
    }

    if (debug > 1 && master())
    {
        Info<< "Writing transformed slave patch as VTK." << nl
            << "Master: " << name()
            << " Slave: " << shadowName()
            << " Angle (master to slave): " << rotationAngle() << " deg"
            << " Axis: " << rotationAxis()
            << " Separation: " << separationOffset() << endl;

            const polyMesh& mesh = boundaryMesh().mesh();

            fileName fvPath(mesh.time().path()/"VTK");
            mkDir(fvPath);

            pointField transformedPoints = cyclicShadow().localPoints();

            tensor rot = RodriguesRotation(rotationAxis_,  -rotationAngle_);

            transform(transformedPoints, rot, transformedPoints);

            // Add separation offset to transformed points.  HJ, 24/Nov/2009
            transformedPoints += cyclicShadow().separationOffset();

            standAlonePatch::writeVTK
            (
                fvPath/fileName("cyclicGgi" + name() + cyclicShadow().name()),
                cyclicShadow().localFaces(),
                transformedPoints
            );
    }
}