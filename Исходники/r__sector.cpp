void CPortal::OnRender	()
{
	if (psDeviceFlags.is(rsOcclusionDraw)){
		VERIFY				(poly.size());
		// draw rect
		using LVec = xr_vector<FVF::L>;
		using LVecIt = LVec::iterator;
		static LVec	V;		V.resize(poly.size()+2);
		Fvector C			= {0,0,0};
		for (u32 k=0; k<poly.size(); k++){ C.add(poly[k]); V[k+1].set(poly[k],0x800000FF);}
		V.back().set		(poly[0],0x800000FF);
		C.div				((float)poly.size());
		V[0].set			(C,0x800000FF);

		RCache.set_xform_world(Fidentity);
		// draw solid
		RCache.set_Shader	(dxRenderDeviceRender::Instance().m_SelectionShader);
		RCache.dbg_Draw		(D3DPT_TRIANGLEFAN,&*V.begin(),V.size()-2);

		// draw wire
		if (bDebug){
			RImplementation.rmNear();
		}else{
			Device.SetNearer(TRUE);
		}
		RCache.set_Shader	(dxRenderDeviceRender::Instance().m_WireShader);
		RCache.dbg_Draw		(D3DPT_LINESTRIP,&*(V.begin()+1),V.size()-2);
		if (bDebug){
			RImplementation.rmNormal();
		}else{
			Device.SetNearer(FALSE);
		}
	}
}