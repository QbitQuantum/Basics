MStatus MayaFileTranslator::writer( 	const MFileObject& file,
const MString& options,
FileAccessMode mode){

//-------------------détection des options transmises par le script MEL---------------


	// this will store our option strings
	MStringArray optionList;

	// seperate the option string
	options.split(' ', optionList);

	
	// check all of the options
	int len = optionList.length();

	for( int i = 0; i < len; ++i ){
  		MString Option = optionList[i];

	

		// if we recognised option 1
		if( Option == "vertexcolorFlag" ) {
  			// check for true or false
			if(optionList[++i]=="0")
				Flags.vertex_colors=0;
			else
				Flags.vertex_colors=1;

		}

		// if we recognised our second option
		if( Option == "vertexnormalFlag" ) {
  		// check for true or false
			if(optionList[++i]=="0")
				Flags.Normals=0;
			else
  				Flags.Normals=1;

		}



		// if we recognised our third option
		if( Option == "brushFX" ) {
  			// check for true or false
			if(optionList[++i]=="0")
				Flags.use_vertex_colors=1;
			else
  				Flags.use_vertex_colors=0;

		}
		
	}

	//----------------------------------fin------------------------

	//export Selected Objects
    if(mode == kExportActiveAccessMode) 
	{
		//liste des objets sélectionnés
		MSelectionList selection;
		MGlobal::getActiveSelectionList( selection );
		
		//MStringArray strings;
		//MDagPath dagPath;

			MObject components;
			MDagPath path;

		//-----

//		int temp;
		//MGlobal::displayInfo("Début exportation des objets sélectionnés");
		// ouverture du fichier [BB3D]
		MString output_filename = file.fullName();
		::output.open(output_filename.asChar(),ios::out |ios::binary);
		// ecriture header fichier
		
		::output << "BB3D"; // mise en place du Header fichier B3D
		StartChunck();

		// sauv garde de la position du début de fichier
		//write_int(1);// mise en place d'une valeur entière quelconque pour mise en place ultérieure de la longeur du fichier
		write_int(1);//écriture de la version BB3D
	

#ifdef OLD_TEXS
		// écriture des textures si présentent [TEXS]|detection des textures à enregistrer| + fermeture texs
::output << "TEXS";//header Brush
								StartChunck();
		OutputTextures(selection);
EndChunck();

		// écriture des matériaux [BRUS]|detection des materiaux à enregistrer| +fermeture brus
	
		
//Matid.clear();
		
OutputMaterials(selection);

#else

		//nouvelles textures

#endif	
		
	//------------------------------------fin materials----------------------------------


#ifdef SCENE_ROOT
		// algo des nodes [NODE] réplication de la hierarchie, 
		::output << "NODE"; // mise en place du Header fichier B3D
		StartChunck();
		

		//write_int(1);// mise en place d'une valeur quelconque
		::output << "Scene Root";//nom du Node
		::output << char(0x00);//fin de chaîne

		//écriture des coordonnées spatiales
		//transaltion
		write_float(0);// translation x
		write_float(0);// translation y
		write_float(0);// translation z
		
		write_float(1);//scale x
		write_float(1);//scale y
		write_float(1);//scale z
		
		write_float(0);// rotation  x
		write_float(0);// rotation  y
		write_float(0);// rotation  z
		write_float(0);// rotation  w
		
#else
#endif
		



		int pos_objet=0,pos_nouvel_objet;
		MString nom_objet_precedent;


 	

		// create an iterator to go through all transforms
		//MItDag it(MItDag::depth, MFn::kTransform); 
		MItDag it(MItDag::kDepthFirst, MFn::kTransform);
		// keep looping until done
		int position_hierarchie=0;
		int pos=0;
		while(!it.isDone())
		{
  				MString temp;
				MDagPath path;
				it.getPath(path);
				MFnTransform trans(path);	
				MObject obj=it.item();

	
			
		

				MStringArray chemin_split;
			MString chemin=path.fullPathName();

		
			chemin.split((char)'|',chemin_split);

			pos=chemin_split.length();
			//temp=pos;

			//MGlobal::displayInfo(temp);
		
			if(obj.apiType()== MFn::kTransform && path.child(0).apiType()== MFn::kMesh){
						//MGlobal::displayInfo("Transform trouvé avec child Kmesh");
						//écriture du node avec transform
						//incrément de la hierarchie
						if(pos<position_hierarchie || pos==position_hierarchie){
							//MGlobal::displayInfo("fermeture des nodes précédents");
							for(int i=position_hierarchie;i>pos-1;i--){
							//temp = i;
							//MGlobal::displayInfo(temp);

							EndChunck();
							}//fin for
						
						}//fin if
							
								//MGlobal::displayInfo("Ouverture node");
								::output << "NODE"; // mise en place du Header node
								StartChunck();
								MString nom_objet;
								nom_objet=chemin_split[chemin_split.length()-1];
								
							
									::output << nom_objet.substring(0,nom_objet.length());//nom du Node
								
									::output << char(0x00);//caractêre de fin de chaîne


									
			

			
MVector Translation;
				// get the transforms local translation
		
Translation = trans.getTranslation(MSpace::kTransform);
		
			
			float temp=(float)Translation.x;
			//écriture des coordonnées spaciales
			//transaltion
			write_float(temp);// translation x
			temp=(float)Translation.y;
			write_float(temp);// translation y
			temp=-(float)Translation.z;
			write_float(temp);// translation z
			
				
			double scale[3];
			trans.getScale(scale);
			temp=(float)scale[0];
			write_float(temp);
			temp=(float)scale[1];
			write_float(temp);
			temp=(float)scale[2];
			write_float(temp);

			
			MQuaternion Rotation;
			
			trans.getRotation(Rotation,MSpace::kTransform);



			temp=(float)Rotation.w;
			write_float(temp);
			temp=(float)Rotation.x;
			write_float(temp);
			temp=(float)Rotation.y;
			write_float(temp);
			temp=(float)Rotation.z; 
			write_float(temp);

		


							
		
			


						path.getPath(path);
						if(selection.hasItem(path)!=MStatus::kSuccess){
							//MGlobal::displayInfo("présent dans la liste de selection");
							
							//---------exportation du mesh

						//mais avec des nodes vides, pour les mesh non sélectionnés
					//----------------------------ecriture mesh si objet polygonal présent
						::output << "MESH"; // mise en place du Header mesh
						StartChunck();
										MPointArray vertexArray;// coordonnées des point format double x,y,z;
										MIntArray vertexList;// stockage des indexs des points pour les triangles
										MVector Normal;//stockage d'une normal d'un vertex
		
						//----------------------coordonnées Vertexs  (normal & color si présent et demandés)
						//master brush
						//write_int(0xffffffff);
						write_int(-1);//-1 master brush
						
						MFnMesh meshFn(path.child(0)); // crée une fonction pour le mesh
										
						MItMeshVertex polyperVertex(path, MObject::kNullObj);// crée une fonction pour le mesh , mais avec les fonctions de itmesh
						
						//récupération des coordonnées des points
						//obtient les coordonnées des vertex en mode global
						//meshFn.getPoints(vertexArray,MSpace::kObject);
						meshFn.getPoints(vertexArray,MSpace::kTransform);

						//MFloatArray uArray;
						//MFloatArray vArray;

						//meshFn.getUVs(uArray,vArray);//getUVs( MFloatArray& uArray, MFloatArray& vArray,const MString * uvSet = NULL )
						
						MIntArray uvCounts,uvIds;

						meshFn.getAssignedUVs(uvCounts,uvIds,0);



						//ecriture VRTS
						::output<<"VRTS";
						StartChunck();

										//flags 0=none just vertices coords 1=normal values present, 2=rgba values present
										//The way the flags work, is that you combine them.
										//1 = Vertex Normal
										//2 = Vertex Color
										//3 = Vertex Normal + Color
int flag_normal_colors=0;
//info = "Normals ";
//info += Flags.Normals;
//Affich(info);
//info = "vertex colors ";
//info += Flags.vertex_colors;
//Affich(info);
flag_normal_colors = Flags.Normals+((Flags.use_vertex_colors && Flags.vertex_colors)*2);
//info = flag_normal_colors;
//Affich(info);
						write_int(flag_normal_colors);//présence normale
						
						//int tex_coord_sets          ;texture coords per vertex (eg: 1 for simple U/V) max=8
						write_int(1);//uv simple
						//  int tex_coord_set_size      ;components per set (eg: 2 for simple U/V) max=4
						write_int(2);//2 coordonées textures






										
										




						float x,y,z,normx,normy,normz;//,normx,normy,normz;
						for (unsigned int i=0;i<vertexArray.length();i++){


							x =float(vertexArray[i].x); // -  pour replacer l'axe X dans le sens de celui de blitz
							y =float(vertexArray[i].y);
							z =-float(vertexArray[i].z);// -



							//vertices coords

							write_float(x);
							write_float(y);
							write_float(z);

							//récupère la normale du point
							if(flag_normal_colors==1 || flag_normal_colors==3){
											meshFn.getVertexNormal(i, Normal ,MSpace::kObject);
											normx=float(Normal.x);
											normy=float(Normal.y);
											normz=float(Normal.z);

											
											
											write_float(normx);
											write_float(normy);
											write_float(normz);
							}
											


							//-----------------------------------------
											//vertex_colors_present=1;
											
											if (flag_normal_colors == 2 || flag_normal_colors==3){
											
											
											MStringArray colorsets;
											MColorArray color;
											
											//status = meshFn.getColorSetNames(colorsets);
											meshFn.getColorSetNames(colorsets);
										
												   
												MColor couleur;
												MString colorset = colorsets[0];
												//récupère la couleur moyenne des faces connectés au point
												meshFn.getVertexColors(color,&colorset);

												
												
												
												//polyperVertex.getColor
												//int a;
												//meshFn.getColor(a,couleur);
												//meshFn.getColors(color);
												couleur=color[i];
												float col=float(couleur.r);
												//R
												::output.write((char*)&couleur.r,sizeof(couleur.r));
												//write_float(col);
												col=float(couleur.g);
												//G
												::output.write((char*)&couleur.g,sizeof(couleur.g));
												//write_float(col);
												col=float(couleur.b);
												//B
												::output.write((char*)&couleur.b,sizeof(couleur.b));
												//write_float(col);
												col=float(couleur.a);
												//Alpha
												::output.write((char*)&couleur.a,sizeof(couleur.a));
												//write_float(col);
											
											
											
											}
											//-----------------------------------------
											

//float tempo;
float u,v;

MFloatArray uArray;
MFloatArray vArray;
MIntArray FaceIds;

polyperVertex.getUVs(uArray,vArray,FaceIds);

//meshFn.getUV(i*2,u,v);

u=uArray[0];
v=vArray[0];



//tempo = uArray[0];
//write_float(tempo);

//tempo = vArray[0];
//write_float(tempo);

write_float(u);
write_float(-v);


polyperVertex.next();













						}//fin for

	

						//-----------------fermeture coordonées Vertex
						EndChunck();
						// ----------------------------------export des triangles


#ifdef OLD_TRIS

							//ecriture TRIS
						::output<<"TRIS";
						StartChunck();

										//brush ID
										write_int(-1);//write_int(0);




										//MItMeshPolygon  itPolygon( path, MObject::kNullObj );
										MItMeshPolygon  itPolygon(path.child(0));

	

										for ( /* nothing */; !itPolygon.isDone(); itPolygon.next() )
										{		
					
	

											// Get triangulation of this poly.
											int  numTriangles; 
											itPolygon.numTriangles(numTriangles);

											while ( numTriangles-- )
											{
												//MGlobal::displayInfo("  triangle");
												MStatus status;

												MIntArray                           polygonVertices;

												itPolygon.getVertices( polygonVertices );

												MPointArray                     nonTweaked;
												// object-relative vertex indices for each triangle
												MIntArray                       triangleVertices;
												// face-relative vertex indices for each triangle
												MIntArray                       localIndex;

												status = itPolygon.getTriangle( numTriangles,
												nonTweaked,
												triangleVertices,
												MSpace::kObject );
		
												if ( status == MS::kSuccess )
												{



													//traitement du triangle
			
													// Get face-relative vertex indices for this triangle

			
													//int temp=triangleVertices[0];
						
						
													write_int(triangleVertices[0]);
													write_int(triangleVertices[2]);
													write_int(triangleVertices[1]);
													//::output.write((char*)&triangleVertices[0],sizeof(triangleVertices[0]));
													//::output.write((char*)&triangleVertices[2],sizeof(triangleVertices[2]));
													//::output.write((char*)&triangleVertices[1],sizeof(triangleVertices[1]));
			
			

												} // fin if	


											};// fin while



									}; //fin for

										EndChunck();

#else

			

	unsigned int instancenumbers;
	MObjectArray shaders;
	MIntArray indices;
	//MFnMesh		Fn(path.instanceNumber);
	meshFn.getConnectedShaders(instancenumbers,shaders,indices);
	MString info="shaders.lenght ";
	info += shaders.length();
	Affich(info);

	for (int i=-1;i<shaders.length();i++){//création de tris en fonction du nombre de brush appliqué
		//___________ouput tris________
	
		info = "shader ";
		info += i;
	Affich(info);

							//ecriture TRIS
						::output<<"TRIS";
						StartChunck();
						


	//trouver le brush id par rapport à matid
	//recup nom shader et compare à matid
	MString nameshader;
	nameshader=GetShaderName(shaders[i]);

	info = "Matid id lenght";
	info += Matid.length();
	Affich(info);

int BrushId=0;
	for (int b=0;b<Matid.length();b++){
		if (nameshader==Matid[b]){
		BrushId=b;
		}	
	}

							//brush ID
						write_int(BrushId);
						//write_int(-1);//default
			info= "BrushId ";
		info += BrushId;
	Affich(info);

	info = Matid[BrushId];
	Affich(info);

	MItMeshPolygon  itPolygon(path.child(0));
	int d=0;
	for ( /* nothing */; !itPolygon.isDone(); itPolygon.next() )
		{

			nameshader=GetShaderName(shaders[indices[d]]);
			if(nameshader==Matid[BrushId]){

				// Get triangulation of this poly.
				int  numTriangles; 
				itPolygon.numTriangles(numTriangles);
				while ( numTriangles-- )
											{
												//MGlobal::displayInfo("  triangle");
												MStatus status;

												MIntArray                           polygonVertices;

												itPolygon.getVertices( polygonVertices );
											
												MPointArray                     nonTweaked;
												// object-relative vertex indices for each triangle
												MIntArray                       triangleVertices;
												// face-relative vertex indices for each triangle
												MIntArray                       localIndex;

												status = itPolygon.getTriangle( numTriangles,
												nonTweaked,
												triangleVertices,
												MSpace::kObject );
		
												if ( status == MS::kSuccess )
												{



													
						
						
													write_int(triangleVertices[0]);
													write_int(triangleVertices[2]);
													write_int(triangleVertices[1]);
													
			

												} // fin if	


											};// fin while


			}
		d++;

		}
					
	for (int i=0;i<indices.length();i++){
		//info = " indice ";
		//info += indices[i];
		//Affich(info);

		nameshader=GetShaderName(shaders[indices[i]]);
		if(nameshader==Matid[BrushId]){
		//info=nameshader;
		//Affich(info);

//*********************ecrire triangle*******


		}

	}

	
						EndChunck();

	}
	//for (int i=0;i<Matid.length();i++){
	//	info = Matid[i];
	//	Affich(info);
	//}
//Affich("fin objet");

#endif

						


					//---------------------fermeture mesh
						EndChunck();

							//------------------------------------------------------------
						
						}
						position_hierarchie=pos;
				}
				// move on to next node
				it.next();
			 
			
		}//fin while
		

				//fermeture du node
		//fermeture fichier
		//fermeture de tous les nodes ouverts
			//for (int i=posfichier.length();i>0;i--){

#ifdef SCENE_ROOT
				EndChunck();
#else
#endif

				//}
		//écriture de la longueur du fichier

		output.close();
		Matid.clear();
		Texid.clear();
		nb_Tex_by_Brush.clear();
		Texids_by_brush.clear();
	}
	else		
		//export all polygonal scene objects
	{
	}
	


	return MS::kSuccess;
}