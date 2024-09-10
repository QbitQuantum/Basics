// ------------------------------------------------------------------------------------------------
void ProcessParametrizedProfile(const IfcParameterizedProfileDef& def, TempMesh& meshout, ConversionData& conv)
{
	if(const IfcRectangleProfileDef* const cprofile = def.ToPtr<IfcRectangleProfileDef>()) {
		const IfcFloat x = cprofile->XDim*0.5f, y = cprofile->YDim*0.5f;

		meshout.verts.reserve(meshout.verts.size()+4);
		meshout.verts.push_back( IfcVector3( x, y, 0.f ));
		meshout.verts.push_back( IfcVector3(-x, y, 0.f ));
		meshout.verts.push_back( IfcVector3(-x,-y, 0.f ));
		meshout.verts.push_back( IfcVector3( x,-y, 0.f ));
		meshout.vertcnt.push_back(4);
	}
	else if( const IfcCircleProfileDef* const circle = def.ToPtr<IfcCircleProfileDef>()) {
		if( const IfcCircleHollowProfileDef* const hollow = def.ToPtr<IfcCircleHollowProfileDef>()) {
			// TODO
		}
		const size_t segments = 32;
		const IfcFloat delta = AI_MATH_TWO_PI_F/segments, radius = circle->Radius;

		meshout.verts.reserve(segments);

		IfcFloat angle = 0.f;
		for(size_t i = 0; i < segments; ++i, angle += delta) {
			meshout.verts.push_back( IfcVector3( ::cos(angle)*radius, ::sin(angle)*radius, 0.f ));
		}

		meshout.vertcnt.push_back(segments);
	}
	else {
		IFCImporter::LogWarn("skipping unknown IfcParameterizedProfileDef entity, type is " + def.GetClassName());
		return;
	}

	IfcMatrix4 trafo;
	ConvertAxisPlacement(trafo, *def.Position);
	meshout.Transform(trafo);
}