/*
 * Phillips wave spectrum, equation 40 with modification specified in equation 41
 */
float Ocean::phillips(int n_prime, int m_prime) const
{
   // Wavevector
   float kx = M_PI * (2 * n_prime - _N) / _length;
   float kz = M_PI * (2 * m_prime - _N) / _length;
   vec2  k(kx, kz);
   
   // Magnitude of wavevector
   float k_length = glm::length(k);
   
   // Wind speed
	float w_length = glm::length(_w);

   // If wavevector is very small, no need to calculate, just return zero
   if (k_length < 0.000001) return 0.0;
   
   // Precaculate k^2 and k^4
	float k_length2 = k_length  * k_length;
	float k_length4 = k_length2 * k_length2;

   // Cosine factor - eliminates waves that travel perpendicular to the wind
   float k_dot_w = dot(normalize(k), normalize(_w));
	float k_dot_w2  = k_dot_w * k_dot_w;
   
   
	float L         = w_length * w_length / _g;
	float L2        = L * L;
	
   // Something a bit extra to keep waves from exploding. Not in the paper.
	float damping   = 0.001;
	float l2        = L2 * damping * damping;
   
   // Phillips spectrum as described in eqn  40 with modification described in 41 to
   // suppress very small waves that cause convergence problems
	return _A * (exp(-1.0f / (k_length2 * L2)) / k_length4) * k_dot_w2 * exp(-k_length2 * l2);
}