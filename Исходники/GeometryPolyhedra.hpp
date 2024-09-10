      bool
      Compute(const std::vector< Matrix<T,3,1> >& egV, method_t method_type = METHOD_BRUTE_FORCE, bool flag_check_euler = true)
      {
        ////////////////////////////////////////////////////////////////////////
        // clear all data
        ClearAll();
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Test for error
        if(egV.size() < 4) return(false);
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Fill in V
        V = egV;
        size_t nV = egV.size();
        //
        ////////////////////////////////////////////////////////////////////////

#ifdef PROMTS_USE_BULLET
        ////////////////////////////////////////////////////////////////////////
        // Compute 3D convex hull - BULLET Implementation
        if(method_type == METHOD_BULLET)
        {
          btAlignedObjectArray<btVector3> btV;
          btV.resize(egV.size());
          for(size_t i=0; i<egV.size(); i++)
            btV[i] = btVector3(egV[i].x(), egV[i].y(), egV[i].z());
          convexUtil.compute(&btV[0].getX(), sizeof(btVector3), btV.size(), 0, 0);
          for(int i=0; i<convexUtil.vertices.size(); i++)
            V[i] = Matrix<T,3,1>(convexUtil.vertices[i].getX(),convexUtil.vertices[i].getY(),convexUtil.vertices[i].getZ());
        }
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Fill in F
        if(method_type == METHOD_BULLET)
        {
          F.resize(convexUtil.faces.size());
          for(int f=0;f<convexUtil.faces.size();f++)
          {
            int face = convexUtil.faces[f];
            const btConvexHullComputer::Edge*  firstEdge = &convexUtil.edges[face];
            const btConvexHullComputer::Edge*  edge = firstEdge;

            do{
              int src  = edge->getSourceVertex();
              F[f].Idx.push_back(src);
              edge = edge->getNextEdgeOfFace();

            }while (edge!=firstEdge);

            if(F[f].Idx.size() < 3) return(false);

            std::vector< Matrix<T,3,1> > vf(F[f].Idx.size());
            for(size_t k=0; k<F[f].Idx.size(); k++) vf[k] = V[ F[f].Idx[k] ];
            F[f].cm = PolygonCentroid3D(vf);

            Matrix<T,3,1> e1 = V[F[f].Idx[1]] - V[F[f].Idx[0]];
            Matrix<T,3,1> e2 = V[F[f].Idx[2]] - V[F[f].Idx[0]];
            Matrix<T,3,1> nf = e2.cross(e1);
            T magf = nf.stableNorm();
            for(size_t i=3; i<F[f].Idx.size(); i++)
            {
              e2 = V[F[f].Idx[i]] - V[F[f].Idx[0]];
              Matrix<T,3,1> n = e2.cross(e1);
              T mag = n.stableNorm();
              if(magf<mag){ magf = mag; nf = n;}
            }
            F[f].normal = nf.normalized();
            F[f].endp = F[f].cm + F[f].normal;
          }
        }
        //
        ////////////////////////////////////////////////////////////////////////
#endif
        ////////////////////////////////////////////////////////////////////////
        // Compute 3D convex hull - BRUTE FORCE
        if(method_type == METHOD_BRUTE_FORCE)
        {
          std::vector<bool> cnr(nV);
          std::vector<unsigned int> pIdx;
          std::fill(cnr.begin() + nV - 3, cnr.end(), true);
          do
          {
            // Selecting 3 vertices from nv vertices
            for (unsigned int i = 0; i < nV; ++i)
            {
              if (cnr[i])
              {
                pIdx.push_back(i);
                if(pIdx.size() == 3) break;
              }
            }

            // Compute the distance of the other points to the plane that is identified by the three points
            Matrix<T,3,1> n = (V[pIdx[0]]-V[pIdx[1]]).cross(V[pIdx[2]]-V[pIdx[1]]);
            n.normalize();
            unsigned int neg_counter(0), pos_counter(0);
            std::vector<unsigned int> zeros;
            for(unsigned int i=0; i<nV; i++)
            {
              if(i==pIdx[0] || i==pIdx[1] || i==pIdx[2]) continue;
              T d = n.dot(V[i]-V[pIdx[1]]);
              if( d >= (T) 1e-3 ) pos_counter++;
              else if( d <= (T) -1e-3 ) neg_counter++;
              else zeros.push_back(i);
              if(pos_counter != 0 && neg_counter != 0) break;
            }

            // Test if all the other point remain on or in one side of the palne?
            if(pos_counter == 0 || neg_counter == 0) // THIS IS A FACE!
            {
              // First check if the plane is already identified by an face
              bool found = false;
              for(unsigned int i=0; i<F.size(); i++)
              {
                bool found0 = false, found1 = false, found2 = false;
                for(unsigned int j=0; j<F[i].Idx.size(); j++)
                  if(F[i].Idx[j] == pIdx[0]) found0 = true;
                  else if(F[i].Idx[j] == pIdx[1]) found1 = true;
                  else if(F[i].Idx[j] == pIdx[2]) found2 = true;
                if(found0 && found1 && found2) {found = true; break;}
              }
              // If the plane is not identified by so far detected faces, then add this new face
              if(not found)
              {
                pIdx.insert(pIdx.end(), zeros.begin(), zeros.end());
                std::vector< Matrix<T,3,1> > fv(pIdx.size());
                for(unsigned int i=0; i<fv.size(); i++) fv[i] = V[pIdx[i]];
                OrderVertices(fv, pIdx);
                Face<T> face;
                face.Idx = pIdx;
                F.push_back(face);
              }
            }
            pIdx.clear();
          } while (std::next_permutation(cnr.begin(), cnr.end()));
          // Fill in the center of mass, normal and end point of each face
          for(size_t f=0; f<F.size(); f++)
          {
            // Check for error
            if(F[f].Idx.size() < 3) {ClearAll(); return(false);}
            // Compute center of mass of the f-th face
            std::vector< Matrix<T,3,1> > vf(F[f].Idx.size());
            for(size_t k=0; k<F[f].Idx.size(); k++) vf[k] = V[ F[f].Idx[k] ];
            F[f].cm = PolygonCentroid3D(vf);
            // Compute normal vector of f-th face
            Matrix<T,3,1> e1 = V[F[f].Idx[1]] - V[F[f].Idx[0]];
            Matrix<T,3,1> e2 = V[F[f].Idx[2]] - V[F[f].Idx[0]];
            Matrix<T,3,1> nf = e2.cross(e1);
            T magf = nf.stableNorm();
            for(size_t i=3; i<F[f].Idx.size(); i++)
            {
              e2 = V[F[f].Idx[i]] - V[F[f].Idx[0]];
              Matrix<T,3,1> n = e2.cross(e1);
              T mag = n.stableNorm();
              if(magf<mag){ magf = mag; nf = n;}
            }
            F[f].normal = nf.normalized();
            // Compute end point of f-th face
            F[f].endp = F[f].cm + F[f].normal;
          }
        }
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Fill in E
        Edge<T> eTemp;
        size_t vN = F[0].Idx.size();

        for(size_t v=0; v<vN; v++)
        {
          eTemp.i = F[0].Idx[v];
          eTemp.j = F[0].Idx[(v+1)%vN];
          eTemp.u = V[eTemp.j]-V[eTemp.i];
          eTemp.u.normalize();
          eTemp.endp = V[eTemp.i] + eTemp.u;
          E.push_back(eTemp);
        }

        for(size_t f=1; f<F.size(); f++)
        {
          vN = F[f].Idx.size();
          for(size_t v=0; v<vN; v++)
          {
            eTemp.i = F[f].Idx[v];
            eTemp.j = F[f].Idx[(v+1)%vN];

            bool found = false;
            for(size_t e=0; e<E.size(); e++)
            {
              if( (eTemp.i == E[e].i && eTemp.j == E[e].j) || (eTemp.i == E[e].j && eTemp.j == E[e].i) )
              {
                found = true;
                break;
              }
            }
            if(not found)
            {
              eTemp.u = V[eTemp.j]-V[eTemp.i];
              eTemp.u.normalize();
              eTemp.endp = V[eTemp.i] + eTemp.u;
              E.push_back(eTemp);
            }
          }
        }
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Fill in uF (Unique Faces)
        uF.push_back(0);
        for(size_t i=1; i<F.size(); i++)
        {
          bool found = false;
          for(size_t j=0; j<uF.size(); j++)
          {
            if( fabs( (T)1.0 - F[i].normal.dot(F[uF[j]].normal) ) < epsil )
            {
              found = true;
              break;
            }
          }
          if(not found) uF.push_back(i);
        }
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Fill in uE (Unique Edges)
        uE.push_back(0);
        for(size_t i=1; i<E.size(); i++)
        {
          bool found = false;
          for(size_t j=0; j<uE.size(); j++)
          {
            if( fabs( (T)1.0 - E[i].u.dot(E[uE[j]].u) ) < epsil )
            {
              found = true;
              break;
            }
          }
          if(not found) uE.push_back(i);
        }
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Center of mass of the polyhedron
        C = Matrix<T,3,1>::Zero();
        if(F.empty()) {ClearAll(); return(false);}
        unsigned int vi = F[0].Idx[0];
        std::vector<unsigned int> ftri;
        for(unsigned int i=1; i<F.size(); i++)
        {
          bool found = false;
          for(unsigned int j=0; j<F[i].Idx.size(); j++)
          {
            if(F[i].Idx[j] == vi)
            {
              found = true;
              break;
            }
          }
          if(not found)
            ftri.push_back(i);
        }
        T total_vol = T(0);
        for(unsigned int i=0; i<ftri.size(); i++)
        {
          for(unsigned int j=1; j<F[ftri[i]].Idx.size()-1; j++)
          {
            T vol = T(0);
            Matrix<T,3,1> cm;
            cm  = TetrahedronCentroid(V[vi], V[F[ftri[i]].Idx[0]], V[F[ftri[i]].Idx[j]], V[F[ftri[i]].Idx[j+1]]);
            vol = TetrahedronVolume(V[vi], V[F[ftri[i]].Idx[0]], V[F[ftri[i]].Idx[j]], V[F[ftri[i]].Idx[j+1]]);
            C += vol*cm;
            total_vol += vol;
          }
        }
        C /= total_vol;
        volume = total_vol;
        //
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // make a back up
        V_ = V;
        E_ = E;
        F_ = F;
        C_ = C;
        //
        ////////////////////////////////////////////////////////////////////////

        return(true);
      }