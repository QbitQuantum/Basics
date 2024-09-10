// ------------------------------------------------------------------------------------------------
void ProcessRevolvedAreaSolid(const IfcRevolvedAreaSolid& solid, TempMesh& result, ConversionData& conv)
{
    TempMesh meshout;

    // first read the profile description
    if(!ProcessProfile(*solid.SweptArea,meshout,conv) || meshout.verts.size()<=1) {
        return;
    }

    IfcVector3 axis, pos;
    ConvertAxisPlacement(axis,pos,solid.Axis);

    IfcMatrix4 tb0,tb1;
    IfcMatrix4::Translation(pos,tb0);
    IfcMatrix4::Translation(-pos,tb1);

    const std::vector<IfcVector3>& in = meshout.verts;
    const size_t size=in.size();

    bool has_area = solid.SweptArea->ProfileType == "AREA" && size>2;
    const IfcFloat max_angle = solid.Angle*conv.angle_scale;
    if(std::fabs(max_angle) < 1e-3) {
        if(has_area) {
            result = meshout;
        }
        return;
    }

    const unsigned int cnt_segments = std::max(2u,static_cast<unsigned int>(16 * std::fabs(max_angle)/AI_MATH_HALF_PI_F));
    const IfcFloat delta = max_angle/cnt_segments;

    has_area = has_area && std::fabs(max_angle) < AI_MATH_TWO_PI_F*0.99;

    result.verts.reserve(size*((cnt_segments+1)*4+(has_area?2:0)));
    result.vertcnt.reserve(size*cnt_segments+2);

    IfcMatrix4 rot;
    rot = tb0 * IfcMatrix4::Rotation(delta,axis,rot) * tb1;

    size_t base = 0;
    std::vector<IfcVector3>& out = result.verts;

    // dummy data to simplify later processing
    for(size_t i = 0; i < size; ++i) {
        out.insert(out.end(),4,in[i]);
    }

    for(unsigned int seg = 0; seg < cnt_segments; ++seg) {
        for(size_t i = 0; i < size; ++i) {
            const size_t next = (i+1)%size;

            result.vertcnt.push_back(4);
            const IfcVector3& base_0 = out[base+i*4+3],base_1 = out[base+next*4+3];

            out.push_back(base_0);
            out.push_back(base_1);
            out.push_back(rot*base_1);
            out.push_back(rot*base_0);
        }
        base += size*4;
    }

    out.erase(out.begin(),out.begin()+size*4);

    if(has_area) {
        // leave the triangulation of the profile area to the ear cutting
        // implementation in aiProcess_Triangulate - for now we just
        // feed in two huge polygons.
        base -= size*8;
        for(size_t i = size; i--; ) {
            out.push_back(out[base+i*4+3]);
        }
        for(size_t i = 0; i < size; ++i ) {
            out.push_back(out[i*4]);
        }
        result.vertcnt.push_back(size);
        result.vertcnt.push_back(size);
    }

    IfcMatrix4 trafo;
    ConvertAxisPlacement(trafo, solid.Position);

    result.Transform(trafo);
    IFCImporter::LogDebug("generate mesh procedurally by radial extrusion (IfcRevolvedAreaSolid)");
}