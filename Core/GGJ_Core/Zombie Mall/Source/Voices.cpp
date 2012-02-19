#include "Voices.h"
#include "CGame.h"

CVoices::CVoices(void)
{
	m_nLastSoundPlayed = -1;
}


CVoices::~CVoices(void)
{
	CSGD_FModManager* fMod = CSGD_FModManager::GetInstance();

	for (unsigned int i = 0; i < voices.size(); i++)
	{
		fMod->UnloadSound(voices[i]);
	}

	voices.clear();
}

int CVoices::AddVoice(const char* filepath)
{
	int index = CSGD_FModManager::GetInstance()->LoadSound(filepath);
	CSGD_FModManager::GetInstance()->SetVolume(index, (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f));
	CSGD_FModManager::GetInstance()->SetPan(index, (float)(CGame::GetInstance()->getPanning()/100.0f));
	
	// Error check
	if (index == -1)
		return index;

	voices.push_back(index);

	return index;
}

void CVoices::PlayRandomClip()
{
	// Error Check
	if (voices.size() <= 0)
		return;

	// If something is talking, can not say something else
	if (CSGD_FModManager::GetInstance()->IsSoundPlaying(m_nLastSoundPlayed))
		return;

	int index = std::rand() % voices.size();

	CSGD_FModManager::GetInstance()->PlaySoundA(voices[index]);

	m_nLastSoundPlayed = voices[index];
}

void CVoices::PlayClip(int index)
{
	// COMMENT THIS OUT TO KEEP IT FROM BREAKING- NO TIME TO FIX

	//for (int i = 0; i < voices.size(); i++)
	//{
	//	if (voices[i] == index)
	//	{
	//		// If something is talking, can not say something else
	//		if (CSGD_FModManager::GetInstance()->IsSoundPlaying(m_nLastSoundPlayed))
	//			return;

	//		CSGD_FModManager::GetInstance()->PlaySoundA(index);

	//		m_nLastSoundPlayed = index;

	//		return;
	//	}
	//}
}