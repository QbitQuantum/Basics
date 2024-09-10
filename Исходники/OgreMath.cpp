    //-----------------------------------------------------------------------
    std::pair<bool, Real> Math::intersects(const Ray& ray, 
        const list<Plane>::type& planes, bool normalIsOutside)
    {
        list<Plane>::type::const_iterator planeit, planeitend;
        planeitend = planes.end();
        bool allInside = true;
        std::pair<bool, Real> ret;
        std::pair<bool, Real> end;
        ret.first = false;
        ret.second = 0.0f;
        end.first = false;
        end.second = 0;


        // derive side
        // NB we don't pass directly since that would require Plane::Side in 
        // interface, which results in recursive includes since Math is so fundamental
        Plane::Side outside = normalIsOutside ? Plane::POSITIVE_SIDE : Plane::NEGATIVE_SIDE;

        for (planeit = planes.begin(); planeit != planeitend; ++planeit)
        {
            const Plane& plane = *planeit;
            // is origin outside?
            if (plane.getSide(ray.getOrigin()) == outside)
            {
                allInside = false;
                // Test single plane
                std::pair<bool, Real> planeRes = 
                    ray.intersects(plane);
                if (planeRes.first)
                {
                    // Ok, we intersected
                    ret.first = true;
                    // Use the most distant result since convex volume
                    ret.second = std::max(ret.second, planeRes.second);
                }
                else
                {
                    ret.first =false;
                    ret.second=0.0f;
                    return ret;
                }
            }
            else
            {
                std::pair<bool, Real> planeRes = 
                    ray.intersects(plane);
                if (planeRes.first)
                {
                    if( !end.first )
                    {
                        end.first = true;
                        end.second = planeRes.second;
                    }
                    else
                    {
                        end.second = std::min( planeRes.second, end.second );
                    }

                }

            }
        }

        if (allInside)
        {
            // Intersecting at 0 distance since inside the volume!
            ret.first = true;
            ret.second = 0.0f;
            return ret;
        }

        if( end.first )
        {
            if( end.second < ret.second )
            {
                ret.first = false;
                return ret;
            }
        }
        return ret;
    }