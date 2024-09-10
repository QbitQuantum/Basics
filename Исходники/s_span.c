/**
 * Compute mipmap LOD from partial derivatives.
 * This the ideal solution, as given in the OpenGL spec.
 */
GLfloat
_swrast_compute_lambda(GLfloat dsdx, GLfloat dsdy, GLfloat dtdx, GLfloat dtdy,
                       GLfloat dqdx, GLfloat dqdy, GLfloat texW, GLfloat texH,
                       GLfloat s, GLfloat t, GLfloat q, GLfloat invQ)
{
   GLfloat dudx = texW * ((s + dsdx) / (q + dqdx) - s * invQ);
   GLfloat dvdx = texH * ((t + dtdx) / (q + dqdx) - t * invQ);
   GLfloat dudy = texW * ((s + dsdy) / (q + dqdy) - s * invQ);
   GLfloat dvdy = texH * ((t + dtdy) / (q + dqdy) - t * invQ);
   GLfloat x = SQRTF(dudx * dudx + dvdx * dvdx);
   GLfloat y = SQRTF(dudy * dudy + dvdy * dvdy);
   GLfloat rho = MAX2(x, y);
   GLfloat lambda = LOG2(rho);
   return lambda;
}