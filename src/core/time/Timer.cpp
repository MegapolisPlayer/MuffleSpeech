#include "Timer.h"

namespace MuffleSpeech {
	ScopeTimer::ScopeTimer() {
		using namespace std::literals;
		this->mTimerName = "";
		this->mStart = std::chrono::system_clock::now();
		this->mDuration = 0ms;
		this->mIsPaused = false;
	}
	ScopeTimer::ScopeTimer(const char*&& aTimerName) {
		using namespace std::literals;
		this->mTimerName = aTimerName;
		this->mStart = std::chrono::system_clock::now();
		this->mDuration = 0ms;
		this->mIsPaused = false;
	}
	void ScopeTimer::Pause() {
		if(!this->mIsPaused) {
			this->mIsPaused = true;
			std::chrono::system_clock::time_point lEnd = std::chrono::system_clock::now();
			this->mDuration += lEnd - this->mStart;
		}
	}
	void ScopeTimer::Unpause() {
		if(this->mIsPaused) {
			this->mIsPaused = false;
			this->mStart = std::chrono::high_resolution_clock::now();
		}
	}
	ScopeTimer::~ScopeTimer() {
		std::chrono::system_clock::time_point lEnd = std::chrono::system_clock::now();
		std::chrono::milliseconds lMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>((lEnd - this->mStart) + this->mDuration);
		if(strlen(mTimerName) == 0) {
			std::cout << "Duration for timer: " << lMilliseconds.count() << "ms\n";
		}
		else {
			std::cout << "Duration for timer " << mTimerName << ": " << lMilliseconds.count() << "ms\n";
		}
	}
}
