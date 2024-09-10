int condvar_wait(struct condvar_handle *condvar, struct mutex_handle *mutex)
{
	struct condvar_priv *priv = (struct condvar_priv *)condvar->priv;
	struct mutex_priv *mpriv = (struct mutex_priv *)mutex->priv;

	if (!SleepConditionVariableSRW(&priv->cond, &mpriv->lock, INFINITE, 0))
	{
		return GetLastError();
	}

	return 0;
}