#ifndef MUFFLESPEECH_CHARMAP
#define MUFFLESPEECH_CHARMAP
#include "../buffer/Buffer.h"

namespace MuffleSpeech {
	//1 string change pair
	struct MFFN CharMapEntry {
		char In[3] = {0, 0, 0};
		uint8_t InSize;
		char Out[3] = {0, 0, 0};
		uint8_t OutSize;
		
		CharMapEntry();
		CharMapEntry(const char (&aIn)[3], const char (&aOut)[3]);
		void PrintIn() const;
		void PrintOut() const;
	};
	//comparison of CharMapEntries for std::sort
	MFFN bool AlphabeticCompare(const CharMapEntry& aFirst, const CharMapEntry& aSecond);
	//CharMapEntry vector with some extra functionality
	struct MFFN CharMap {
		std::vector<CharMapEntry> Map;
		
		void Print();
		
		//Clears STRBUF after finishing
		void Apply(Buffer* aStrbuf, Buffer* aFinbuf) const;
		
		//File MUST be open. On failure returns -1
		int8_t Load(File* aFile);
	};
}

#endif
