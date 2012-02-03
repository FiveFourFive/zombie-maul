#include "CAudioState.h"
#include "COptionsState.h"
#include "CMainMenuState.h"
#include "CGame.h"

#include "CSGD_TextureManager.h"
#include "CSGD_FModManager.h"
#include "CSGD_DirectInput.h"
#include "CSGD_Direct3D.h"
#include "CPrintFont.h"

//#include <stdio.h>
#include "tinyxml.h"

enum Volume { MUSIC, SOUND_FX, PANNING, EXIT, NUM_STATES};

CAudioState::CAudioState()
{
	m_pTM = NULL;
	m_pFM = NULL;
	m_pDI = NULL;
	m_pPF = NULL;
}

CAudioState::~CAudioState()
{

}

CAudioState::CAudioState( const CAudioState&)
{

}

CAudioState& CAudioState::operator = (const CAudioState&)
{
	return *this;
}

CAudioState* CAudioState::GetInstance()
{
	static CAudioState instance;
	return &instance;
}

void CAudioState::Enter(void)
{
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pFM = CSGD_FModManager::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();

	m_nFontID = m_pTM->LoadTexture("resource/Font.png",D3DCOLOR_XRGB(0, 0, 0));
	m_pPF = new CPrintFont(m_nFontID);

	arrowID = m_pTM->LoadTexture("resource/arrow.jpg", D3DCOLOR_XRGB(0,0,0));

	m_nMenuMove = CGame::GetInstance()->GetMenuMoveID();
	m_nMenuSelect = CGame::GetInstance()->GetMenuSelectID();
	m_nMenuCancel = CGame::GetInstance()->GetMenuCancelID();
}

void CAudioState::Exit(void)
{
	Save("resource/AudioSettings.xml");
	m_pTM->UnloadTexture(m_nFontID);
	delete m_pPF;
}

bool CAudioState::Input(void)
{
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		return this->HandleEnter();
	}
	
	if(m_pDI->KeyPressed(DIK_UP))
	{
		m_nSelection--;
		if(m_nSelection < 0)
			m_nSelection = (NUM_STATES - 1);
		m_pFM->PlaySoundA(m_nMenuMove);

	}

	if(m_pDI->KeyPressed(DIK_DOWN))
	{
		m_nSelection++;
		if(m_nSelection > (NUM_STATES - 1))
			m_nSelection = 0;
		m_pFM->PlaySoundA(m_nMenuMove);

	}

	if( m_pDI->KeyPressed(DIK_RIGHT) )
	{
		switch(m_nSelection)
		{
		case MUSIC:
			if( CGame::GetInstance()->getSoundAVolume() < 100)
			{
				CGame::GetInstance()->SetSoundAVolume(CGame::GetInstance()->getSoundAVolume() + 10);
				float vol = (CGame::GetInstance()->getSoundAVolume() / 100.0f);
				m_pFM->SetVolume( CMainMenuState::GetInstance()->GetBackgroundMusicID(), vol);
				m_pFM->PlaySoundA(m_nMenuSelect);

			}
			break;
		case SOUND_FX:
			if( CGame::GetInstance()->getSoundBVolume() < 100)
			{
				CGame::GetInstance()->SetSoundBVolume(CGame::GetInstance()->getSoundBVolume() + 10);
				float vol = (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f);
				m_pFM->SetVolume(CGame::GetInstance()->GetMenuMoveID(), vol);
				m_pFM->SetVolume(CGame::GetInstance()->GetMenuSelectID(), vol);
				m_pFM->SetVolume(CGame::GetInstance()->GetMenuCancelID(), vol);
				m_pFM->PlaySoundA(m_nMenuSelect);
			}

			break;
		case PANNING:
			if( CGame::GetInstance()->getPanning() < 100)
			{
				CGame::GetInstance()->SetPanning(CGame::GetInstance()->getPanning() + 10);
				float pan = (float)(CGame::GetInstance()->getPanning() / 100.0f);
				m_pFM->SetPan(CGame::GetInstance()->GetMenuMoveID(), pan);
				m_pFM->SetPan(CGame::GetInstance()->GetMenuSelectID(), pan);
				m_pFM->SetPan(CGame::GetInstance()->GetMenuCancelID(), pan);
				m_pFM->SetPan( CMainMenuState::GetInstance()->GetBackgroundMusicID(), pan);

				m_pFM->PlaySoundA(m_nMenuSelect);
			}
			break;
		}

	}
	if( m_pDI->KeyPressed(DIK_LEFT) )
	{
		switch(m_nSelection)
		{
		case MUSIC:
			if( CGame::GetInstance()->getSoundAVolume() > 0)
			{
				CGame::GetInstance()->SetSoundAVolume(CGame::GetInstance()->getSoundAVolume() - 10);
				float vol = (CGame::GetInstance()->getSoundAVolume() / 100.0f);
				m_pFM->SetVolume( CMainMenuState::GetInstance()->GetBackgroundMusicID(), vol);
				m_pFM->PlaySoundA(m_nMenuSelect);
			}
			break;
		case SOUND_FX:
			if( CGame::GetInstance()->getSoundBVolume() > 0)
			{
				CGame::GetInstance()->SetSoundBVolume(CGame::GetInstance()->getSoundBVolume() - 10);
				float vol = (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f);
				m_pFM->SetVolume(CGame::GetInstance()->GetMenuMoveID(), vol);
				m_pFM->SetVolume(CGame::GetInstance()->GetMenuSelectID(), vol);
				m_pFM->SetVolume(CGame::GetInstance()->GetMenuCancelID(), vol);
				m_pFM->PlaySoundA(m_nMenuSelect);
			}
			break;
		case PANNING:
			if( CGame::GetInstance()->getPanning() > -100)
			{
				CGame::GetInstance()->SetPanning(CGame::GetInstance()->getPanning() - 10);
				float pan = (float)(CGame::GetInstance()->getPanning() / 100.0f);
				m_pFM->SetPan(CGame::GetInstance()->GetMenuMoveID(), pan);
				m_pFM->SetPan(CGame::GetInstance()->GetMenuSelectID(), pan);
				m_pFM->SetPan(CGame::GetInstance()->GetMenuCancelID(), pan);
				m_pFM->SetPan( CMainMenuState::GetInstance()->GetBackgroundMusicID(), pan);

				m_pFM->PlaySoundA(m_nMenuSelect);
			}
			break;
		}
	}
	return true;
}

