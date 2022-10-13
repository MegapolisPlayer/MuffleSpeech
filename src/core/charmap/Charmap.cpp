#include "CharMap.h"

namespace MuffleSpeech {
	CharMapEntry::CharMapEntry() {
		this->InSize = 0;
		this->OutSize = 0;
	}
	CharMapEntry::CharMapEntry(const char (&aIn)[3], const char (&aOut)[3]) {
		for(uint8_t lId = 0; lId < 3; lId++) {
			this->In[lId] = aIn[lId];
			for(this->InSize = 0; this->InSize < 3; this->InSize++) {
				if(this->In[this->InSize] == 0 || this->In[this->InSize] == '-') { break; }
			}
			this->Out[lId] = aOut[lId];
			for(this->OutSize = 0; this->OutSize < 3; this->OutSize++) {
				if(this->Out[this->OutSize] == 0 || this->Out[this->OutSize] == '-') { break; }
			}
		}
	}
	void CharMapEntry::PrintIn() const {
		PrintCharArray(this->In, 3);
	}
	void CharMapEntry::PrintOut() const {
		PrintCharArray(this->Out, 3);
	}
	
	//returns true if aFirst.In is smaller (should be higher in the list)
	bool AlphabeticCompare(const CharMapEntry& aFirst, const CharMapEntry& aSecond) {
		//comparing ins
		for(uint8_t lId = 0; lId < 3; lId++) {
			if(aFirst.In[lId] != aSecond.In[lId]) {
				return aFirst.In[lId] < aSecond.In[lId];
			}
		}
		//comparing outs
		for(uint8_t lId = 0; lId < 3; lId++) {
			if(aFirst.Out[lId] != aSecond.Out[lId]) {
				return aFirst.Out[lId] < aSecond.Out[lId];
			}
		}
		return false; //if identical dont move
	}
	
	void CharMap::Print() {
		std::sort(this->Map.begin(), this->Map.end(), AlphabeticCompare);
		for(uint64_t lId = 0; lId < this->Map.size(); lId++) {
			std::cout << '(' << lId << "): [";
			this->Map[lId].PrintIn();
			std::cout << "] --> [";
			this->Map[lId].PrintOut();
			std::cout << "]\n";
		}
	}
	
	//the most important function of mufflespeech!
	//if hyphon - ignore
	void CharMap::Apply(Buffer* aStrbuf, Buffer* aFinbuf) const {
		ScopeTimer lST("CharMapApply");
		
		aFinbuf->Clear();
		
		char lOldTemp[3] = {0};
		uint64_t lOldTempSize = 0;
		uint64_t lStrbufAllocAmount = aStrbuf->GetAllocAmount();
		uint8_t lSizeBuffer = 0;
		
		uint64_t lId = 0;
		while(lId < lStrbufAllocAmount) {
			for(uint64_t lId2 = 0; lId2 < this->Map.size(); lId2++) {
				EmptyCharArray(lOldTemp, 3); //empty for previous loop
				for(lOldTempSize = 0; lOldTempSize < Min64(this->Map[lId2].InSize, (lStrbufAllocAmount - lId)); lOldTempSize++) { //minimum, input size or if little space in buffer
					lOldTemp[lOldTempSize] = aStrbuf->Get(lOldTempSize + lId); //assigning
				}
				
				if(
				    StringSameScore(lOldTemp, lOldTempSize, this->Map[lId2].In, this->Map[lId2].InSize) //compare the CUR and the IN
				    > (double(lOldTempSize) / this->Map[lId2].InSize - 0.10f)
				) {
					//allows for arithmetic inprecision
					for(uint8_t lId3 = 0; lId3 < this->Map[lId2].OutSize; lId3++) {
						if(this->Map[lId2].Out[lId3] == '-') {
							lSizeBuffer = lId2;
							goto forend;
						} //we reached the end of the output entry, goto actually useful here
						else { aFinbuf->Append(this->Map[lId2].Out[lId3]); }
					}
					lSizeBuffer = lId2;
					goto forend;
				}
				else { continue; }
			}
			aFinbuf->Append(lOldTemp, lOldTempSize);
		forend:;
			lId += this->Map[lSizeBuffer].InSize; //increment
		}
		aStrbuf->Clear(); //clears strbuf on ending
	}
	
	int8_t CharMap::Load(File* aFile) {
		ScopeTimer lST("CharMapLoad");
		if(!aFile->IsOpen()) { return -1; }
		aFile->ResetRead();
		bool lEOF = false;
		std::string lTemp;
		while(!lEOF) {
			lTemp = aFile->LoadLine(&lEOF);
			if(lTemp.size() != 6) {
				return -1;
			}
			char lTempIn[3] = {lTemp[0], lTemp[1], lTemp[2]};
			char lTempOut[3] = {lTemp[3], lTemp[4], lTemp[5]};
			this->Map.push_back(CharMapEntry(lTempIn, lTempOut));
			lTemp.clear();
		}
		return 0;
	}
}
