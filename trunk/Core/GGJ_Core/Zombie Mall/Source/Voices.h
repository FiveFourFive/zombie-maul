#ifndef VOICES_H
#define VOICES_H

#include <vector>
#include "CSGD_FModManager.h"

class CVoices
{
private:
	std::vector<int> voices;
	int m_nLastSoundPlayed;

public:
	CVoices(void);
	~CVoices(void);

	int AddVoice(const char* filepath);

	void PlayRandomClip();

	void PlayClip(int index);

	inline int GetLastPlayed(void) { return m_nLastSoundPlayed; }
};

#endif