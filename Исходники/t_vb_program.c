/**
 * Initialize virtual machine state prior to executing vertex program.
 */
static void
init_machine(GLcontext *ctx, struct gl_program_machine *machine)
{
   /* Input registers get initialized from the current vertex attribs */
   MEMCPY(machine->VertAttribs, ctx->Current.Attrib,
          MAX_VERTEX_PROGRAM_ATTRIBS * 4 * sizeof(GLfloat));

   if (ctx->VertexProgram._Current->IsNVProgram) {
      GLuint i;
      /* Output/result regs are initialized to [0,0,0,1] */
      for (i = 0; i < MAX_NV_VERTEX_PROGRAM_OUTPUTS; i++) {
         ASSIGN_4V(machine->Outputs[i], 0.0F, 0.0F, 0.0F, 1.0F);
      }
      /* Temp regs are initialized to [0,0,0,0] */
      for (i = 0; i < MAX_NV_VERTEX_PROGRAM_TEMPS; i++) {
         ASSIGN_4V(machine->Temporaries[i], 0.0F, 0.0F, 0.0F, 0.0F);
      }
      for (i = 0; i < MAX_VERTEX_PROGRAM_ADDRESS_REGS; i++) {
         ASSIGN_4V(machine->AddressReg[i], 0, 0, 0, 0);
      }
   }

   machine->NumDeriv = 0;

   /* init condition codes */
   machine->CondCodes[0] = COND_EQ;
   machine->CondCodes[1] = COND_EQ;
   machine->CondCodes[2] = COND_EQ;
   machine->CondCodes[3] = COND_EQ;

   /* init call stack */
   machine->StackDepth = 0;

   machine->FetchTexelLod = vp_fetch_texel;
   machine->FetchTexelDeriv = NULL; /* not used by vertex programs */

   machine->Samplers = ctx->VertexProgram._Current->Base.SamplerUnits;
}