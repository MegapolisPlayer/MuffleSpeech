#ifndef MUFFLESPEECH_TIMER
#define MUFFLESPEECH_TIMER
#include "../boot/Boot.h"

namespace MuffleSpeech {
	class ScopeTimer {
	public:
		ScopeTimer();
		ScopeTimer(const char*&& aTimerName);
		void Pause();
		void Unpause();
		~ScopeTimer();
	protected:
	private:
		const char* mTimerName;
		std::chrono::system_clock::time_point mStart;
		std::chrono::system_clock::duration mDuration;
		bool mIsPaused;
	};
}

#endif
