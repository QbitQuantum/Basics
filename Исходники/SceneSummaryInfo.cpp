void SSceneSummary::STextureInfo::Export	(IWriter* F, u32& mem_use)
{
	string128		mask;
	AnsiString		tmp;
    strcpy			(mask,"%s=%s,%d,%d,%s,%d,%3.2f,%3.2f,%s");
    if (info.flags.is_any(STextureParams::flDiffuseDetail|STextureParams::flBumpDetail)){
        if (0!=info.detail_name.size()){
        	strcat	(mask,",%s,%3.2f");
        }
    }
    if (info.bump_mode==STextureParams::tbmUse){
        if (0!=info.bump_name.size()){
        	strcat	(mask,",%s");
        }
    }
    AnsiString 		tmp2;
    for (objinf_map_it o_it=objects.begin(); o_it!=objects.end(); o_it++){
        tmp2 		+= AnsiString().sprintf("%s%s[%d*%3.2f]",tmp2.Length()?"; ":"",o_it->first.c_str(),o_it->second.ref_count,o_it->second.area);
    }
    int tex_mem		= info.MemoryUsage(*file_name);
    mem_use			+=tex_mem;
    tmp.sprintf		(mask,*file_name,info.FormatString(),
    				info.width,info.height,info.HasAlpha()?"present":"absent",
                    iFloor(tex_mem/1024),
                    effective_area, _sqrt((pixel_area*info.width*info.height)/effective_area), tmp2.c_str(), 
                    *info.detail_name, info.detail_scale, *info.bump_name);
	F->w_string		(tmp.c_str());
}