#include "Grammar.h"

namespace MuffleSpeech {
	namespace Shell {
		uint64_t FindMostSimilar(const char* aCompareWhat, const char** aStrings, uint64_t aStringAmount) {
			uint64_t lTempBest = 0;
			double lTempBestScore = 0.0;
			for(uint64_t lId = 0; lId < aStringAmount; lId++) {
				double lWorkingScore = StringSameScore(aCompareWhat, aStrings[lId]);
				if(lWorkingScore > lTempBestScore) {
					lTempBest = lId;
					lTempBestScore = lWorkingScore;
				}
			}
			return lTempBest;
		}
		
		uint64_t FindMostSimilar(std::string aCompareWhat, std::vector<std::string> aStrings) {
			uint64_t lTempBest = 0;
			double lTempBestScore = 0.0;
			for(uint64_t lId = 0; lId < aStrings.size(); lId++) {
				double lWorkingScore = StringSameScore(aCompareWhat, aStrings[lId]);
				if(lWorkingScore > lTempBestScore) {
					lTempBest = lId;
					lTempBestScore = lWorkingScore;
				}
			}
			return lTempBest;
		}
	}
}
