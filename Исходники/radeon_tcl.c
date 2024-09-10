/**
 * Compute per-vertex fog blend factors from fog coordinates by
 * evaluating the GL_LINEAR, GL_EXP or GL_EXP2 fog function.
 * Fog coordinates are distances from the eye (typically between the
 * near and far clip plane distances).
 * Note the fog (eye Z) coords may be negative so we use ABS(z) below.
 * Fog blend factors are in the range [0,1].
 */
float
radeonComputeFogBlendFactor( struct gl_context *ctx, GLfloat fogcoord )
{
    GLfloat end  = ctx->Fog.End;
    GLfloat d, temp;
    const GLfloat z = FABSF(fogcoord);

    switch (ctx->Fog.Mode) {
    case GL_LINEAR:
        if (ctx->Fog.Start == ctx->Fog.End)
            d = 1.0F;
        else
            d = 1.0F / (ctx->Fog.End - ctx->Fog.Start);
        temp = (end - z) * d;
        return CLAMP(temp, 0.0F, 1.0F);
        break;
    case GL_EXP:
        d = ctx->Fog.Density;
        NEG_EXP( temp, d * z );
        return temp;
        break;
    case GL_EXP2:
        d = ctx->Fog.Density*ctx->Fog.Density;
        NEG_EXP( temp, d * z * z );
        return temp;
        break;
    default:
        _mesa_problem(ctx, "Bad fog mode in make_fog_coord");
        return 0;
    }
}