bool GameDeploymentUtil::createGameConfig( const std::string& targetDir, const GameDeploymentInfo& info )
{
   ResourcesManager& resMgr = TSingleton< ResourcesManager >::getInstance();
   Filesystem& fs = resMgr.getFilesystem();


   GameConfig* config = new GameConfig();
   config->m_renderingPipelinePath = info.m_renderingPipelinePath;
   config->m_worldModelPath = info.m_worldModelPath;

   // save it in this filesystem
   FilePath gameConfigPath( "game.gcf" );
   ReflectionSerializationUtil::saveObject( config, gameConfigPath );

   // destroy the config instance
   delete config;

   // move it to the destination
   std::string gameConfigSourcePath = gameConfigPath.toAbsolutePath( fs );
   std::string gameConfigDestPath = targetDir + "/" + gameConfigPath.c_str();
   bool deploymentSuccessful = CopyFileA( gameConfigSourcePath.c_str(), gameConfigDestPath.c_str(), false ); 

   // delete the temporary file
   fs.remove( gameConfigPath );

   return deploymentSuccessful;
}