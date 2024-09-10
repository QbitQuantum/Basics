//--------------------------------------------------------------------
void 	PDomain::Render		(u32 clr, const Fmatrix& parent)
{
	if (!flags.is(flRenderable)) return;
	u32 clr_s = subst_alpha	(clr,0x60);
	u32 clr_w = subst_alpha	(clr,0xff);
    RCache.set_xform_world	(parent);
	switch(type){
    case PDPoint: 	
		EDevice.SetShader	(EDevice.m_WireShader);
    	DU_impl.DrawCross		(v[0], 0.05f,0.05f,0.05f, 0.05f,0.05f,0.05f, clr_w);
    break;
	case PDLine:
		EDevice.SetShader	(EDevice.m_WireShader);
    	DU_impl.DrawCross		(v[0], 0.05f,0.05f,0.05f, 0.05f,0.05f,0.05f, clr_w);
	  	DU_impl.DrawCross		(v[1], 0.05f,0.05f,0.05f, 0.05f,0.05f,0.05f, clr_w);
    	DU_impl.DrawLine 		(v[0], v[1], clr_w);
    break;
    case PDTriangle:
		EDevice.SetShader	(EDevice.m_SelectionShader);
        DU_impl.DrawFace			(v[0], v[1], v[2], clr_s, clr_w, true, true);
    break;
	case PDPlane:{
		EDevice.SetShader	(EDevice.m_SelectionShader);
        Fvector2 sz			= {100.f,100.f};
        DU_impl.DrawPlane		(v[0],v[1],sz,clr_s,clr_w,true,true,true);
    }break;
	case PDBox:
		EDevice.SetShader	(EDevice.m_SelectionShader);
    	DU_impl.DrawAABB			(v[0], v[1], clr_s, clr_w, true, true);
    break;
	case PDSphere:
    	DU_impl.DrawSphere		(parent, v[0], f[4], clr_s, clr_w, true, true);
    	DU_impl.DrawSphere		(parent, v[0], f[3], clr_s, clr_w, true, true);
    break;
	case PDCylinder:{
    	Fvector c,d;
        float h 			= d.sub(v[1],v[0]).magnitude();
        c.add 				(v[0],v[1]).div(2.f);
        if (!fis_zero(h)){
        	d.div			(h);
			DU_impl.DrawCylinder	(parent, c, d, h, f[6], clr_s, clr_w, true, true);
			DU_impl.DrawCylinder	(parent, c, d, h, f[7], clr_s, clr_w, true, true);
        }
    }break;
	case PDCone:{
    	Fvector d;
        float h 			= d.sub(v[1],v[0]).magnitude();
        if (!fis_zero(h)){
            d.div			(h);
            DU_impl.DrawCone		(parent, v[0], d, h, f[6], clr_s, clr_w, true, true);
            DU_impl.DrawCone		(parent, v[0], d, h, f[7], clr_s, clr_w, true, true);
        }
    }break;
	case PDBlob:
		EDevice.SetShader	(EDevice.m_WireShader);
    	DU_impl.DrawCross		(v[0], f[3],f[3],f[3], f[3],f[3],f[3], clr);
    break;
	case PDDisc:
        DU_impl.DrawCylinder		(parent, v[0], v[1], 0.f, f[6], clr_s, clr_w, true, true);
        DU_impl.DrawCylinder		(parent, v[0], v[1], 0.f, f[7], clr_s, clr_w, true, true);
    break;
	case PDRectangle:
        DU_impl.DrawRectangle	(v[0], v[1], v[2], clr_s, clr_w, true, true);
    break;
   }
}