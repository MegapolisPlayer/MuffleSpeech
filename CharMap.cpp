#include "CharMap.h"

namespace MuffleSpeech {
	bool LoadCharMap(FileMapEntry* aFile, CharMap* aCharMap) {
		std::ifstream lIfstream;
		std::string lTemporary;
		if(aFile->EntryType == FileMapEntryType::PATH) {
			lIfstream.open("profiles/" + aFile->FileName, std::ios::binary);
		} else {
			lIfstream.open(aFile->FileName, std::ios::binary);
		}
		
		if(!lIfstream.is_open()) {
			std::cout << "Something went wrong. Please try again, and if that doesn't work check if there are any profiles available.\n";
			return false;
		}
		
		//loading lowercase letters
		while(std::getline(lIfstream, lTemporary)) {
			if(lTemporary[0] == ' ') {
				continue;
			} else if(lTemporary.size() == 3) {
				aCharMap->Map.push_back(CharMapEntry(lTemporary[0], lTemporary[2]));
			} else if(lTemporary.size() == 4) {
				if(lTemporary[3] != '\r') {
					std::cout << "MFSP profile line size invalid: typo in file.\n";
					return false;
				}
				aCharMap->Map.push_back(CharMapEntry(lTemporary[0], lTemporary[2]));
			} else if(lTemporary.size() == 0) {
				continue;
			} else {
				std::cout << "MFSP profile line size invalid: expected size is 3 or 4, actual is " << lTemporary.size() << "\n";
				return false;
			}
		}
		lIfstream.close();
		return true;
	}
	void GenerateCapitals(CharMap* aCharMap) {
		uint64_t lOrigCharMapSz =  aCharMap->Map.size();
		for(uint64_t lId = 0; lId < lOrigCharMapSz; lId++) {
			if((aCharMap->Map[lId].In >= 97 && aCharMap->Map[lId].Out >= 97) && (aCharMap->Map[lId].In <= 122 && aCharMap->Map[lId].Out <= 122))
				aCharMap->Map.push_back(CharMapEntry(aCharMap->Map[lId].In - 32, aCharMap->Map[lId].Out - 32));
		}
	}
	void PrintCharMap(const CharMap* aCharMap) {
		for(uint64_t lId = 0; lId < aCharMap->Map.size(); lId++) {
			std::cout << aCharMap->Map[lId].In << " --> " << aCharMap->Map[lId].Out << '\n';
		}
	}
	void ApplyCharMap(std::string& aIO, const CharMap* aCharMap, const bool aLoggingEnabled) {
		if(aLoggingEnabled) {
			std::cout << "Input: " << aIO << "\n";
		}
		for(uint64_t lCharId = 0; lCharId < aIO.size(); lCharId++) {
			if(aIO[lCharId] == ' ') {
				std::putchar('S');
				if(aLoggingEnabled) {
					std::cout << "pace, skipping.\n";
				}
				continue;
			}
			for(uint64_t lCheckId = 0; lCheckId < aCharMap->Map.size(); lCheckId++) {
				std::putchar('C');
				if(aLoggingEnabled) {
					std::cout << "hecking character no. " << lCharId << " = " << aIO[lCharId] << ", check no. " << lCheckId << " = " << aCharMap->Map[lCheckId].In << "\n";
				}
				if(aIO[lCharId] == aCharMap->Map[lCheckId].In) {
					if(aLoggingEnabled) {
						std::cout << "Found, changing char " << aIO[lCharId] << " to " << aCharMap->Map[lCheckId].Out << "\n";
					}
					aIO[lCharId] = aCharMap->Map[lCheckId].Out;
					break;
				}
			}
		}
		if(!aLoggingEnabled) {
			std::putchar('\n');
		}
	}
	
	void LoadCharMaps(FileMap* aFileMap, CharMap* aCharMap) {
		aFileMap->Map.clear();
		aCharMap->Map.clear();
		
		FindFiles(aFileMap);
		if(aFileMap->Map.size() == 0) {
			std::cout << "MuffleSpeech could not detect any files.\nPlease check you haven't deleted them or changed their extension.\n";
			Shell::PauseExit(1);
		}
		
		PrintFiles(aFileMap);
		uint64_t lSelection = SelectFile(aFileMap);
		if(lSelection == 0) { Shell::PauseExit(0); }
		
	if(!MuffleSpeech::LoadCharMap(&(aFileMap->Map[lSelection - 1]), aCharMap)) { Shell::PauseExit(1);}
		std::cout << "Character changes detected: " << aCharMap->Map.size() << "\nGenerating capital letter variants:\n";
		GenerateCapitals(aCharMap);
		PrintCharMap(aCharMap);
	}
}
