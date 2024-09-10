        //! Return this vector reflected off the surface with the given normal \a N. N should be normalized.
        vec3<Type> reflect(const vec3<Type>& N) const
        {
            const vec3<Type>& I(*this);

            return I - 2 * N.dot(I) * N;
        }