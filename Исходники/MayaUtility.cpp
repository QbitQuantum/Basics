bool util::isDrivenBySplineIK(const MFnIkJoint & iJoint)
{
    // spline IK can drive the starting joint's translate channel but
    // it has no connection to the translate plug.
    // we treat the joint as animated in this case.
    // find the ikHandle node.
    MPlug msgPlug = iJoint.findPlug("message", false);
    MPlugArray msgPlugDst;
    msgPlug.connectedTo(msgPlugDst, false, true);
    for (unsigned int i = 0; i < msgPlugDst.length(); i++) {
        MFnDependencyNode ikHandle(msgPlugDst[i].node());
        if (!ikHandle.object().hasFn(MFn::kIkHandle)) continue;

        // find the ikSolver node.
        MPlug ikSolverPlug = ikHandle.findPlug("ikSolver");
        MPlugArray ikSolverDst;
        ikSolverPlug.connectedTo(ikSolverDst, true, false);
        for (unsigned int j = 0; j < ikSolverDst.length(); j++) {

            // return true if the ikSolver is a spline solver.
            if (ikSolverDst[j].node().hasFn(MFn::kSplineSolver)) {
                return true;
            }
        }
    }
    
    return false;
}