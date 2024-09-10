/**
 *
 * Core function which takes care of deployment in Linux.
 * Essentially it does
 * - uncabing of the cabinet
 * - execution of the command embedded in the cabinet header
 *
 * @param   [IN[  packageName  Package file to be used for deployment
 * @returns DEPLOYPKG_STATUS_SUCCESS on success
 *          DEPLOYPKG_STATUS_CLOUD_INIT_DELEGATED if customization task is
 *          delegated to cloud-init.
 *          DEPLOYPKG_STATUS_ERROR on error
 *
 **/
static DeployPkgStatus
Deploy(const char* packageName)
{
   DeployPkgStatus deployPkgStatus = DEPLOYPKG_STATUS_SUCCESS;
   char* pkgCommand = NULL;
   char* command = NULL;
   int deploymentResult = 0;
   char *nics;
   char* cleanupCommand;
   uint8 archiveType;
   uint8 flags;
   bool forceSkipReboot = false;
   const char *baseDirPath = NULL;
   char *imcDirPath = NULL;
   bool useCloudInitWorkflow = false;

   TransitionState(NULL, INPROGRESS);

   // Notify the vpx of customization in-progress state
   SetCustomizationStatusInVmx(TOOLSDEPLOYPKG_RUNNING,
                               TOOLSDEPLOYPKG_ERROR_SUCCESS,
                               NULL);

   // PR 2127543, Use /var/run or /run but /tmp firstly
   if (File_IsDirectory(VARRUNDIR)) {
      baseDirPath = VARRUNDIR;
   } else if (File_IsDirectory(RUNDIR)) {
      baseDirPath = RUNDIR;
   } else {
      baseDirPath = TMPDIR;
   }

   // Create a random name dir under base dir path
   imcDirPath = malloc(strlen(baseDirPath) + strlen(IMC_DIR_PATH_PATTERN) + 1);
   if (imcDirPath == NULL) {
      SetDeployError("Error allocating memory to create imc dir.");
      return DEPLOYPKG_STATUS_ERROR;
   }
   strcpy(imcDirPath, baseDirPath);
   strcat(imcDirPath, IMC_DIR_PATH_PATTERN);
   if (mkdtemp(imcDirPath) == NULL) {
      free(imcDirPath);
      SetDeployError("Error creating imc dir: %s", strerror(errno));
      return DEPLOYPKG_STATUS_ERROR;
   }

   sLog(log_info,
        "Reading cabinet file %s and will extract it to %s. \n",
         packageName,
         imcDirPath);

   // Get the command to execute
   if (!GetPackageInfo(packageName, &pkgCommand, &archiveType, &flags)) {
      SetDeployError("Error extracting package header information. (%s)",
                     GetDeployError());
      free(imcDirPath);
      return DEPLOYPKG_STATUS_CAB_ERROR;
   }

   sLog(log_info, "Flags in the header: %d\n", (int) flags);

   sLog(log_info, "Original deployment command: %s\n", pkgCommand);
   if (strstr(pkgCommand, IMC_TMP_PATH_VAR) != NULL) {
      command = StrUtil_ReplaceAll(pkgCommand, IMC_TMP_PATH_VAR, imcDirPath);
   } else {
      command = StrUtil_ReplaceAll(pkgCommand, TMP_PATH_VAR, imcDirPath);
   }
   free(pkgCommand);

   sLog(log_info, "Actual deployment command: %s\n", command);

   if (archiveType == VMWAREDEPLOYPKG_PAYLOAD_TYPE_CAB) {
      if (!ExtractCabPackage(packageName, imcDirPath)) {
         free(imcDirPath);
         free(command);
         return DEPLOYPKG_STATUS_CAB_ERROR;
      }
   } else if (archiveType == VMWAREDEPLOYPKG_PAYLOAD_TYPE_ZIP) {
      if (!ExtractZipPackage(packageName, imcDirPath)) {
         free(imcDirPath);
         free(command);
         return DEPLOYPKG_STATUS_CAB_ERROR;
      }
   }

   if (!(flags & VMWAREDEPLOYPKG_HEADER_FLAGS_IGNORE_CLOUD_INIT)) {
      useCloudInitWorkflow = UseCloudInitWorkflow(imcDirPath);
   } else {
      sLog(log_info, "Ignoring cloud-init.");
   }

   if (useCloudInitWorkflow) {
      sLog(log_info, "Executing cloud-init workflow");
      sSkipReboot = TRUE;
      free(command);
      deployPkgStatus = CloudInitSetup(imcDirPath);
   } else {
      sLog(log_info, "Executing traditional GOSC workflow");
      deploymentResult = ForkExecAndWaitCommand(command, false);
      free(command);

      if (deploymentResult != CUST_SUCCESS) {
         sLog(log_error, "Customization process returned with error. \n");
         sLog(log_debug, "Deployment result = %d \n", deploymentResult);

         if (deploymentResult == CUST_NETWORK_ERROR ||
             deploymentResult == CUST_NIC_ERROR ||
             deploymentResult == CUST_DNS_ERROR) {
            sLog(log_info, "Setting network error status in vmx. \n");
            SetCustomizationStatusInVmx(TOOLSDEPLOYPKG_RUNNING,
                                        GUESTCUST_EVENT_NETWORK_SETUP_FAILED,
                                        NULL);
         } else {
            sLog(log_info, "Setting %s error status in vmx. \n",
                 deploymentResult == CUST_GENERIC_ERROR ? "generic" : "unknown");
            SetCustomizationStatusInVmx(TOOLSDEPLOYPKG_RUNNING,
                                        GUESTCUST_EVENT_CUSTOMIZE_FAILED,
                                        NULL);
         }

         TransitionState(INPROGRESS, ERRORED);

         deployPkgStatus = DEPLOYPKG_STATUS_ERROR;
         SetDeployError("Deployment failed. "
                        "The forked off process returned error code.");
         sLog(log_error, "Deployment failed. "
                         "The forked off process returned error code. \n");
      } else {
         nics = GetNicsToEnable(imcDirPath);
         if (nics) {
            // XXX: Sleep before the last SetCustomizationStatusInVmx
            //      This is a temporary-hack for PR 422790
            sleep(5);
            sLog(log_info, "Wait before set enable-nics stats in vmx.\n");

            TryToEnableNics(nics);

            free(nics);
         } else {
            sLog(log_info, "No nics to enable.\n");
         }

         SetCustomizationStatusInVmx(TOOLSDEPLOYPKG_DONE,
                                     TOOLSDEPLOYPKG_ERROR_SUCCESS,
                                     NULL);

         TransitionState(INPROGRESS, DONE);

         deployPkgStatus = DEPLOYPKG_STATUS_SUCCESS;
         sLog(log_info, "Deployment succeeded. \n");
      }
   }

   cleanupCommand = malloc(strlen(CLEANUPCMD) + strlen(imcDirPath) + 1);
   if (!cleanupCommand) {
      SetDeployError("Error allocating memory.");
      free(imcDirPath);
      return DEPLOYPKG_STATUS_ERROR;
   }

   strcpy(cleanupCommand, CLEANUPCMD);
   strcat(cleanupCommand, imcDirPath);

   sLog(log_info, "Launching cleanup. \n");
   if (ForkExecAndWaitCommand(cleanupCommand, false) != 0) {
      sLog(log_warning, "Error while cleaning up imc directory %s: (%s)",
           imcDirPath, strerror (errno));
   }
   free (cleanupCommand);
   free(imcDirPath);

   if (flags & VMWAREDEPLOYPKG_HEADER_FLAGS_SKIP_REBOOT) {
      forceSkipReboot = true;
   }
   sLog(log_info,
        "sSkipReboot: %s, forceSkipReboot %s\n",
        sSkipReboot ? "true" : "false",
        forceSkipReboot ? "true" : "false");
   sSkipReboot |= forceSkipReboot;

   //Reset the guest OS
   if (!sSkipReboot && !deploymentResult) {
      pid_t pid = fork();
      if (pid == -1) {
         sLog(log_error, "Failed to fork: %s", strerror(errno));
      } else if (pid == 0) {
         // We're in the child

         // Repeatedly try to reboot to workaround PR 530641 where
         // telinit 6 is overwritten by a telinit 2
         int rebootComandResult = 0;
         do {
            sLog(log_info, "Rebooting\n");
            rebootComandResult = ForkExecAndWaitCommand("/sbin/telinit 6", false);
            sleep(1);
         } while (rebootComandResult == 0);
         sLog(log_error, "telinit returned error %d\n", rebootComandResult);

         exit (127);
      }
   }

   return deployPkgStatus;
}