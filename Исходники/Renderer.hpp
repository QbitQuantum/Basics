			__forceinline static Vec3f getDirectContribution(const AreaLight* light, int idx, const Vec3f& origin, 
												 const Vec3f& normal, const RayTracer* rt, Sequence* s)
			{
				// Draw a sample on light source
				float pdf;
				Vec3f Pl;
				light->sample( pdf, Pl, idx, s );

				// Construct vector from current vertex (o) to light sample
				Vec3f vl = Pl - origin;
				Vec3f vl_normalized = vl.normalized();

				// Calculate the lamp cosine term and check whether we're at the back of the lamp
				float cosl = FW::clamp(FW::dot(light->getNormal(), -vl_normalized), 0.0f, 1.0f);
				if (cosl == 0.0f) 
					return Vec3f(0.0f);

				// Trace shadow ray to see if it's blocked
				if (!rt->rayCastShadow(origin + EPSILON*normal, vl))
				{
					// If not, add the appropriate emission, 1/r^2 and clamped cosine terms, accounting for the PDF as well.
					// accumulate into E
					float cosv = FW::clamp(FW::dot(vl_normalized, normal), 0.0f, 1.0f);
					float vl_length = vl.length();
					return (light->getEmission() * (1.0f/(vl_length*vl_length)) * cosl * cosv) / pdf;
				}

				return Vec3f(0.0f);
			}