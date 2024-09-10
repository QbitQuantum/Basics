/**
 * Compute the diffusely reemited light data and place the result into reemited.
 * localBasis : the object localBasis at the computation point.
 * surfaceCoordinate : the surface coordinate (texture coordinate) of the computation
 *   point on the object.
 * incident : the incident ray (light ray)
 * view : the view ray (from the camera or bounced)
 * incidentLight : the incident light comming from the incident ray.
 * reemitedLight : the light reemited into the view direction (result will be placed 
 *   here).
 */
void BeckmannBRDF::getDiffuseReemited(const Basis& localBasis, const Point2D& surfaceCoordinate, const LightVector& incidentLight, LightVector& reemitedLight)
{
  const Vector& incident = incidentLight.getRay().v;
  const Vector& view     = reemitedLight.getRay().v;

  //Computing the micro normal
  Vector microNormal;
  microNormal.setsum(incident, view);
  microNormal.mul(-1.0);
  microNormal.normalize();

  //Computing some cosinuses and sinuses
  Real cosLN = -localBasis.k.dot(incident);   // incident and normal
  Real cosVN = -localBasis.k.dot(view);       // view and normal 
  Real cosHN = localBasis.k.dot(microNormal); // micro normal and normal
  Real cosLH = -microNormal.dot(incident);    // incident and micro normal
  Real cosVH = -microNormal.dot(view);        // view and micro normal

  //Compute Beckmann and Shadowing&masking coeficients
  Real beckmann = BeckmannRoughnessFormula::BeckmannDistribution(cosHN, 
                                                                 _roughness);
  Real shadmask = BeckmannRoughnessFormula::BeckmannShadowMasking(cosLN, 
                                                                  cosVN, 
                                                                  cosVH, 
                                                                  cosHN);
  
  //Setting the polarisation framework
  LightVector localIncidentLight(incidentLight);
  localIncidentLight.changeIncidentPolarisationFramework(microNormal);
  localIncidentLight.flip();
  reemitedLight.changeReemitedPolarisationFramework(microNormal);

  if(cosVN <=0.001 || cosLN <=0.001)
  {
    reemitedLight.clear();
    return;
  }

  //Computing reflectances for each wavelength
  for(unsigned int i=0; i<localIncidentLight.size(); i++)
  {
    Real ROrth, RPara;
    getReflectance(cosLH, localIncidentLight[i].getIndex(), ROrth, RPara);
    reemitedLight[i].applyReflectance(localIncidentLight[i], RPara*beckmann*shadmask, ROrth*beckmann*shadmask);
  }
}