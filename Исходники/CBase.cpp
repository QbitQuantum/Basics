CEventAction::CEventAction( const CEventAction &p_EventAction )
{
	m_pNext = NULL;
	m_iIDStamp = ++s_iNextIDStamp;

	m_flDelay = p_EventAction.m_flDelay;
	m_iTarget = p_EventAction.m_iTarget;
	m_iParameter = p_EventAction.m_iParameter;
	m_iTargetInput = p_EventAction.m_iTargetInput;
	m_nTimesToFire = p_EventAction.m_nTimesToFire;
}


// this memory pool stores blocks around the size of CEventAction/inputitem_t structs
// can be used for other blocks; will error if to big a block is tried to be allocated
CUtlMemoryPool g_EntityListPool( MAX(sizeof(CEventAction),sizeof(CMultiInputVar::inputitem_t)), 512, CUtlMemoryPool::GROW_FAST, "g_EntityListPool" );

#include "tier0/memdbgoff.h"

void *CEventAction::operator new( size_t stAllocateBlock )
{
	return g_EntityListPool.Alloc( stAllocateBlock );
}

void *CEventAction::operator new( size_t stAllocateBlock, int nBlockUse, const char *pFileName, int nLine )
{
	return g_EntityListPool.Alloc( stAllocateBlock );
}

void CEventAction::operator delete( void *pMem )
{