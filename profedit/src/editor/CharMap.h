#ifndef PROFILEEDITOR_CHARMAP
#define PROFILEEDITOR_CHARMAP
#include "../boot/Boot.h"

namespace ProfileEditor {
	//1 string change pair
	struct CharMapEntry {
		char In[3] = {0, 0, 0};
		char Out[3] = {0, 0, 0};
		
		CharMapEntry();
		CharMapEntry(const char (&aIn)[3], const char (&aOut)[3]);
		void Update(const char (&aIn)[3], const char (&aOut)[3]);
		void UpdateIn(const char (&aNew)[3]);
		void UpdateOut(const char (&aNew)[3]);
		void PrintIn() const;
		void PrintOut() const;
	};
	enum struct CharMapChangeDest {
		UNINIT = -1,
		INPUT,
		OUTPUT
	};
	//Query to change a CharMapEntry
	struct CharMapChange {
		uint64_t Id;
		CharMapChangeDest Destination;
		char New[3] = {0, 0, 0};
		
		CharMapChange();
		CharMapChange(uint64_t aId, CharMapChangeDest aDest, const char (&aNew)[3]);
		void Update(uint64_t aId, CharMapChangeDest aDest, const char (&aNew)[3]);
	};
	//comparison of CharMapEntries for std::sort
	bool AlphabeticCompare(const CharMapEntry& aFirst, const CharMapEntry& aSecond);
	//CharMapEntry vector with some extra functionality
	struct CharMap {
		std::vector<CharMapEntry> Map;
		
		void Change(const CharMapChange aChange);
		
		void Print();
	};
}

#endif
