void InitVirtualDriveDialog::checkDownloadProgress()
{
    // First check for error
    std::vector<CloneTask> tasks;
    if (seafApplet->rpcClient()->getCloneTasks(&tasks) < 0) {
        return;
    }

    CloneTask task;
    for (size_t i = 0; i < tasks.size(); i++) {
        if (tasks[i].repo_id == default_repo_id_) {
            task = tasks[i];
            break;
        }
    }

    if (!task.isValid()) {
        return;
    }

    if (task.state != "done" && task.state != "error") {
        return;
    }

    check_download_timer_->stop();

    mRunInBackgroundBtn->setVisible(false);
    ensureVisible();

    if (task.state == "error") {
        fail(tr("Error when downloading the default library: %1").arg(task.error_str));
        return;
    }

    // Download is finished. Create the virutal disk in "My Computer".
    LocalRepo repo;
    seafApplet->rpcClient()->getLocalRepo(default_repo_id_, &repo);
    createVirtualDisk(repo);
    default_repo_path_ = repo.worktree;
    finish();
}