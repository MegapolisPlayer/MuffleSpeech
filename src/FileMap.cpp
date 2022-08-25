#include "FileMap.h"

namespace MuffleSpeech {
	void FindFiles(FileMap* aFileMap) {
		uint64_t lSelection = 1;
		std::putchar('r');
		for(const auto & entry : std::filesystem::directory_iterator(".")) {
			if(entry.path().extension() == ".mfsp") {
				aFileMap->Map.push_back(FileMapEntry(entry.path().filename().string(), lSelection, FileMapEntryType::ROOT));
				std::putchar('F');
				lSelection++;
			}
		}
		std::putchar('p');
		for(const auto & entry : std::filesystem::directory_iterator("./profiles/")) {
			if(entry.path().extension() == ".mfsp") {
				aFileMap->Map.push_back(FileMapEntry(entry.path().filename().string(), lSelection, FileMapEntryType::PATH));
				std::putchar('F');
				lSelection++;
			}
		}
		if(aFileMap->Map.size() == 0) {
			std::cout << "No profiles found, exiting.\n";
		}
	}
	void PrintFiles(const FileMap* aFileMap) {
		std::putchar('\n');
		for(int i = 0; i < aFileMap->Map.size(); i++) {
			std::cout << aFileMap->Map[i].FileId << ") (";
			switch(aFileMap->Map[i].EntryType) {
				case(FileMapEntryType::ROOT):
					std::putchar('R');
					break;
				case(FileMapEntryType::PATH):
					std::putchar('P');
					break;
				default:
					std::putchar('?');
			}
			std::cout << ") " << aFileMap->Map[i].FileName << "\n";
		}
	}
	uint64_t SelectFile(const FileMap* aFileMap) {
		uint64_t lSelection;
		while(true) {
			std::cout << "Please select profile from above options. Input 0 to exit.\nmfsp>";
			std::cin >> lSelection;
			if(lSelection == 0) {
				std::cout << "Exiting MuffleSpeech...\n";
				return 0;
			}
			for(int i = 0; i < aFileMap->Map.size(); i++) {
				if(aFileMap->Map[i].FileId == lSelection) {
					std::cout << "Selected " << aFileMap->Map[i].FileName << "\n";
					return lSelection;
				}
			}
			std::cout << "Invalid selection, please try again.\n";
		}
	}
}
