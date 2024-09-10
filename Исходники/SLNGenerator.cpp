// WriteProjectListings
//------------------------------------------------------------------------------
void SLNGenerator::WriteProjectListings(    const AString& solutionBasePath,
        const AString& solutionBuildProject,
        const Array< VCXProjectNode * > & projects,
        const Array< SLNSolutionFolder > & folders,
        const Array< SLNDependency > & slnDeps,
        AString & solutionBuildProjectGuid,
        Array< AString > & projectGuids,
        Array< AString > & solutionProjectsToFolder )
{
    // Project Listings

    VCXProjectNode ** const projectsEnd = projects.End();
    for( VCXProjectNode ** it = projects.Begin() ; it != projectsEnd ; ++it )
    {
        // check if this project is the master project
        const bool projectIsActive = ( solutionBuildProject.CompareI( (*it)->GetName() ) == 0 );

        AStackString<> projectPath( (*it)->GetName() );

        // get project base name only
        const char * lastSlash  = projectPath.FindLast( NATIVE_SLASH );
        const char * lastPeriod = projectPath.FindLast( '.' );
        AStackString<> projectName( lastSlash  ? lastSlash + 1  : projectPath.Get(),
                                    lastPeriod ? lastPeriod		: projectPath.GetEnd() );

        // retrieve projectGuid
        AStackString<> projectGuid;
        if ( (*it)->GetProjectGuid().GetLength() == 0 )
        {
            // For backward compatibility, keep the preceding slash and .vcxproj extension for GUID generation
            AStackString<> projectNameForGuid( lastSlash ? lastSlash : projectPath.Get() );
            VSProjectGenerator::FormatDeterministicProjectGUID( projectGuid, projectNameForGuid );
        }
        else
        {
            projectGuid = (*it)->GetProjectGuid();
        }

        // make project path relative
        projectPath.Replace( solutionBasePath.Get(), "" );

        // projectGuid must be uppercase (visual does that, it changes the .sln otherwise)
        projectGuid.ToUpper();

        if ( projectIsActive )
        {
            ASSERT( solutionBuildProjectGuid.GetLength() == 0 );
            solutionBuildProjectGuid = projectGuid;
        }

        Write( "Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"%s\", \"%s\", \"%s\"\r\n",
               projectName.Get(), projectPath.Get(), projectGuid.Get() );

        // Manage dependencies
        Array< AString > dependencyGUIDs( 64, true );
        const AString & fullProjectPath = (*it)->GetName();
        for ( const SLNDependency & deps : slnDeps )
        {
            // is the set of deps relevant to this project?
            if ( deps.m_Projects.Find( fullProjectPath ) )
            {
                // get all the projects this project depends on
                for ( const AString & dependency : deps.m_Dependencies )
                {
                    // For backward compatibility, keep the preceding slash and .vcxproj extension for GUID generation
                    const char * projNameFromSlash = dependency.FindLast( NATIVE_SLASH );
                    AStackString<> projectNameForGuid( projNameFromSlash ? projNameFromSlash : dependency.Get() );

                    AStackString<> newGUID;
                    VSProjectGenerator::FormatDeterministicProjectGUID( newGUID, projectNameForGuid );
                    dependencyGUIDs.Append( newGUID );
                }
            }
        }
        if ( !dependencyGUIDs.IsEmpty() )
        {
            Write( "\tProjectSection(ProjectDependencies) = postProject\r\n" );
            for ( const AString & guid : dependencyGUIDs )
            {
                Write( "\t\t%s = %s\r\n", guid.Get(), guid.Get() );
            }
            Write( "\tEndProjectSection\r\n" );
        }

        Write( "EndProject\r\n" );

        projectGuids.Append( projectGuid );

        // check if this project is in a solution folder
        const SLNSolutionFolder * const foldersEnd = folders.End();
        for ( const SLNSolutionFolder * it2 = folders.Begin() ; it2 != foldersEnd ; ++it2 )
        {
            // this has to be done here to have the same order of declaration (like visual)
            if ( it2->m_ProjectNames.Find( (*it)->GetName() ) )
            {
                // generate a guid for the solution folder
                AStackString<> solutionFolderGuid;
                VSProjectGenerator::FormatDeterministicProjectGUID( solutionFolderGuid, it2->m_Path );

                solutionFolderGuid.ToUpper();

                AStackString<> projectToFolder;
                projectToFolder.Format( "\t\t%s = %s\r\n", projectGuid.Get(), solutionFolderGuid.Get() );

                solutionProjectsToFolder.Append( projectToFolder );
            }
        }
    }
}