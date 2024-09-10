Project *
App::CreateNewProject(const BMessage &settings)
{
	Project *proj = NULL;
	
	BString projectName, targetName, projectPath, templateName, pldName;
	int32 projectType, scmType;
	bool createFolder, populateProject = true;
	
	settings.FindString("name",&projectName);
	settings.FindString("target",&targetName);
	settings.FindInt32("type",&projectType);
	settings.FindString("path",&projectPath);
	settings.FindInt32("scmtype", &scmType);
	settings.FindBool("createfolder",&createFolder);
	settings.FindString("template", &templateName);
	settings.FindString("pldfile", &pldName);

	if (templateName.CountChars() > 0)
	{
		// Templates are now a directory with a TEMPLATEINFO file. All files in the
		// directory are copies, allowing for much greater flexibility than before.
		
		BString projectFileName(projectName);
		projectFileName << ".pld";
		
		DPath templatePath(gAppPath.GetFolder());
		templatePath << "Templates" << templateName;
		
		// Copy the contents of the chosen template folder to the project path
		DPath sourcePath(templatePath);
		DPath destPath(gProjectPath);
		
		if (createFolder)
		{
			destPath << projectName;
			create_directory(destPath.GetFullPath(), 0700);
		}
		
		BString wildcard("'");
		wildcard << sourcePath.GetFullPath() << "'/*";
		ShellHelper shell("cp -a ");
		shell << wildcard;
		shell.AddQuotedArg(destPath.GetFullPath());
		shell.Run();
		
		// The copy command copies *everything*, so we have to delete the
		// TEMPLATEINFO file.
		DPath templateInfo(destPath);
		templateInfo << "TEMPLATEINFO";
		BEntry infoEntry(templateInfo.GetFullPath());
		infoEntry.Remove();
		infoEntry.Unset();
		
		DPath finalPath;
		
		// Load project and set info or create one, if needed.
		
		// If the settings contain the name of a .pld project file, we'll search
		// for that first. Assuming that it exists, we'll rename that file to the
		// project name specified. If it doesn't exist or the .pld name is empty,
		// we'll create a new project with the appropriate name.
		
		// The pldname field comes from the TEMPLATEINFO file, which can designate
		// the main project file in a template. This allows a template to have
		// multiple project files, such as for the Tracker Add-on development framework
		// which has both a project file for generating the actual addon and another
		// one which is the testing framework.
		bool createProjFile = true;
		if (pldName.CountChars() > 0)
		{
			// If a .pld project file was specified in TEMPLATEINFO, check to see if
			// the file exists and rename it. If it doesn't exist, we'll create a new
			// file, and if a .pld file already exists with the intended name, we won't
			// do anything except tell the user what's happened.
			DPath oldPldNamePath(destPath);
			oldPldNamePath << pldName;
			BEntry oldPldNameEntry(oldPldNamePath.GetFullPath());
			
			DPath newPldNamePath(destPath);
			newPldNamePath << projectFileName;
			
			BEntry newPldNameEntry(newPldNamePath.GetFullPath());
			if (newPldNameEntry.Exists())
			{
				// createProjFile is false here only if there is a .pld file with the
				// user's chosen project name. If that is the case, we keep both files and
				// let the user sort it out.
				BString errMsg = B_TRANSLATE(
					"Project file '%projectname%.pld' already exists. The "
					"original file for this template is '%pldname%'. You'll need "
					"to open the project folder and figure out which one you wish to keep.");
				errMsg.ReplaceFirst("%projectname%", projectName);
				errMsg.ReplaceFirst("%pldname%", pldName);
				ShowAlert(errMsg);
				populateProject = createProjFile = false;
				
				finalPath = newPldNamePath;
			}
			else
			if (oldPldNameEntry.Exists())
			{
				oldPldNameEntry.Rename(projectFileName.String());
				populateProject = createProjFile = false;
				
				finalPath = newPldNamePath;
			}
		}
		
		if (createProjFile)
		{
			proj = Project::CreateProject(projectName.String(), targetName.String(),
									projectType, projectPath.String(), createFolder);
			if (proj)
				finalPath = proj->GetPath();
		}
		else
		{
			proj = new Project();
			if (proj->Load(finalPath.GetFullPath()) != B_OK)
			{
				delete proj;
				return NULL;
			}
		}
	}
	else
	{
		// This case is for stuff like the Quick Import feature
		proj = Project::CreateProject(projectName.String(), targetName.String(),
									projectType, projectPath.String(), createFolder);
	}
	
	if (!proj)
		return NULL;
	
	scm_t detectedSCM = DetectSCM(projectPath);
	proj->SetSourceControl(detectedSCM == SCM_NONE ? (scm_t)scmType : detectedSCM);
	
	gCurrentProject = proj;
	gProjectList->Lock();
	gProjectList->AddItem(proj);
	gProjectList->Unlock();
	
	BRect r(0,0,200,300);
	/*
	r.OffsetTo(gProjectWindowPoint);
	gProjectWindowPoint.x += 25;
	gProjectWindowPoint.y += 25;
	if (gProjectWindowPoint.x < 0)
		gProjectWindowPoint.x = 0;
	if (gProjectWindowPoint.y < 0)
		gProjectWindowPoint.y - 0;
		*/
	ProjectWindow *projwin = new ProjectWindow(r,gCurrentProject);
	projwin->Show();
	
	BEntry entry(gCurrentProject->GetPath().GetFullPath());
	if (entry.InitCheck() == B_OK)
	{
		entry_ref newprojref;
		entry.GetRef(&newprojref);
		UpdateRecentItems(newprojref);
	}
	
	if (populateProject)
	{
		entry_ref addRef;
		int32 i = 0;
		while (settings.FindRef("libs",i++,&addRef) == B_OK)
		{
			if (BEntry(&addRef).Exists())
				proj->AddLibrary(DPath(addRef).GetFullPath());
		}
		
		i = 0;
		BMessage addMsg(M_IMPORT_REFS);
		while (settings.FindRef("refs",i++,&addRef) == B_OK)
			addMsg.AddRef("refs",&addRef);
		PostToProjectWindow(&addMsg,NULL);
	}
	
	return proj;
}