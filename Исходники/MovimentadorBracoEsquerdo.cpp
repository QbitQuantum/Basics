void MovimentadorBracoEsquerdo::mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) 
{
	std::string ombro_esquerdo_bone			=       "UpArm_L";
	std::string braco_esquerdo_bone			=       "LoArm_L";
	std::string mao_esquerda_bone			=		"Index_L";

	float anguloOmbroEsquerdo = getAnguloBraco(esqueleto.ombro_esquerdo,esqueleto.cotovelo_esquerdo);	
	setarAnguloBone(node,ombro_esquerdo_bone,-anguloOmbroEsquerdo);		
	float anguloMaoEsquerda = CalculosUteis::anguloEntrePontos(esqueleto.cotovelo_esquerdo,esqueleto.ombro_esquerdo,esqueleto.mao_esquerda);
	if(esqueleto.cotovelo_esquerdo.y < esqueleto.mao_esquerda.y)
		anguloMaoEsquerda = - anguloMaoEsquerda;
	if(!_isnan(anguloMaoEsquerda))
		setarAnguloBone(node,braco_esquerdo_bone,anguloMaoEsquerda);


	IBoneSceneNode * mao = node->getJointNode(mao_esquerda_bone.c_str());
	pos = Vetor(
		mao->getAbsolutePosition().X,
		mao->getAbsolutePosition().Y,
		mao->getAbsolutePosition().Z);
	//teste
	/*
	bool tem = false;
	for(int i=0;i<marcadores.size();i++)
	{
		if(marcadores[i]->pontoDentroMarcador(pos) && i!=indiceAnterior)
		{
			if(!cronometro.iniciado())
			{
				cronometro.iniciarContagem();						
			}
			tem = true;
			indiceAtual = i;
		}


	}
	if(!tem)
	{
		cronometro.pararContagem();
	}
	*/

}