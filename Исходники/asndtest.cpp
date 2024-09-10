void ASndTest::CreateWorld ()
{
  // Load the first texture from the standard library.
  if (!loader->LoadTexture ("stone", "/lib/std/stone4.gif"))
    ReportError("Error loading %s texture!",
		CS::Quote::Single ("stone4"));
  iMaterialWrapper* tm = engine->GetMaterialList ()->FindByName ("stone");

  // Load a second texture from the standard library.
  if (!loader->LoadTexture ("spark", "/lib/std/spark.png"))
    ReportError("Error loading %s texture!",
		CS::Quote::Single ("spark"));

  // Load a sprite from the standard library.
  csRef<iMeshFactoryWrapper> imeshfact (loader->LoadMeshObjectFactory ("/lib/std/sprite1"));
  if (imeshfact == 0)
    ReportError("Error loading %s mesh object factory!",
		CS::Quote::Single ("sprite1"));
  csRef<iMeshWrapper> sprite;
  csRef<iSprite3DState> spstate;

  // Create and prepare the world
  world = engine->CreateSector ("room");

  // First we make a primitive for our geometry.
  using namespace CS::Geometry;
  DensityTextureMapper mapper (0.3f);
  TesselatedBox box (csVector3 (-40, 0, 0), csVector3 (40, 10, 40));
  box.SetLevel (3);
  box.SetMapper (&mapper);
  box.SetFlags (Primitives::CS_PRIMBOX_INSIDE);

  // Now we make a factory and a mesh at once.
  csRef<iMeshWrapper> walls = GeneralMeshBuilder::CreateFactoryAndMesh (
      engine, world, "walls", "walls_factory", &box);
  walls->GetMeshObject ()->SetMaterialWrapper (tm);

  // Prepare lighting
  csRef<iLight> light;
  iLightList* ll = world->GetLights ();

  csRef<iCommandLineParser> cmdline (
        csQueryRegistry<iCommandLineParser> (GetObjectRegistry ()));

  csString fname = cmdline->GetOption ("sndfile");
  if (fname.IsEmpty ())
  {
    fname = "/lib/std/loopbzzt.wav";
    csPrintf ("You can override sound file using -sndfile option (VFS path)\n");
  }
  csPrintf ("Sound file  : %s\n", fname.GetData ());

  csRef<iDataBuffer> soundbuf = vfs->ReadFile (fname.GetData ());
  if (!soundbuf)
    ReportError ("Can't load file %s!", CS::Quote::Single (fname.GetData ()));

  // Interpret the sound
  csRef<iSndSysData> snddata = sndloader->LoadSound (soundbuf);
  if (!snddata)
    ReportError ("Can't load sound %s!", CS::Quote::Single (fname.GetData ()));

  const csSndSysSoundFormat* format = snddata->GetFormat ();
  csPrintf ("=== iSndSysData format informations ===\n");
  csPrintf ("Format      : %d bits, %d channel(s), %d Hz\n",
        format->Bits, format->Channels, format->Freq);
  csPrintf ("Sample Size : %zu bytes, %zu frames\n", snddata->GetDataSize (),
        snddata->GetFrameCount ());
  csPrintf ("Duration : %f second\n", ((float) snddata->GetFrameCount ()) / ((float) format->Freq));
  csPrintf ("Description : %s\n", snddata->GetDescription ());

  // Create a stream for the sound
  csRef<iSndSysStream> sndstream = sndrenderer->CreateStream (snddata, CS_SND3D_ABSOLUTE);
  if (!sndstream)
    ReportError ("Can't create stream for %s!", CS::Quote::Single (fname.GetData ()));

  const csSndSysSoundFormat* rformat = sndstream->GetRenderedFormat ();
  csPrintf ("=== iSndSysStream format informations ===\n");
  csPrintf ("Format      : %d bits, %d channel(s), %d Hz\n",
        rformat->Bits, rformat->Channels, rformat->Freq);
  csPrintf ("Stream Size : %zu frames\n", sndstream->GetFrameCount ());
  csPrintf ("Duration : %f second\n", ((float) sndstream->GetFrameCount ()) / ((float) rformat->Freq));
  csPrintf ("Description : %s\n", sndstream->GetDescription ());

  // Make the stream loop and play (unpaused)
  sndstream->SetLoopState (CS_SNDSYS_STREAM_LOOP);
  sndstream->Unpause ();

  csRef<iSndSysSource> sndsource;
  csRef<iSndSysSource3D> sndsource3d;

  // Add some quick lighting
  light = engine->CreateLight (0, csVector3 (-30, 5, 10), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);
  light = engine->CreateLight (0, csVector3 (-30, 5, 30), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);
  light = engine->CreateLight (0, csVector3 (-10, 5, 10), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);
  light = engine->CreateLight (0, csVector3 (-10, 5, 30), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);
  light = engine->CreateLight (0, csVector3 ( 10, 5, 30), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);
  light = engine->CreateLight (0, csVector3 ( 10, 5, 10), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);
  light = engine->CreateLight (0, csVector3 ( 30, 5, 30), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);
  light = engine->CreateLight (0, csVector3 ( 30, 5, 10), 20, csColor (0.22f, 0.2f, 0.25f));
  ll->Add (light);

  // Create a small sound source
  sndsource = sndrenderer->CreateSource (sndstream);
  sndsource3d = scfQueryInterface<iSndSysSource3D> (sndsource);
  sndsource->SetVolume( 1.0f );
  sndsource3d->SetMinimumDistance( 1.0f );
  sndsource3d->SetPosition( csVector3 (3.0f, 5.0f, 10.0f) );
  light = engine->CreateLight (0, csVector3 (30.0f, 1.0f, 10.0f), 5.0f, csColor (0.15f, 0.0f, 0.0f));
  ll->Add (light);
  sprite = engine->CreateMeshWrapper (imeshfact, "Sound1Sprite", world, csVector3 (30.0f, 5.0f, 10.0f));
  spstate = scfQueryInterface<iSprite3DState> (sprite->GetMeshObject());
  spstate->SetAction ("default");

  // Create a medium sound source
  sndsource = sndrenderer->CreateSource (sndstream);
  sndsource3d = scfQueryInterface<iSndSysSource3D> (sndsource);
  sndsource->SetVolume( 1.0f );
  sndsource3d->SetMinimumDistance( 2.0f );
  sndsource3d->SetPosition( csVector3 (3.0f, 5.0f, 30.0f) );
  light = engine->CreateLight (0, csVector3 (30.0f, 1.0f, 30.0f), 5.0f, csColor (0.3f, 0.0f, 0.0f));
  ll->Add (light);
  sprite = engine->CreateMeshWrapper (imeshfact, "Sound2Sprite", world, csVector3 (30.0f, 5.0f, 30.0f));
  spstate = scfQueryInterface<iSprite3DState> (sprite->GetMeshObject());
  spstate->SetAction ("default");

  // Create a large sound source
  sndsource = sndrenderer->CreateSource (sndstream);
  sndsource3d = scfQueryInterface<iSndSysSource3D> (sndsource);
  sndsource->SetVolume( 1.0f );
  sndsource3d->SetMinimumDistance( 4.0f );
  sndsource3d->SetPosition( csVector3 (10.0f, 5.0f, 30.0f) );
  light = engine->CreateLight (0, csVector3 (10.0f, 1.0f, 30.0f), 5.0f, csColor (0.6f, 0.0f, 0.0f));
  ll->Add (light);
  sprite = engine->CreateMeshWrapper (imeshfact, "Sound3Sprite", world, csVector3 (10.0f, 5.0f, 30.0f));
  spstate = scfQueryInterface<iSprite3DState> (sprite->GetMeshObject());
  spstate->SetAction ("default");

  // Create a simple directional source
  sndsource = sndrenderer->CreateSource (sndstream);
  sndsource3d = scfQueryInterface<iSndSysSource3D> (sndsource);
  sndsource->SetVolume( 1.0f );
  sndsource3d->SetMinimumDistance( 8.0f );
  sndsource3d->SetPosition( csVector3 (-10.0f, 5.0f, 30.0f) );
  csRef<iSndSysSource3DDirectionalSimple> sndsource3dds = scfQueryInterface<iSndSysSource3DDirectionalSimple> (sndsource);
  sndsource3dds->SetDirection( csVector3 (0.0f, 0.0f, 1.0f) );
  sndsource3dds->SetDirectionalRadiation (QUARTER_PI);
  light = engine->CreateLight (0, csVector3 (-10.0f, 5.0f, 39.0f), 5.0f, csColor (0.6f, 0.0f, 0.0f));
  ll->Add (light);
  sprite = engine->CreateMeshWrapper (imeshfact, "Sound4Sprite", world, csVector3 (-10.0f, 5.0f, 30.0f));
  spstate = scfQueryInterface<iSprite3DState> (sprite->GetMeshObject());
  spstate->SetAction ("default");

  // Create a normal directional source
  sndsource = sndrenderer->CreateSource (sndstream);
  sndsource3d = scfQueryInterface<iSndSysSource3D> (sndsource);
  sndsource->SetVolume( 1.0f );
  sndsource3d->SetMinimumDistance( 8.0f );
  sndsource3d->SetPosition( csVector3 (-30.0f, 5.0f, 30.0f) );
  csRef<iSndSysSource3DDirectional> sndsource3dd = scfQueryInterface<iSndSysSource3DDirectional> (sndsource);
  sndsource3dd->SetDirection( csVector3 (0.0f, 0.0f, 1.0f) );
  sndsource3dd->SetDirectionalRadiationInnerCone (QUARTER_PI);
  sndsource3dd->SetDirectionalRadiationOuterCone(HALF_PI);
  sndsource3dd->SetDirectionalRadiationOuterGain( 0.0f );
  light = engine->CreateLight (0, csVector3 (-30.0f, 5.0f, 39.0f), 5.0f, csColor (0.6f, 0.0f, 0.0f));
  ll->Add (light);
  sprite = engine->CreateMeshWrapper (imeshfact, "Sound5Sprite", world, csVector3 (-30.0f, 5.0f, 30.0f));
  spstate = scfQueryInterface<iSprite3DState> (sprite->GetMeshObject());
  spstate->SetAction ("default");

  // Create a doppler source
  sndsource = sndrenderer->CreateSource (sndstream);
  movingsound = scfQueryInterface<iSndSysSource3D> (sndsource);
  sndsource->SetVolume( 1.0f );
  movingsound->SetMinimumDistance( 8.0f );
  movingsound->SetPosition( csVector3 (-10.0f, 5.0f, 10.0f) );
  movingsounddoppler = scfQueryInterface<iSndSysSource3DDoppler> (sndsource);
  movingsoundsprite = engine->CreateMeshWrapper (imeshfact, "Sound6Sprite", world, csVector3 (-10.0f, 5.0f, 10.0f));
  spstate = scfQueryInterface<iSprite3DState> (movingsoundsprite->GetMeshObject());
  spstate->SetAction ("default");
  movingsoundstep = 0;
  listenerdoppler = scfQueryInterface<iSndSysListenerDoppler> (sndrenderer->GetListener ());
  // 10 Units = 1 meter
  listenerdoppler->SetSpeedOfSound( 3433 );
  // Amplify Doppler effect by 100
  listenerdoppler->SetDopplerFactor( 100 );

  engine->Prepare ();

  using namespace CS::Lighting;
  SimpleStaticLighter::ShineLights (world, engine, 4);
}