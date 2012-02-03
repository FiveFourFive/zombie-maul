////////////////////////////////////////////////
//	File	:	"CObjectManager.cpp"
//
//	Author	:	Wade Shwallon
//
//	Purpose	:	contains and managse all game objects.
/////////////////////////////////////////////////

#include "CObjectManager.h"
#include "CSGD_Direct3D.h"
#include "CBase.h"
#include "CPlayer.h"
#include "CHuman.h"
#include "AnimationManager.h"
#include "Guard.h"

CObjectManager* CObjectManager::m_pInstance = NULL;

CObjectManager::CObjectManager(void)
{

}

CObjectManager::~CObjectManager(void)
{

}

CObjectManager* CObjectManager::GetInstance(void)
{
	if(m_pInstance == NULL)
		m_pInstance = new CObjectManager();
	return m_pInstance;
}

void CObjectManager::DeleteInstance(void)
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CObjectManager::UpdateObjects(float fElapsedTime)
{
	vector<IBaseInterface*>::iterator iter = m_vObjectList.begin();
	CheckCollisions();
	while(iter != m_vObjectList.end())
	{
		(*iter)->Update(fElapsedTime);
		iter++;
	}
}

void CObjectManager::RenderObjects(void)
{
	for(size_t i = 0; i < m_vObjectList.size(); i++)
	{
		m_vObjectList[i]->Render();
	}
}

void CObjectManager::AddObject(IBaseInterface* pObject)
{
	if(pObject == NULL)
		return;
	
	m_vObjectList.push_back(pObject);

	pObject->AddRef();
}

void CObjectManager::RemoveObject(IBaseInterface* pObject)
{
	if(pObject == NULL)
		return;
	vector<IBaseInterface*>::iterator iter = m_vObjectList.begin();
	for(; iter != m_vObjectList.end(); iter++)
	{
		if((*iter) == pObject)
		{
			(*iter)->Release();

			iter = m_vObjectList.erase(iter);
			break;
		}
	}

}

void CObjectManager::RemoveAllObjects(void)
{
	for(size_t i = 0; i < m_vObjectList.size(); i++)
	{
		m_vObjectList[i]->Release();
	}
	m_vObjectList.clear();

}

void CObjectManager::CheckCollisions()
{
	int ret;
	for(size_t i = 0; i < m_vObjectList.size(); i++)
	{
		for(size_t m = 0; m < m_vObjectList.size(); m++)
		{
			if(m_vObjectList[i] != m_vObjectList[m])
			{
				ret = m_vObjectList[i]->CheckCollision(m_vObjectList[m]);
				if(ret != 4)
					break;
			}
		}

	}
}

void CObjectManager::DrawObjects(void)
{
	CBase* pbase;
	for(size_t i = 0; i < m_vObjectList.size(); i++)
	{
		pbase =  (CBase*)m_vObjectList[i];
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
			RECT r = { (LONG)(600 + pbase->GetPosX() * 0.108f),
			(LONG)(452 + pbase->GetPosY() * 0.104f),
			r.left + 2,
			r.top + 2 };
			
			if(pbase->GetType() == type::OBJECT_PLAYER)
			{
				CPlayer* player = (CPlayer*)pbase;
					AnimManager::GetInstance()->Render( player->GetAnimID(), 
					(int)(600 + pbase->GetPosX() * 0.108f),(int)(452 + pbase->GetPosY() * 0.104f), 
					0.25f, 0.25f, player->GetRot() );
			}
			else if(pbase->GetType() == type::OBJECT_HUMAN || pbase->GetType() == type::OBJECT_ZOMBIE)
			{
				CHuman* human = (CHuman*)pbase;
					AnimManager::GetInstance()->Render( human->GetAnimID(), 
					(int)(600 + human->GetPosX() * 0.108f),(int)(452 + human->GetPosY() * 0.104f), 
					0.25f, 0.25f, human->GetRotation() );
				
			}
			else if(pbase->GetType() == type::OBJECT_GUARD)
			{
				CGuard* guard = (CGuard*)pbase;
				AnimManager::GetInstance()->Render( guard->GetAnimID(), 
					(int)(600 + guard->GetPosX() * 0.108f),(int)(452 + guard->GetPosY() * 0.104f), 
					0.25f, 0.25f, guard->GetRotation() );
			}
	}
}