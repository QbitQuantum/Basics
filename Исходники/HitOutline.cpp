int HitOutline::Raycast(Point2D p, Vector2D v, Scalar maxTime, 
    Hit* hitArr, int hitArrSize, Scalar sense)
{
	//local data: Bart
	Hit localHitArr[100];
	int localHitArrSize=100;

    int hitCount = 0;

    // TODO: Currently very slow, brute force!
    int lineVertexCount = m_Lines.size();
	int quadVertexCount = m_Quads.size();

    Scalar epsilon = 1e-6;

	Point2D p1 = p;
	Point2D p2 = p+v;
    Point2D orig(0,0);
	Scalar vDv = v.Dot(v);
    Vector2D n = v.Orthogonal();

	// Line-line intersections.
	if( lineVertexCount > 0 )
	{
		Point2D* lines = &m_Lines[0];

		for( int i=0; i<lineVertexCount && hitCount<localHitArrSize; i += 2 )
		{
			Point2D q1 = lines[i+0];
			Point2D q2 = lines[i+1];

			Vector2D ortho = (q2-q1).Orthogonal();
			if( (dot(ortho, v) * sense < 0) || sense==0)
			{
				Scalar time1;
				Scalar time2;
				if( IntersectLines(p1, p2, q1, q2, time1, time2) )
				{
					if( time1 >= 0 && time1 < maxTime &&
						time2 >= 0 && time2 <= 1 )
					{
						Hit hit;
                        hit.Time = time1;
						hit.Point = p + time1 * v;
						hit.Normal = ortho.Normalized();
                        localHitArr[hitCount++] = hit;
					}
				}
			}
		}
	}

	// Line-quadratic intersections.
	if( quadVertexCount > 0 )
	{
		Point2D* quads = &m_Quads[0];
		for( int i=0; i<quadVertexCount && hitCount<localHitArrSize; i += 3 )
		{
			Vector2D q0 = quads[i+0] - p;
			Vector2D q1 = quads[i+1] - p;
			Vector2D q2 = quads[i+2] - p;

            // Hit only possible if:
            // (1) not all points are on same side of ray,
            //     
            // (2) and some points are in front of ray (currently not checked, handled by abc formula)

            Scalar dot_n_q0 = dot(n,q0);
            Scalar dot_n_q1 = dot(n,q1);
            Scalar dot_n_q2 = dot(n,q2);

            if( dot_n_q0 <= 0 && dot_n_q1 <= 0 && dot_n_q2 <= 0 )
                continue;

            if( dot_n_q0 >= 0 && dot_n_q1 >= 0 && dot_n_q2 >= 0 )
                continue;

            Scalar ts[2];
            Scalar a = 2*dot_n_q1-dot_n_q0-dot_n_q2;
            Scalar b = 2*dot_n_q0-2*dot_n_q1;
            Scalar c = -dot_n_q0;
			int n = solveQuadratic(a,b,c,ts);

			for( int j=0; j<n && hitCount < localHitArrSize; ++j )
			{
				Scalar t = ts[j];
				if( t >= 0 && t <= 1 )
				{
					Vector2D diff = (2*(q2-q1)+2*(q0-q1))*t+2*(q1-q0);
					Vector2D ortho = diff.Orthogonal();
					if( (dot(ortho, v) * sense < 0) || sense==0)
					{
						Vector2D h = lerp( lerp(q0,q1,t), lerp(q1,q2,t), t);
						Scalar time = h.Dot(v) / vDv;
						//time >= -maxTime
                        if( time >= 0 && time < maxTime )
                        {
						    Hit hit;
						    hit.Point = p+h;
						    hit.Time = time;
						    hit.Normal = ortho.Normalized();
                            localHitArr[hitCount++] = hit;
                        }
					}
				}
			}
		}
	}

    std::sort(localHitArr, localHitArr+hitCount, sortHitOnTime);
	//Bart
	for( int i=0; i<hitCount && i < hitArrSize; ++i )
	{
		hitArr[i]=localHitArr[i];
	}
    return hitCount;
}