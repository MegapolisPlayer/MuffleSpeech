#ifndef MUFFLESPEECH_FILEMAP
#define MUFFLESPEECH_FILEMAP
#include "File.h"

namespace MuffleSpeech {
	struct MFFN FileMapEntry {
		std::string Name;
		
		FileMapEntry();
		FileMapEntry(std::string aName);
	};
	struct MFFN FileMap {
		std::vector<FileMapEntry> Map;
		
		void Print() const;
		void PrintExtensive() const; //with title
		uint64_t Select() const; //print filemap and returns ID chosen
		
		void Detect(std::string aDirectory = ".");
	};
	
}

#endif
