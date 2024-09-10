//
inline float degreeToRadian(float deg){ return deg/180*M_PI; }
const float a = 6378137;       // semi-major axis of the ellipsoid
const float e = 0.08181919106; // first eccentricity of the ellipsoid
const float lc = degreeToRadian(3.f);
const float l0 = degreeToRadian(3.f);
const float phi1 = degreeToRadian(44.f); // 1st automecoic parallel
const float phi2 = degreeToRadian(49.f); // 2nd automecoic parallel
const float phi0 = degreeToRadian(46.5f);// latitude of origin
const float X0 =  700000; // x coordinate at origin
const float Y0 = 6600000; // y coordinate at origin
// Normals
const float gN1 = a/sqrt(1-e*e*sin(phi1)*sin(phi1));
const float gN2 = a/sqrt(1-e*e*sin(phi2)*sin(phi2));
// Isometric latitudes
const float gl1=log(tan(M_PI/4+phi1/2)*pow((1-e*sin(phi1))/(1+e*sin(phi1)),e/2));
const float gl2=log(tan(M_PI/4+phi2/2)*pow((1-e*sin(phi2))/(1+e*sin(phi2)),e/2));
const float gl0=log(tan(M_PI/4+phi0/2)*pow((1-e*sin(phi0))/(1+e*sin(phi0)),e/2));
// Projection exponent
const float n = (log((gN2*cos(phi2))/(gN1*cos(phi1))))/(gl1-gl2);
// Projection constant
const float c = ((gN1*cos(phi1))/n)*exp(n*gl1);
// Coordinate
const float ys = Y0 + c*exp(-n*gl0);

// Convert geographic coordinates (latitude, longitude in degrees) into
// cartesian coordinates (in kilometers) using the Lambert 93 projection.
pair<float,float> geoToLambert93(float latitude,float longitude)
{
    float phi = degreeToRadian(latitude);
    float l   = degreeToRadian(longitude);