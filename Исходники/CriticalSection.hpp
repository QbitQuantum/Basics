	~CriticalSectionScope(){
		critSec->Exit();
	}