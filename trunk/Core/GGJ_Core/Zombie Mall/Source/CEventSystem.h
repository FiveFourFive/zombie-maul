/////////////////////////////////////////////////
//	File	:	"CEventSystem.h"
//
//	Author	:	Josh Fields
//
//	Purpose	:	Contains the functions for using events
//				
/////////////////////////////////////////////////

#ifndef _CEVENTSYSTEM_H_
#define _CEVENTSYSTEM_H_

#include <list>
//#include <map>
#include <vector>

//using std::multimap;
//using std::pair;

#include "CEvent.h"
#include "IListener.h"

class CEventSystem
{
private:
	
	//multimap<EVENTID, IListener*>	m_ClientDatabase;
	std::vector <EVENTID> m_ClientEvents;
	std::vector <IListener*> m_Clients;

	std::list<CEvent>		m_CurrentEvents;

	void DispatchEvent(CEvent* pEvent);
	bool AlreadyRegistered(EVENTID eventID, IListener* pClient);

	CEventSystem() {}
	CEventSystem(const CEventSystem&);
	CEventSystem& operator=(const CEventSystem&);

	~CEventSystem() {}

public:

	static CEventSystem* GetInstance(void);

	void RegisterClient(EVENTID eventID, IListener* pClient);
	void UnregisterClient(EVENTID eventID, IListener* pClient);
	void UnregisterClientAll(IListener* pClient);

	void SendEvent(EVENTID eventID, void* pData = NULL);
	void ProcessEvents(void);
	void ClearEvents(void);


	void ShutdownEventSystem(void);
};

#endif