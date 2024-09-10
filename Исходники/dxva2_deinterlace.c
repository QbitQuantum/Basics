static void FillSample( DXVA2_VideoSample *p_sample,
                        const struct deinterlace_ctx *p_context,
                        picture_t *p_pic,
                        const video_format_t *p_fmt,
                        const RECT *p_area,
                        int i_field )
{
    picture_sys_t *p_sys_src = ActivePictureSys(p_pic);

    p_sample->SrcSurface = p_sys_src->surface;
    p_sample->SampleFormat.SampleFormat = p_pic->b_top_field_first ?
                DXVA2_SampleFieldInterleavedEvenFirst :
                DXVA2_SampleFieldInterleavedOddFirst;
    p_sample->Start = 0;
    p_sample->End = GetFieldDuration(p_context, p_fmt, p_pic) * 10;
    p_sample->SampleData = DXVA2_SampleData_RFF_TFF_Present;
    if (!i_field)
        p_sample->SampleData |= DXVA2_SampleData_TFF;
    else
        p_sample->SampleData |= DXVA2_SampleData_RFF;
    p_sample->DstRect = p_sample->SrcRect = *p_area;
    p_sample->PlanarAlpha    = DXVA2_Fixed32OpaqueAlpha();
}