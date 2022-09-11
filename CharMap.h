#ifndef MUFFLESPEECH_CHARMAP
#define MUFFLESPEECH_CHARMAP
#include "FileMap.h"
#include "ShellHandler.h"

namespace MuffleSpeech {
	struct CharMapEntry {
		char In;
		char Out;
		CharMapEntry() : In(0), Out(0) {}
		CharMapEntry(char aIn, char aOut) : In(aIn), Out(aOut) {}
	};
	struct CharMap {
		std::vector<CharMapEntry> Map;
	};
	
	bool LoadCharMap(FileMapEntry* aFile, CharMap* aCharMap);
	void GenerateCapitals(CharMap* aCharMap);
	void PrintCharMap(const CharMap* aCharMap);
	void ApplyCharMap(std::string& aIO, const CharMap* aCharMap, const bool aLoggingEnabled = false);
	
	void LoadCharMaps(FileMap* aFileMap, CharMap* aCharMap);
}

#endif