void CAudioState::Update(float fElapsedTime)
{
	m_pFM->Update();
}

void CAudioState::Render(void)
{
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	RECT r = { 0, 0, 800, 600 };
	CSGD_Direct3D::GetInstance()->DrawRect(r, 0,0,0);

	m_pPF->PrintCentered("Zombie Mall",400,50,1.0f,D3DCOLOR_XRGB(200, 0, 0));
	m_pPF->PrintCentered("v1.0",400,100,1.0f,D3DCOLOR_XRGB(200, 0, 0));

	m_pPF->Print("MUSIC",200,200,0.5f,D3DCOLOR_XRGB(200, 0, 0));
	m_pPF->Print("SOUND FX",200,250,0.5f,D3DCOLOR_XRGB(200, 0, 0));
	m_pPF->Print("PANNING",200,300,0.5f,D3DCOLOR_XRGB(200, 0, 0));
	m_pPF->Print("EXIT",200,350,0.5f,D3DCOLOR_XRGB(200, 0, 0));

	char text[50];
	sprintf_s(text, "Volume: %i", CGame::GetInstance()->getSoundAVolume());
	m_pPF->Print(text,350,200,0.5f,D3DCOLOR_XRGB(200, 0, 0));

	sprintf_s(text, "Volume: %i", CGame::GetInstance()->getSoundBVolume());
	m_pPF->Print(text,350,250,0.5f,D3DCOLOR_XRGB(200, 0, 0));

	sprintf_s(text, "Volume: %i", CGame::GetInstance()->getPanning());
	m_pPF->Print(text,350,300,0.5f,D3DCOLOR_XRGB(200, 0, 0));

	switch(m_nSelection)
		{
		case MUSIC:			
			m_pPF->Print("MUSIC",200,200,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			sprintf_s(text, "Volume: %i", CGame::GetInstance()->getSoundAVolume());
			m_pPF->Print(text,350,200,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			m_pTM->Draw(arrowID, 320, 193, 0.05f, 0.05f, NULL, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
			m_pTM->Draw(arrowID, 520, 193, -0.05f, 0.05f, NULL, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
			break;
		case SOUND_FX:
			m_pPF->Print("SOUND FX",200,250,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			sprintf_s(text, "Volume: %i", CGame::GetInstance()->getSoundBVolume());
			m_pPF->Print(text,350,250,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			m_pTM->Draw(arrowID, 320, 243, 0.05f, 0.05f, NULL, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
			m_pTM->Draw(arrowID, 520, 243, -0.05f, 0.05f, NULL, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
			break;
		case PANNING:
			m_pPF->Print("PANNING",200,300,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			sprintf_s(text, "Volume: %i", CGame::GetInstance()->getPanning());
			m_pPF->Print(text,350,300,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			m_pTM->Draw(arrowID, 320, 293, 0.05f, 0.05f, NULL, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
			m_pTM->Draw(arrowID, 520, 293, -0.05f, 0.05f, NULL, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
			break;
		case EXIT:
			m_pPF->Print("EXIT",200,350,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			break;
		}
}

bool CAudioState::HandleEnter(void)
{
	switch(m_nSelection)
		{
		case MUSIC:
			break;
		case SOUND_FX:
			break;
		case PANNING:
			break;
		case EXIT:
			m_pFM->PlaySoundA(m_nMenuCancel);
			CGame::GetInstance()->RemoveState();
		}
	return true;
}

bool CAudioState::Save( const char* szFileName)
{
	// Declare the doc
	TiXmlDocument doc;

	// Establish the file header.
	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0", "utf-8", "");

	// Step1: Cut a hole in the box
	// Step2: Put your dec in the box
	doc.LinkEndChild(pDec);

	TiXmlElement* pRoot = new TiXmlElement("AudioSetting");
	doc.LinkEndChild(pRoot);

	TiXmlElement* usersettings = new TiXmlElement("user_settings");

	usersettings->SetDoubleAttribute("music_volume", CGame::GetInstance()->getSoundAVolume());
	usersettings->SetDoubleAttribute("sfx_volume", CGame::GetInstance()->getSoundBVolume());
	usersettings->SetDoubleAttribute("panning", CGame::GetInstance()->getPanning());

	pRoot->LinkEndChild(usersettings);

	if(doc.SaveFile(szFileName) == false)
		return false;

	return true;
}