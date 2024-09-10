/*!
 * Register an embeddable plugin with XAP_App
 */
UT_sint32 XAP_App::registerEmbeddable(GR_EmbedManager * pEmbed)
{
	 UT_return_val_if_fail( pEmbed, -1 );
	 
     UT_sint32 i=0;
     bool bFound = false;
     GR_EmbedManager * pCur = NULL;
     for(i=0; !bFound && (i< m_vecEmbedManagers.getItemCount()); i++)
     {
		 pCur =  m_vecEmbedManagers.getNthItem(i);
		 if(pCur && (strcmp(pCur->getObjectType(),pEmbed->getObjectType()) == 0))
		 {
			 bFound = true;
		 }
     }
     if(!bFound)
     {
		 m_vecEmbedManagers.addItem(pEmbed);
		 return  m_vecEmbedManagers.getItemCount() - 1;
     }
     return -1;
}