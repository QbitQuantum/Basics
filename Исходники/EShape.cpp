bool CEditShape::RayPick(float& distance, const Fvector& start, const Fvector& direction, SRayPickInfo* pinf)
{
    float dist					= distance;

	for (ShapeIt it=shapes.begin(); it!=shapes.end(); it++){
		switch (it->type){
		case cfSphere:{
            Fvector S,D;
            Fmatrix M;
            M.invert			(FTransformR);
            M.transform_dir		(D,direction);
            FITransform.transform_tiny(S,start);
            Fsphere&	T		= it->data.sphere;
            float bk_r = T.R;
//            T.R					= FScale.x;
            T.intersect			(S,D,dist);
            if (dist<=0.f)		dist = distance;

            T.R					= bk_r;
		}break;
		case cfBox:{
        	Fbox box;
            box.identity		();
            Fmatrix BI;
            BI.invert			(it->data.box);
		    Fvector S,D,S1,D1,P;
		    FITransform.transform_tiny	(S,start);
		    FITransform.transform_dir	(D,direction);
		    BI.transform_tiny			(S1,S);
		    BI.transform_dir			(D1,D);
            Fbox::ERP_Result	rp_res 	= box.Pick2(S1,D1,P);
            if (rp_res==Fbox::rpOriginOutside){
            	it->data.box.transform_tiny	(P);
                FTransform.transform_tiny	(P);
                P.sub			(start);
                dist			= P.magnitude();
            }
		}break;
		}
    }
    if (dist<distance){
        distance	= dist;
        return 		true;
    }
	return false;
}