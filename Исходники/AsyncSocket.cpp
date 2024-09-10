// ソケットを強制的に閉じる
// ポストされたメッセージが残る可能性があるのでなるべくShutdown()を使う
void CAsyncSocket::Close()
{
	if (hGethost_) {
		WSACancelAsyncRequest(hGethost_);
		hGethost_ = NULL;
	}
	if (soc_ != INVALID_SOCKET) {
		closesocket(soc_);
		soc_ = INVALID_SOCKET;
	}
	bReady_ = false;
	bShutdown_ = false;
}