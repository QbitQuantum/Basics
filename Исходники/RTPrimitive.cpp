// ************************************************************
// get hit result with a ray.
RTHitResult RTPlane::GetHitResult(RTRay *r) {
    /*
    Ray = r->vStart + t * r->vDir
     and
    vNormal dot (vOrigin - vPointOnPlane) = 0.

    So substitute the ray equation r(t) in for x and solve for t:

      vNormal dot (vOrigin - ray(t)) = 0
      vNormal dot (vOrigin - vStart - vDir*t) = 0
      vNormal dot (vOrigin - vStart) = (vNormal dot vDir) * t
      t = [ vNormal dot (vOrigin - vStart) ] / (vNormal dot vDir)
    */

    Vec3 vDirToOrigin = vPos.Sub(r->vStart);
    vDirToOrigin.Normalize();

    Vec3 vDirNormalized = r->vDir.GetNormalized();


    GLfloat numerator = vec3_dot(&vNormal, &vDirToOrigin);
    GLfloat denominator = vec3_dot(&vNormal, &vDirNormalized);

    GLfloat t = (GLfloat) (numerator / denominator);

    RTHitResult hr;
    hr.Clear();

    // if line wasn't parallel or directly on the plane,
    if(t >= 0) {
        // find point hit
        hr.vPointHit = r->PointAtTValue(t);

        // if point hit was at a reasonable distance
        if(vec3_distance(&r->vStart, &hr.vPointHit) > 30) {
            hr.bHit = false;
            return hr;

        } else {
            // return a hit result containing the point, normal, etc.
            hr.bHit = true;
            hr.t = t;
            hr.vNormalHit = vNormal;
            hr.matHit = mat;

        }

    }

    return hr;

}