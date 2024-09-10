int RenderContext::stringToBlendContant(String fun, int vlDefault)
{
    //normalize
    fun.replaceAll(" ","");
    fun=fun.toUpper();
    //
    if(fun=="ONE") return GL_ONE;
    if(fun=="ZERO") return GL_ZERO;
    //
    if(fun=="ONE::MINUS::DST::COLOR") return GL_ONE_MINUS_DST_COLOR;
    if(fun=="ONE::MINUS::DST::ALPHA") return GL_ONE_MINUS_DST_ALPHA;
    if(fun=="ONE::MINUS::SRC::COLOR") return GL_ONE_MINUS_SRC_COLOR;
    if(fun=="ONE::MINUS::SRC::ALPHA") return GL_ONE_MINUS_SRC_ALPHA;
    //
    if(fun=="DST::COLOR") return GL_DST_COLOR;
    if(fun=="DST::ALPHA") return GL_DST_ALPHA;
    //
    if(fun=="SRC::COLOR") return GL_SRC_COLOR;
    if(fun=="SRC::ALPHA") return GL_SRC_ALPHA;
    if(fun=="SRC::ALPHA::SATURATE") return GL_SRC_ALPHA_SATURATE;
    
    return vlDefault;
}