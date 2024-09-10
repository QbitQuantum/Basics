 void _computeForceRaw(Real3D& force1,
                       Real3D& force2,
                       Real3D& force3,
                       Real3D& force4,
                       const Real3D& r21,
                       const Real3D& r32,
                       const Real3D& r43, const real _phi0) const {
   
   Real3D retF[4];
   
   Real3D rijjk = r21.cross(r32); // [r21 x r32]
   Real3D rjkkn = r32.cross(r43); // [r32 x r43]
   
   real rijjk_sqr = rijjk.sqr();
   real rjkkn_sqr = rjkkn.sqr();
   
   real rijjk_abs = sqrt(rijjk_sqr);
   real rjkkn_abs = sqrt(rjkkn_sqr);
   
   real inv_rijjk = 1.0 / rijjk_abs;
   real inv_rjkkn = 1.0 / rjkkn_abs;
   
   // cosine between planes
   real cos_phi = (rijjk * rjkkn) * (inv_rijjk * inv_rjkkn);
   if (cos_phi > 1.0) cos_phi = 1.0;
   else if (cos_phi < -1.0) cos_phi = -1.0;
   
   real coef1 = (-2.0) * K * (cos_phi - cos(_phi0));
   
   real A1 = inv_rijjk * inv_rjkkn;
   real A2 = inv_rijjk * inv_rijjk;
   real A3 = inv_rjkkn * inv_rjkkn;
   
   Real3D p3232 ( prod(r32,r32) );
   Real3D p3243 ( prod(r32,r43) );
   Real3D p2132 ( prod(r21,r32) );
   Real3D p2143 ( prod(r21,r43) );
   Real3D p2121 ( prod(r21,r21) );
   Real3D p4343 ( prod(r43,r43) );
   
   // we have 4 particles 1,2,3,4
   for(int l=0; l<4; l++){
     Real3D B1, B2, B3;
     
     for(int i=0; i<3; i++){
       B1[i]= r21[i] * ( p3232[i] * (d(l,2)-d(l,3)) + p3243[i] * (d(l,2)-d(l,1)) ) +
              r32[i] * ( p2132[i] * (d(l,3)-d(l,2)) + p3243[i] * (d(l,1)-d(l,0)) ) +
              r43[i] * ( p2132[i] * (d(l,2)-d(l,1)) + p3232[i] * (d(l,0)-d(l,1)) ) +
              2.0 * r32[i] * p2143[i] * (d(l,1)-d(l,2));
     
       B2[i]= 2.0 * r21[i] * ( p3232[i] * (d(l,1)-d(l,0)) + p2132[i] * (d(l,1)-d(l,2)) ) +
              2.0 * r32[i] * ( p2121[i] * (d(l,2)-d(l,1)) + p2132[i] * (d(l,0)-d(l,1)));
     
       B3[i]= 2.0 * r43[i] * ( p3232[i] * (d(l,3)-d(l,2)) + p3243[i] * (d(l,1)-d(l,2)) ) +
              2.0 * r32[i] * ( p4343[i] * (d(l,2)-d(l,1)) + p3243[i] * (d(l,2)-d(l,3)));
     }
     
     retF[l] = coef1 * ( A1*B1 - 0.5*cos_phi*(A2*B2 + A3*B3) );
   }
   
   force1 = retF[0];
   force2 = retF[1];
   force3 = retF[2];
   force4 = retF[3];
 }