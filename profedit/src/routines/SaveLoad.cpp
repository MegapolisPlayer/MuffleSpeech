#include "SaveLoad.h"

namespace ProfileEditor {
	int16_t LoadFileLegacy(std::fstream& aFstream, CharMap* aCharMap) {
		std::string lTemp;
		while(std::getline(aFstream, lTemp)) {
			if(lTemp.size() != 3) {
				return -1;
			}
			aCharMap->Map.push_back(CharMapEntry({lTemp[0], '-', '-'}, {lTemp[2], '-', '-'}));
		}
		return 0;
	}
	int16_t LoadFile(std::fstream& aFstream, CharMap* aCharMap) {
		std::string lTemp;
		while(std::getline(aFstream, lTemp)) {
			if(lTemp.size() != 6) {
				return -1;
			}
			char lTempIn[3] = {lTemp[0], lTemp[1], lTemp[2]};
			char lTempOut[3] = {lTemp[3], lTemp[4], lTemp[5]};
			aCharMap->Map.push_back(CharMapEntry(lTempIn, lTempOut));
		}
		return 0;
	}
	void SaveFile(std::fstream& aFstream, CharMap* aCharMap) {
		for(uint64_t lId = 0; lId < aCharMap->Map.size(); lId++) {
			for(uint8_t llId = 0; llId < 3; llId++) {
				aFstream.put(aCharMap->Map[lId].In[llId]);
			}
			for(uint8_t llId = 0; llId < 3; llId++) {
				aFstream.put(aCharMap->Map[lId].Out[llId]);
			}
			aFstream.put('\n');
		}
	}
	
	void OverwriteFile(std::fstream& aFstream, std::string aFileName) {
		aFstream.open(aFileName, std::ios::trunc);
		aFstream.close();
	}
}
