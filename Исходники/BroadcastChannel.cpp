  bool MainThreadRun() override
  {
    MOZ_ASSERT(NS_IsMainThread());

    nsIPrincipal* principal = GetPrincipalFromWorkerPrivate(mWorkerPrivate);
    if (!principal) {
      mRv.Throw(NS_ERROR_FAILURE);
      return true;
    }

    bool isNullPrincipal;
    mRv = principal->GetIsNullPrincipal(&isNullPrincipal);
    if (NS_WARN_IF(mRv.Failed())) {
      return true;
    }

    if (NS_WARN_IF(isNullPrincipal)) {
      mRv.Throw(NS_ERROR_FAILURE);
      return true;
    }

    mRv = PrincipalToPrincipalInfo(principal, &mPrincipalInfo);
    if (NS_WARN_IF(mRv.Failed())) {
      return true;
    }

    mRv = principal->GetOrigin(mOrigin);
    if (NS_WARN_IF(mRv.Failed())) {
      return true;
    }

    // Walk up to our containing page
    WorkerPrivate* wp = mWorkerPrivate;
    while (wp->GetParent()) {
      wp = wp->GetParent();
    }

    // Window doesn't exist for some kind of workers (eg: SharedWorkers)
    nsPIDOMWindowInner* window = wp->GetWindow();
    if (!window) {
      return true;
    }

    return true;
  }