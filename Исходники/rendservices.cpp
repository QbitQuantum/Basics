bool
RendererServices::get_inverse_matrix (ShaderGlobals *sg, Matrix44 &result,
                                      ustring to)
{
    bool ok = get_matrix (sg, result, to);
    if (ok)
        result.invert ();
    return ok;
}