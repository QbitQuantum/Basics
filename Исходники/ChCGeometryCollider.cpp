    static unsigned int BoxBoxContacts(
      Vector&  p_a, ChMatrix33<>& R_a, Vector const & ext_a,
      Vector&  p_b, ChMatrix33<>& R_b, Vector const & ext_b,
      double const & envelope,
      Vector * p,
	  Vector & n,
	  double * distances
      )
    {
      assert(p);
      assert(distances);

	  unsigned int cnt = 0;

      //--- Sign lookup table, could be precomputed!!!
      Vector sign[8];
      for(unsigned int mask=0;mask<8;++mask)
      {
        sign[mask](0) = (mask&0x0001)?1:-1;
        sign[mask](1) = ((mask>>1)&0x0001)?1:-1;
        sign[mask](2) = ((mask>>2)&0x0001)?1:-1;
      }
      //--- extract axis of boxes in WCS
      Vector A[3];
      A[0].x = R_a(0,0);   A[0].y = R_a(1,0);   A[0].z = R_a(2,0);
      A[1].x = R_a(0,1);   A[1].y = R_a(1,1);   A[1].z = R_a(2,1);
      A[2].x = R_a(0,2);   A[2].y = R_a(1,2);   A[2].z = R_a(2,2);
      Vector B[3];
      B[0].x = R_b(0,0);   B[0].y = R_b(1,0);   B[0].z = R_b(2,0);
      B[1].x = R_b(0,1);   B[1].y = R_b(1,1);   B[1].z = R_b(2,1);
      B[2].x = R_b(0,2);   B[2].y = R_b(1,2);   B[2].z = R_b(2,2);

      //--- To compat numerical round-offs, these tend to favor edge-edge
      //--- cases, when one really rather wants a face-case. Truncating
      //--- seems to let the algorithm pick face cases over edge-edge
      //--- cases.
      unsigned int i;

      for( i=0;i<3;++i)
        for(unsigned int j=0;j<3;++j)
        {
          if(fabs(A[i](j))<10e-7)
            A[i](j) = 0.;
          if(fabs(B[i](j))<10e-7)
            B[i](j) = 0.;
        }

      Vector a[8];
      Vector b[8];
      //--- corner points of boxes in WCS
      for( i=0;i<8;++i)
      {
        a[i] = A[2]*(sign[i](2)*ext_a(2)) + A[1]*(sign[i](1)*ext_a(1)) + A[0]*(sign[i](0)*ext_a(0)) + p_a;
        b[i] = B[2]*(sign[i](2)*ext_b(2)) + B[1]*(sign[i](1)*ext_b(1)) + B[0]*(sign[i](0)*ext_b(0)) + p_b;
	  }
      //--- Potential separating axes in WCS
      Vector axis[15];
      axis[0] = A[0];
      axis[1] = A[1];
      axis[2] = A[2];
      axis[3] = B[0];
      axis[4] = B[1];
      axis[5] = B[2];
      axis[6].Cross(A[0],B[0]);
      if(axis[6](0)==0 && axis[6](1)==0 && axis[6](2)==0)
        axis[6] = A[0];
      else
        axis[6] /= sqrt(axis[6].Dot(axis[6]));
      axis[7].Cross(A[0],B[1]);
      if(axis[7](0)==0 && axis[7](1)==0 && axis[7](2)==0)
        axis[7] = A[0];
      else
        axis[7] /= sqrt(axis[7].Dot(axis[7]));
      axis[8].Cross(A[0],B[2]);
      if(axis[8](0)==0 && axis[8](1)==0 && axis[8](2)==0)
        axis[8] = A[0];
      else
        axis[8] /= sqrt(axis[8].Dot(axis[8]));
      axis[9].Cross(A[1],B[0]);
      if(axis[9](0)==0 && axis[9](1)==0 && axis[9](2)==0)
        axis[9] = A[1];
      else
        axis[9] /= sqrt(axis[9].Dot(axis[9]));
      axis[10].Cross(A[1],B[1]);
      if(axis[10](0)==0 && axis[10](1)==0 && axis[10](2)==0)
        axis[10] = A[1];
      else
        axis[10] /= sqrt(axis[10].Dot(axis[10]));
      axis[11].Cross(A[1],B[2]);
      if(axis[11](0)==0 && axis[11](1)==0 && axis[11](2)==0)
        axis[11] = A[1];
      else
        axis[11] /= sqrt(axis[11].Dot(axis[11]));
      axis[12].Cross(A[2],B[0]);
      if(axis[12](0)==0 && axis[12](1)==0 && axis[12](2)==0)
        axis[12] = A[2];
      else
        axis[12] /= sqrt(axis[12].Dot(axis[12]));
      axis[13].Cross(A[2],B[1]);
      if(axis[13](0)==0 && axis[13](1)==0 && axis[13](2)==0)
        axis[13] = A[2];
      else
        axis[13] /= sqrt(axis[13].Dot(axis[13]));
      axis[14].Cross(A[2],B[2]);
      if(axis[14](0)==0 && axis[14](1)==0 && axis[14](2)==0)
        axis[14] = A[2];
      else
        axis[14] /= sqrt(axis[14].Dot(axis[14]));
      //--- project vertices of boxes onto separating axis
      double min_proj_a[15];
      double min_proj_b[15];
      double max_proj_a[15];
      double max_proj_b[15];
      for(i=0;i<15;++i)
      {
        min_proj_a[i] = min_proj_b[i] = 10e30;
        max_proj_a[i] = max_proj_b[i] = -10e30;
      }
      for(i=0;i<15;++i)
      {
        for(unsigned int j=0;j<8;++j)
        {
          double proj_a = a[j].Dot(axis[i]);
          double proj_b = b[j].Dot(axis[i]);
          min_proj_a[i] = ChMin(min_proj_a[i],proj_a);
          max_proj_a[i] = ChMax(max_proj_a[i],proj_a);
          min_proj_b[i] = ChMin(min_proj_b[i],proj_b);
          max_proj_b[i] = ChMax(max_proj_b[i],proj_b);
        }
        //--- test for valid separation axis if so return
        if (min_proj_a[i] > (max_proj_b[i]+envelope) ||   min_proj_b[i] > (max_proj_a[i]+envelope))
          return 0;
      }
      //--- Compute box overlaps along all 15 separating axes, and determine
      //--- minimum overlap
      double overlap[15];
      double minimum_overlap = -10e30;
      unsigned int minimum_axis = 15;
      bool flip_axis[15];
      //--- Notice that edge-edge cases are testet last, so face cases
      //--- are favored over edge-edge cases
      for(i=0;i<15;++i)
      {
        flip_axis[i] = false;
        overlap[i] = 10e30;
        if(max_proj_a[i] <= min_proj_b[i])
        {
          overlap[i] = ChMin( overlap[i], min_proj_b[i] - max_proj_a[i] );
          if(overlap[i]>minimum_overlap)
          {
            minimum_overlap = overlap[i];
            minimum_axis = i;
            flip_axis[i] = false;
          }
        }
        if(max_proj_b[i] <= min_proj_a[i])
        {
          overlap[i] = ChMin( overlap[i], min_proj_a[i] - max_proj_b[i] );
          if(overlap[i]>minimum_overlap)
          {
            minimum_overlap = overlap[i];
            minimum_axis = i;
            flip_axis[i] = true;
          }
        }
        if(min_proj_a[i] <= min_proj_b[i] &&  min_proj_b[i] <= max_proj_a[i])
        {
          overlap[i] = ChMin( overlap[i], -(max_proj_a[i] - min_proj_b[i]) );
          if(overlap[i]>minimum_overlap)
          {
            minimum_overlap = overlap[i];
            minimum_axis = i;
            flip_axis[i] = false;
          }
        }
        if(min_proj_b[i] <= min_proj_a[i] &&  min_proj_a[i] <= max_proj_b[i])
        {
          overlap[i] = ChMin(overlap[i], -(max_proj_b[i] - min_proj_a[i]) );
          if(overlap[i]>minimum_overlap)
          {
            minimum_overlap = overlap[i];
            minimum_axis = i;
            flip_axis[i] = true;
          }
        }
      }
      if(minimum_overlap>envelope)
        return 0;
      //--- Take care of normals, so they point in the correct direction.
      for(i=0;i<15;++i)
      {
        if(flip_axis[i])
          axis[i] = - axis[i];
      }
      //--- At this point we know that a projection along axis[minimum_axis] with
      //--- value minimum_overlap will lead to non-penetration of the two boxes. We
      //--- just need to generate the contact points!!!
      unsigned int corners_inside = 0;
      unsigned int corners_B_in_A = 0;
      unsigned int corners_A_in_B = 0;
      bool AinB[8];
      bool BinA[8];
      Coordsys WCStoA(p_a, R_a.Get_A_quaternion());
	  Coordsys WCStoB(p_b, R_b.Get_A_quaternion());
      Vector eps_a = ext_a + Vector(envelope,envelope,envelope);
      Vector eps_b = ext_b + Vector(envelope,envelope,envelope);
      for(i=0;i<8;++i)
      {
		Vector a_in_B = WCStoB.TransformParentToLocal(a[i]);//ChTransform<>::TransformParentToLocal(a[i], p_a, R_a);
		// = WCStoB.TransformParentToLocal(a[i]);
        Vector abs_a(fabs(a_in_B.x),fabs(a_in_B.y),fabs(a_in_B.z) ) ;
        if(abs_a <= eps_b)
        {
          ++corners_inside;
          ++corners_A_in_B;
          AinB[i] = true;
        }
        else
          AinB[i] = false;
        Vector b_in_A = WCStoA.TransformParentToLocal(b[i]);//= ChTransform<>::TransformParentToLocal(b[i], p_b, R_b);
		// = WCStoA.TransformParentToLocal(b[i]);
        Vector abs_b(fabs(b_in_A.x),fabs(b_in_A.y),fabs(b_in_A.z) );
        if(abs_b <= eps_a)
        {
          ++corners_inside;
          ++corners_B_in_A;
          BinA[i] = true;
        }
        else
          BinA[i] = false;
      }
      //--- This may indicate an edge-edge case
      if(minimum_axis >= 6)
      {
        //--- However the edge-edge case may not be the best choice,
        //--- so if we find a corner point of one box being inside
        //--- the other, we fall back to use the face case with
        //--- minimum overlap.
        if(corners_inside)//--- Actually we only need to test end-points of edge for inclusion (4 points instead of 16!!!).
        {
          minimum_overlap = -10e30;
          minimum_axis = 15;
          for(unsigned int i=0;i<6;++i)
          {
            if(overlap[i]>minimum_overlap)
            {
              minimum_overlap = overlap[i];
              minimum_axis = i;
            }
          }
        }
      }

      //--- now we can safely pick the contact normal, since we
      //--- know wheter we have a face-case or edge-edge case.
      n = axis[minimum_axis];

      //--- This is definitely an edge-edge case
      if(minimum_axis>=6)
      {
        //--- Find a point p_a on the edge from box A.
        for(unsigned int i=0;i<3;++i)
          if(n.Dot(A[i]) > 0.)
            p_a += ext_a(i)*A[i];
          else
            p_a -= ext_a(i)*A[i];
        //--- Find a point p_b on the edge from box B.
        for(int ci=0;ci<3;++ci)
          if(n.Dot(B[ci]) < 0.)
            p_b += ext_b(ci)*B[ci];
          else
            p_b -= ext_b(ci)*B[ci];

        //--- Determine the indices of two unit edge direction vectors (columns
        //--- of rotation matrices in WCS).
        int columnA = ((minimum_axis)-6)/3;
        int columnB = ((minimum_axis)-6)%3;
        double s,t;
        //--- Compute the edge-paramter values s and t corresponding to the closest
        //--- points between the two infinite lines parallel to the two edges.
        ClosestPointsBetweenLines()(p_a,A[columnA],p_b,B[columnB],s,t);
        //--- Use the edge parameter values to compute the closest
        //--- points between the two edges.
        p_a += A[columnA]*s;
        p_b += B[columnB]*t;
        //--- Let the contact point be given by the mean of the closest points.
        p[0] = (p_a + p_b)*.5;
        distances[0] = overlap[minimum_axis];
        return 1;
      }
      //--- This is a face-``something else'' case, we actually already have taken
      //--- care of all corner points, but there might be some edge-edge crossings
      //--- generating contact points



      //--- Make sure that we work in the frame of the box that defines the contact
      //--- normal. This coordinate frame is nice, because the contact-face is a axis
      //--- aligned rectangle. We will refer to this frame as the reference frame, and
      //--- use the letter 'r' or 'R' for it. The other box is named the incident box,
      //--- its closest face towards the reference face is called the incidient face, and
      //--- is denoted by the letter 'i' or 'I'.
      Vector * R_r,* R_i;  //--- Box direction vectors in WCS
      Vector ext_r,ext_i;          //--- Box extents
      Vector p_r,p_i;              //--- Box centers in WCS
      bool * incident_inside;    //--- corner inside state of incident box.
      if (minimum_axis  < 3)
      {
        //--- This means that box A is defining the reference frame
        R_r = A;
        R_i = B;
        p_r = p_a;
        p_i = p_b;
        ext_r = ext_a;
        ext_i = ext_b;
        incident_inside = BinA;
      }
      else
      {
        //--- This means that box B is defining the reference frame
        R_r = B;
        R_i = A;
        p_r = p_b;
        p_i = p_a;
        ext_r = ext_b;
        ext_i = ext_a;
        incident_inside = AinB;
      }
      //--- Following vectors are used for computing the corner points of the incident
      //--- face. At first they are used to determine the axis of the incidient box
      //--- pointing towards the reference box.
      //---
      //--- n_r_wcs = normal pointing away from reference frame in WCS coordinates.
      //--- n_r = normal vector of reference face dotted with axes of incident box.
      //--- abs_n_r = absolute values of n_r.
      Vector n_r_wcs,n_r,abs_n_r;
      if (minimum_axis < 3)
      {
        n_r_wcs = n;
      }
      else
      {
        n_r_wcs = -n;
      }

      //--- Each of these is a measure for how much the axis' of the incident box
      //--- points in the direction of n_r_wcs. The largest absolute value give
      //--- us the axis along which we will find the closest face towards the reference
      //--- box. The sign will tell us if we should take the positive or negative
      //--- face to get the closest incident face.
      n_r(0) = R_i[0].Dot(n_r_wcs);
      n_r(1) = R_i[1].Dot(n_r_wcs);
      n_r(2) = R_i[2].Dot(n_r_wcs);
      abs_n_r(0) = fabs (n_r(0));
      abs_n_r(1) = fabs (n_r(1));
      abs_n_r(2) = fabs (n_r(2));
      //--- Find the largest compontent of abs_n_r: This corresponds to the normal
      //--- for the indident face. The axis number is stored in a3. the other
      //--- axis numbers of the indicent face are stored in a1,a2.
      int a1,a2,a3;
      if (abs_n_r(1) > abs_n_r(0))
      {
        if (abs_n_r(1) > abs_n_r(2))
        {
          a1 = 2; a2 = 0; a3 = 1;
        }
        else
        {
          a1 = 0; a2 = 1; a3 = 2;
        }
      }
      else
      {
        if (abs_n_r(0) > abs_n_r(2))
        {
          a1 = 1; a2 = 2; a3 = 0;
        }
        else
        {
          a1 = 0; a2 = 1; a3 = 2;
        }
      }
      //--- Now we have information enough to determine the incidient face, that means we can
      //--- compute the center point of incident face in WCS coordinates.

      int plus_sign[3];
      Vector center_i_wcs;
      if (n_r(a3) < 0)
      {
        center_i_wcs = p_i + ext_i(a3) * R_i[a3];
        plus_sign[a3] = 1;
      }
      else
      {
        center_i_wcs = p_i - ext_i(a3) * R_i[a3];
        plus_sign[a3] = 0;
      }
      //--- Compute difference of center point of incident face with center of reference coordinates.
      Vector center_ir = center_i_wcs - p_r;
      //--- Find the normal and non-normal axis numbers of the reference box
      int code1,code2,code3;
      if (minimum_axis < 3)
        code3 = minimum_axis;  //012
      else
        code3 = minimum_axis-3;  //345
      if (code3==0)
      {
        code1 = 1;
        code2 = 2;
      }
      else if (code3==1)
      {
        code1 = 2;
        code2 = 0;
      }
      else
      {
        code1 = 0;
        code2 = 1;
      }
      //--- Find the four corners of the incident face, in reference-face coordinates
      double quad[8]; //--- 2D coordinate of incident face (stored as x,y pairs).
      bool inside[4];     //--- inside state of the four coners of the quad
      //--- Project center_ri onto reference-face coordinate system (has origo
      //--- at the center of the reference face, and the two orthogonal unit vectors
      //--- denoted by R_r[code1] and R_r[code2] spaning the face-plane).
      double c1 = R_r[code1].Dot( center_ir);
      double c2 = R_r[code2].Dot( center_ir);
      //--- Compute the projections of the axis spanning the incidient
      //--- face, onto the axis spanning the reference face.
      //---
      //--- This will allow us to determine the coordinates in the reference-face
      //--- when we step along a direction of the incident face given by either
      //--- a1 or a2.
      double m11 = R_r[code1].Dot( R_i[a1]);
      double m12 = R_r[code1].Dot( R_i[a2]);
      double m21 = R_r[code2].Dot( R_i[a1]);
      double m22 = R_r[code2].Dot( R_i[a2]);
      {
        double k1 = m11 * ext_i(a1);
        double k2 = m21 * ext_i(a1);
        double k3 = m12 * ext_i(a2);
        double k4 = m22 * ext_i(a2);

        plus_sign[a1] = 0;
        plus_sign[a2] = 0;
        unsigned int mask = ( (plus_sign[a1]<<a1) |  (plus_sign[a2]<<a2) |  (plus_sign[a3]<<a3));
        inside[0] = incident_inside[ mask ];

        quad[0] = c1 - k1 - k3;
        quad[1] = c2 - k2 - k4;

        plus_sign[a1] = 0;
        plus_sign[a2] = 1;
        mask = (plus_sign[a1]<<a1 |  plus_sign[a2]<<a2 |  plus_sign[a3]<<a3);
        inside[1] = incident_inside[ mask ];

        quad[2] = c1 - k1 + k3;
        quad[3] = c2 - k2 + k4;

        plus_sign[a1] = 1;
        plus_sign[a2] = 1;
        mask = (plus_sign[a1]<<a1 |  plus_sign[a2]<<a2 |  plus_sign[a3]<<a3);
        inside[2] = incident_inside[ mask ];

        quad[4] = c1 + k1 + k3;
        quad[5] = c2 + k2 + k4;

        plus_sign[a1] = 1;
        plus_sign[a2] = 0;
        mask = (plus_sign[a1]<<a1 |  plus_sign[a2]<<a2 |  plus_sign[a3]<<a3);
        inside[3] = incident_inside[ mask ];

        quad[6] = c1 + k1 - k3;
        quad[7] = c2 + k2 - k4;
      }
      //--- find the size of the reference face
      double rect[2];
      rect[0] = ext_r(code1);
      rect[1] = ext_r(code2);

      //--- Intersect the edges of the incident and the reference face
      double crossings[16];
      unsigned int edge_crossings = RectQuadEdgeIntersectionTest()(envelope,rect,quad,inside,crossings);
      assert(edge_crossings<=8);

      if(!corners_inside && !edge_crossings)
        return 0;

      //--- Convert the intersection points into reference-face coordinates,
      //--- and compute the contact position and depth for each point.
      double det1 = 1./(m11*m22 - m12*m21);
      m11 *= det1;
      m12 *= det1;
      m21 *= det1;
      m22 *= det1;

      for (unsigned int j=0; j < edge_crossings; ++j)
      {
        //--- Get coordinates of edge-edge crossing point in reference face coordinate system.
        double p0 = crossings[j*2] - c1;
        double p1 = crossings[j*2+1] - c2;
        //--- Compute intersection point in (almost) WCS. Actually we have
        //--- displaced origin to center of reference frame box
        double k1 =  m22*p0 - m12*p1;
        double k2 = -m21*p0 + m11*p1;
        Vector point = center_ir + k1*R_i[a1] + k2*R_i[a2];
        //--- Depth of intersection point
        double depth = n_r_wcs.Dot(point) - ext_r(code3);
        if(depth<envelope)
        {
          p[cnt] = point + p_r;//--- Move origin from center of reference frame box to WCS
          distances[cnt] = depth;
          ++cnt;
        }
      }
      //      assert((corners_inside + cnt)<=8);//--- If not we are in serious trouble!!!
      //--- I think there is a special case, if corners_inside = 8 and
      //--- corners_in_A = 4 and corners_in_B = 4, then there really
      //--- can only be 4 contacts???

      if(corners_inside)
      {
        unsigned int start_corner_A = cnt;
        unsigned int end_corner_A = cnt;

        //--- Compute Displacement of contact plane from origin of WCS, the
        //--- contact plane is equal to the face plane of the reference box
        double w =   ext_r(code3) +  n_r_wcs.Dot(p_r);

        if(corners_A_in_B)
        {
          for (unsigned int i=0; i < 8; ++i)
          {
            if(AinB[i])
            {
              Vector point = a[i];
              double depth = n_r_wcs.Dot(point) - w;
              if(depth<envelope)
              {
                p[cnt] = point;
                distances[cnt] = depth;
                ++cnt;
              }
            }
          }
          end_corner_A = cnt;
        }
        if(corners_B_in_A)
        {
          for (unsigned int i=0; i < 8; ++i)
          {
            if(BinA[i])
            {
              Vector point = b[i];
              bool redundant = false;
              for(unsigned int j=start_corner_A;j<end_corner_A;++j)
              {
                if( p[j].Equals(point,envelope) )
                {
                  redundant = true;
                  break;
                }
              }
              if(redundant)
                continue;
              double depth = n_r_wcs.Dot(point) - w;
              if(depth<envelope)
              {
                p[cnt] = point;
                distances[cnt] = depth;
                ++cnt;
              }
            }
          }
        }
      }
      //      assert(cnt<=8);//--- If not we are in serious trouble!!!
      return cnt;
    };