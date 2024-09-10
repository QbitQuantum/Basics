//----------------------------------------------------------------------------
void SEPhotonShootingTask::DoWork()
{
    // Declare local variables for the task.
    SEMemoryArena arena;
    SERandomNumberGenerator rng(31 * TaskNum);
    std::vector<SEBNPhoton> localDirectPhotons;
    std::vector<SEBNPhoton> localIndirectPhotons;
    std::vector<SEBNPhoton> localCausticPhotons;
    std::vector<SEBNRadiancePhoton> localRadiancePhotons;
    SE_UInt32 totalPaths = 0;
    bool causticDone = (PhotonMapShader->CausticPhotonsWantedCount == 0);
    bool indirectDone = (PhotonMapShader->IndirectPhotonsWantedCount == 0);
    SEPermutedHalton halton(6, rng);
    std::vector<SESpectrum> localRpReflectances;
    std::vector<SESpectrum> localRpTransmittances;

    while( true )
    {
        // Follow photon paths for a block of samples.
        const SE_UInt32 blockSize = 4096;
        for( SE_UInt32 i = 0; i < blockSize; ++i )
        {
            float u[6];
            halton.Sample(++totalPaths, u);

            // Choose light to shoot photon from.
            float lightPdf;
            int lightNum = LightDistribution->SampleDiscrete(u[0], &lightPdf);
            const SEBNLight* light = Scene->Lights[lightNum];

            // Generate photonRay from light source.
            SERayDifferential photonRay;
            float pdf;
            SEBNLightSample lightSample(u[1], u[2], u[3]);
            SEVector3f lightSurfaceNormal;
            SESpectrum Le = light->Sample_L(Scene, lightSample, u[4], u[5],
                Time, &photonRay, &lightSurfaceNormal, &pdf);
            if( pdf == 0.0f || Le.IsBlack() )
            {
                continue;
            }

            // Initialize alpha value.
            float absCostheta = 
                fabsf(lightSurfaceNormal.Dot(photonRay.Direction));
            SESpectrum alpha = Le * (absCostheta / (pdf * lightPdf));

            if( !alpha.IsBlack() )
            {
                // Follow photon path through scene and record intersections.

                bool specularPath = true;
                SEBNIntersection photonIsect;
                int nIntersections = 0;
                while( Scene->Intersect(photonRay, &photonIsect) )
                {
                    ++nIntersections;

                    // Handle photon/surface intersection.

                    alpha *= Renderer->Transmittance(Scene, photonRay, 0, rng, 
                        arena);

                    // Determine if none specular component exists.
                    SEBSDF* photonBSDF = photonIsect.GetBSDF(photonRay, arena);
                    SEBxDF::BxDFType specularType = SEBxDF::BxDFType(
                        SEBxDF::BSDF_REFLECTION | SEBxDF::BSDF_TRANSMISSION | 
                        SEBxDF::BSDF_SPECULAR);
                    bool hasNonSpecular = (photonBSDF->GetComponentCount() >
                        photonBSDF->GetComponentCount(specularType));

                    SEVector3f wo = -photonRay.Direction;
                    if( hasNonSpecular )
                    {
                        // Deposit photon at surface that has non-specular BSDF
                        // component.

                        SEBNPhoton photon(photonIsect.DG.p, alpha, wo);
                        bool depositedPhoton = false;
                        if( specularPath && nIntersections > 1 )
                        {
                            if( !causticDone )
                            {
                                // Deposit caustic photon at surface.
                                depositedPhoton = true;
                                localCausticPhotons.push_back(photon);
                            }
                        }
                        else
                        {
                            // Deposit either direct or indirect photon.
                            // Stop depositing direct photons once indirectDone
                            // is true; don't want to waste memory storing too 
                            // many if we're going a long time trying to get 
                            // enough caustic photons desposited.
                            if( nIntersections == 1 && !indirectDone && 
                                PhotonMapShader->FinalGather )
                            {
                                // Deposit direct photon at surface.
                                depositedPhoton = true;
                                localDirectPhotons.push_back(photon);
                            }
                            else if( nIntersections > 1 && !indirectDone )
                            {
                                // Deposit indirect photon at surface.
                                depositedPhoton = true;
                                localIndirectPhotons.push_back(photon);
                            }
                        }

                        // Possibly create radiance photon at photon 
                        // intersection point.
                        if( depositedPhoton && PhotonMapShader->FinalGather &&
                            rng.RandomFloat() < 0.125f )
                        {
                            SEVector3f n = photonIsect.DG.nn;
                            SEVector3f::Faceforward(n, -photonRay.Direction, n);
                            SEBNRadiancePhoton radiancePhoton(photonIsect.DG.p, 
                                n);
                            localRadiancePhotons.push_back(radiancePhoton);

                            SESpectrum rho_r = photonBSDF->rho(rng, 
                                SEBxDF::BSDF_ALL_REFLECTION);
                            localRpReflectances.push_back(rho_r);

                            SESpectrum rho_t = photonBSDF->rho(rng, 
                                SEBxDF::BSDF_ALL_TRANSMISSION);
                            localRpTransmittances.push_back(rho_t);
                        }
                    }

                    // Stop bouncing if max photon depth has been reached.
                    if( nIntersections >= PhotonMapShader->MaxPhotonDepth )
                    {
                        break;
                    }

                    // Sample new photon ray direction.
                    SEVector3f wi;
                    float _pdf;
                    SEBxDF::BxDFType flags;
                    SESpectrum fr = photonBSDF->Sample_f(wo, &wi, 
                        SEBSDFSample(rng), &_pdf, SEBxDF::BSDF_ALL, &flags);
                    if( fr.IsBlack() || _pdf == 0.0f )
                    {
                        break;
                    }

                    float absCosi = fabsf(wi.Dot(photonBSDF->DGShading.nn));
                    SESpectrum anew = alpha * fr * (absCosi / _pdf);

                    // Possibly terminate photon path with Russian roulette.
                    float luminanceRatio = anew.y() / alpha.y();
                    float continueProb = SE_MIN(1.0f, luminanceRatio);
                    if( rng.RandomFloat() > continueProb )
                    {
                        break;
                    }

                    alpha = anew / continueProb;
                    specularPath &= ((flags & SEBxDF::BSDF_SPECULAR) != 0);
                    
                    if( indirectDone && !specularPath )
                    {
                        break;
                    }

                    photonRay = SERayDifferential(photonIsect.DG.p, wi, 
                        photonRay, photonIsect.RayEpsilon);
                }
            }

            arena.FreeAll();
        }

        // Merge local photon data with data in photon map shader.
        {
            // Begin mutex scope.

            SEMutexLock lock(Mutex);

            // Give up if we're not storing enough photons.
            if( AbortTasks )
            {
                return;
            }

            bool causticUnsuccessful = Unsuccessful(
                PhotonMapShader->CausticPhotonsWantedCount, 
                CausticPhotons.size(), blockSize);

            bool indirectUnsuccessful = Unsuccessful(
                PhotonMapShader->IndirectPhotonsWantedCount,
                IndirectPhotons.size(), blockSize);

            if( ShotCount > SEBNPhotonMapShader::MAX_PHOTON_PATH_SHOT_COUNT 
                && (causticUnsuccessful || indirectUnsuccessful) )
            {
                // Unable to store enough photons. Giving up.
                CausticPhotons.erase(CausticPhotons.begin(), 
                    CausticPhotons.end());
                IndirectPhotons.erase(IndirectPhotons.begin(), 
                    IndirectPhotons.end());
                RadiancePhotons.erase(RadiancePhotons.begin(), 
                    RadiancePhotons.end());

                // Notify all the other tasks to stop.
                AbortTasks = true;

                return;
            }

            ProgressReporter.Update(localIndirectPhotons.size() + 
                localCausticPhotons.size());
            ShotCount += blockSize;

            // Merge direct and indirect photons into shared array.
            if( !indirectDone )
            {
                PhotonMapShader->IndirectPathsCount += blockSize;
                for( SE_UInt32 i = 0; i < localIndirectPhotons.size(); ++i )
                {
                    IndirectPhotons.push_back(localIndirectPhotons[i]);
                }
                localIndirectPhotons.erase(localIndirectPhotons.begin(),
                    localIndirectPhotons.end());

                if( IndirectPhotons.size() >= 
                    PhotonMapShader->IndirectPhotonsWantedCount )
                {
                    indirectDone = true;
                }

                DirectPathsCount += blockSize;
                for( SE_UInt32 i = 0; i < localDirectPhotons.size(); ++i )
                {
                    DirectPhotons.push_back(localDirectPhotons[i]);
                }
                localDirectPhotons.erase(localDirectPhotons.begin(),
                    localDirectPhotons.end());
            }

            // Merge caustic, and radiance photons into shared array.
            if( !causticDone )
            {
                PhotonMapShader->CausticPathsCount += blockSize;
                for( SE_UInt32 i = 0; i < localCausticPhotons.size(); ++i )
                {
                    CausticPhotons.push_back(localCausticPhotons[i]);
                }
                localCausticPhotons.erase(localCausticPhotons.begin(), 
                    localCausticPhotons.end());

                if( CausticPhotons.size() >= 
                    PhotonMapShader->CausticPhotonsWantedCount )
                {
                    causticDone = true;
                }
            }
        
            for( SE_UInt32 i = 0; i < localRadiancePhotons.size(); ++i )
            {
                RadiancePhotons.push_back(localRadiancePhotons[i]);
            }
            localRadiancePhotons.erase(localRadiancePhotons.begin(), 
                localRadiancePhotons.end());

            for( SE_UInt32 i = 0; i < localRpReflectances.size(); ++i )
            {
                RadiancePhotonReflectances.push_back(localRpReflectances[i]);
            }
            localRpReflectances.erase(localRpReflectances.begin(), 
                localRpReflectances.end());

            for( SE_UInt32 i = 0; i < localRpTransmittances.size(); ++i )
            {
                RadiancePhotonTransmittances.push_back(
                    localRpTransmittances[i]);
            }
            localRpTransmittances.erase(localRpTransmittances.begin(), 
                localRpTransmittances.end());

            // End mutex scope.
        }

        // Exit task if enough photons have been found.
        if( indirectDone && causticDone )
        {
            break;
        }
    }
}