void ShaderInfo::ReflectShader(ID3D10Blob* shader)
{
    D3D11_SHADER_DESC sd;

    D3DReflect(shader->GetBufferPointer(), shader->GetBufferSize(),
               IID_ID3D11ShaderReflection, (void**)&m_reflector);

    m_reflector->GetDesc(&sd);
    shaderDesc = sd;

    for(UINT i = 0; i < sd.InputParameters; i++)
    {
        //Mask gives info on how many components
        D3D11_SIGNATURE_PARAMETER_DESC inputparam_desc;
        m_reflector->GetInputParameterDesc(i, &inputparam_desc);
        m_inputParams.push_back(inputparam_desc);

    }
    for(UINT i = 0; i < sd.OutputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC outputparam_desc;
        m_reflector->GetOutputParameterDesc(i, &outputparam_desc);
        m_outputParams.push_back(outputparam_desc);
    }
    for(UINT i = 0; i < sd.BoundResources; i++)
    {
        D3D11_SHADER_INPUT_BIND_DESC resource_desc; //Bind point is the register location
        m_reflector->GetResourceBindingDesc(i, &resource_desc);

        if(resource_desc.Type == D3D_SIT_CBUFFER)
        {
            Cbuffer* cbuffer = new Cbuffer();
            cbuffer->input_bind_desc = resource_desc;

            ID3D11ShaderReflectionConstantBuffer* cb =
                m_reflector->GetConstantBufferByName(cbuffer->input_bind_desc.Name);

            cb->GetDesc(&cbuffer->buffer_desc);

            for(UINT j = 0; j < cbuffer->buffer_desc.Variables; j++)
            {
                Variable* var = new Variable();

                ID3D11ShaderReflectionVariable* variable =
                    cb->GetVariableByIndex(j);

                variable->GetDesc(&var->var);

                ID3D11ShaderReflectionType* type =
                    variable->GetType();

                type->GetDesc(&var->type);

                cbuffer->vars.push_back(var);

                //register cbuff vars with ShaderVars object
// 				switch(var->type.Class) {
// 				case D3D_SVC_MATRIX_COLUMNS:
// 					if(var->type.Rows == 4 && var->type.Columns == 4) {
// 						cbp->AddMatrix(var->var.Name);
// 					}
// 					else if(var->type.Rows == 3 && var->type.Columns == 3) {
//
// 					}
// 					break;
// 				case D3D_SVC_VECTOR:
// 					if(var->type.Columns == 4) {
// 						cbp->AddVector(var->var.Name);
// 					}
// 					else if(var->type.Columns == 3) {
//
// 					}
// 					else if(var->type.Columns == 2) {
//
// 					}
// 					break;
// 				case D3D_SVC_SCALAR:
// 					if(var->type.Type == D3D_SVT_FLOAT) {
// 						cbp->AddScalar(var->var.Name);
// 					}
// 					break;
// 				default:
// 					break;
// 				}



            }
            m_cbuffers.push_back(cbuffer);
        }
        else if(resource_desc.Type == D3D_SIT_SAMPLER)
        {
            m_samplers.push_back(resource_desc);
        }
        else if(resource_desc.Type == D3D_SIT_TEXTURE)
        {
            m_textures.push_back(resource_desc);
        }
        else
        {
            m_resources.push_back(resource_desc);
        }
    }
}