/*---------------------------------------------------------------------------
   Class specific setup function for the effects assets.
  ---------------------------------------------------------------------------*/
void FilterSolids::Assets(Buffers &Buffer)
   {
   if (!Ready()) {return;}

   vector2u Res = Buffer.GetDepthResolution();
   Depth.Create(Res, Buffer.GetDepthDataType());
   Depth.ClearData();
   Depth.Buffer(false);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glPushMatrix();
   Light.SetPosition(vector4f(0.5f, -0.5f, Near + 1.0f, 0.0f));
   Light.Buffer(0);
   glPopMatrix();

   Grid = Res / GridDiv;
   Grid = Grid.Clamp(GridMin, GridMax);
   GridNorm = cast_vector2(float, Grid);
   GridNorm = GridNorm.Rcp();
   uint GridSmallest = Math::Min(Grid.U, Grid.V);

   Offset = cast_vector2(float, Grid);
   Offset = (Offset - 1.0f) * 0.5f;

   //Geometry subdivisions for curved solids
   uint PolyDiv = (Math::Min(Res.U, Res.V) / GridSmallest) / PolyDivPixels;
   PolyDiv = Math::Clamp(PolyDiv, PolyDivMin, PolyDivMax);

   File::Text Text;
   std::string CodeVert, CodeFrag;

   switch (Type)
      {
      case FilterSolids::Cubes :
         Model.Cube(1, Mesh::ModeSolid);
         Text.Load(CodeVert, File::Path::Shader(File::FilterSolidsDepthVert));
         EnableVideo = false;
         EnableDepth = true;
         EnableCal = false;
         Mat.SetShininess(0.0f);
         break;

      case FilterSolids::Spheres :
         Model.Sphere(PolyDiv, Mesh::ModeSolid);
         Text.Load(CodeVert, File::Path::Shader(File::FilterSolidsDepthVert));
         EnableVideo = false;
         EnableDepth = true;
         EnableCal = false;
         break;

      case FilterSolids::CubesTinted :
         Model.Cube(1, Mesh::ModeSolid);
         Text.Load(CodeVert, File::Path::Shader(File::FilterSolidsVideoVert));
         Video.Create(Buffer.GetVideoResolution(), Buffer.GetVideoDataType());
         Video.ClearData();
         Video.Buffer(false);
         EnableVideo = true;
         EnableDepth = true;
         EnableCal = true;
         Mat.SetShininess(0.0f);
         break;

      case FilterSolids::SpheresTinted :
         Model.Sphere(PolyDiv, Mesh::ModeSolid);
         Text.Load(CodeVert, File::Path::Shader(File::FilterSolidsVideoVert));
         Video.Create(Buffer.GetVideoResolution(), Buffer.GetVideoDataType());
         Video.ClearData();
         Video.Buffer(false);
         EnableVideo = true;
         EnableDepth = true;
         EnableCal = true;
         break;

      case FilterSolids::CubesFar :
         Model.Cube(1, Mesh::ModeSolid);
         Text.Load(CodeVert, File::Path::Shader(File::FilterSolidsDepthVert));
         EnableVideo = false;
         EnableDepth = true;
         EnableCal = false;
         Mat.SetShininess(0.0f);
         Far = -1000.0f;
         break;

      case FilterSolids::SpheresFar :
         Model.Sphere(PolyDiv, Mesh::ModeSolid);
         Text.Load(CodeVert, File::Path::Shader(File::FilterSolidsDepthVert));
         EnableVideo = false;
         EnableDepth = true;
         EnableCal = false;
         Far = -1000.0f;
         break;

      default : dexception("Unknown filter enumeration type.");
      }

   Range = Math::Abs(Far - Near);

   Model.Buffer(false);

   Text.Load(CodeFrag, File::Path::Shader(File::FilterSolidsFrag));
   Program.Attach(CodeVert, Shader::ShaderVert);
   Program.Attach(CodeFrag, Shader::ShaderFrag);
   Program.Buffer(false);

   Program.Bind();
   glUniform1f(glGetUniformLocation(Program.ID(), "Range"), Math::Abs(Range));
   glUniform1i(glGetUniformLocation(Program.ID(), "Depth"), 0);   //Texture unit 0
   glUniform1i(glGetUniformLocation(Program.ID(), "Video"), 1);   //Texture unit 1
   UID = glGetUniformLocation(Program.ID(), "TexCoord");
   glUniform2f(UID, 0.0f, 0.0f);
   Program.Unbind();

   //Projection matrix
   MP = MP.Identity();
   MP = MP.Frustum(-Ratio.X, Ratio.X, -Ratio.Y, Ratio.Y, Math::Abs(Near), Math::Abs(Far));

   //Modelview matrix
   float Scale = 1.0f / (float)GridSmallest;
   MV = MV.Identity();
   MV = MV.Scale(Scale, Scale, Scale);
   MV = MV.Translate(0.0f, 0.0f, (Near - Scale - 0.01f) / Scale);

   GLenum Error = glGetError();
   if (Error != GL_NO_ERROR) {throw dexception("OpenGL generated an error: %s", Debug::ErrorGL(Error));}
   }