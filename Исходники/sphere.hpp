        //! Intersect ray and sphere, returning true if there is an intersection.
        bool intersect(const ray<Type>& r, Type& tmin, Type& tmax) const
        {
            const vec3<Type> r_to_s = r.getOrigin() - m_center;

            //Compute A, B and C coefficients
            const Type A = r.getDirection().sqrLength();
            const Type B = 2.0f * r_to_s.dot(r.getDirection());
            const Type C = r_to_s.sqrLength() - m_radius * m_radius;

            //Find discriminant
            Type disc = B * B - 4.0 * A * C;

            // if discriminant is negative there are no real roots
            if (disc < 0.0)
                return false;

            disc = (Type)std::sqrt((double)disc);

            tmin = (-B + disc) / (2.0 * A);
            tmax = (-B - disc) / (2.0 * A);

            // check if we're inside it
            if ((tmin < 0.0 && tmax > 0) || (tmin > 0 && tmax < 0))
                return false;

            if (tmin > tmax)
                std::swap(tmin, tmax);

            return (tmin > 0);
        }