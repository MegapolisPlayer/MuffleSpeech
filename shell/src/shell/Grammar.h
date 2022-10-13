#ifndef MUFFLESPEECH_SHELLGRAMMAR
#define MUFFLESPEECH_SHELLGRAMMAR
#include <MS/MFSP.h>

namespace MuffleSpeech {
	namespace Shell {
		//returns id of most similar string in array
		//strings MUST be null-terminated
		uint64_t FindMostSimilar(const char* aCompareWhat, const char** aStrings, uint64_t aStringAmount);
		//returns id of most similar string in array
		uint64_t FindMostSimilar(std::string aCompareWhat, std::vector<std::string> aStrings);
	}
}

#endif
