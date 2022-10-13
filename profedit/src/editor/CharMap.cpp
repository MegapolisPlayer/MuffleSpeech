#include "CharMap.h"

namespace PEInternal {
	void PrintCharArray(const char* aArray, const uint64_t aSize) {
		for(uint64_t lId = 0; lId < aSize; lId++) {
			std::putchar(aArray[lId]);
		}
	}
}

namespace ProfileEditor {
	CharMapEntry::CharMapEntry() {
	
	}
	CharMapEntry::CharMapEntry(const char (&aIn)[3], const char (&aOut)[3]) {
		for(uint8_t lId = 0; lId < 3; lId++) {
			this->In[lId] = aIn[lId];
			this->Out[lId] = aOut[lId];
		}
	}
	void CharMapEntry::Update(const char (&aIn)[3], const char (&aOut)[3]) {
		for(uint8_t lId = 0; lId < 3; lId++) {
			this->In[lId] = aIn[lId];
			this->Out[lId] = aOut[lId];
		}
	}
	void CharMapEntry::UpdateIn(const char (&aNew)[3]) {
		for(uint8_t lId = 0; lId < 3; lId++) {
			this->In[lId] = aNew[lId];
		}
	}
	void CharMapEntry::UpdateOut(const char (&aNew)[3]) {
		for(uint8_t lId = 0; lId < 3; lId++) {
			this->Out[lId] = aNew[lId];
		}
	}
	void CharMapEntry::PrintIn() const {
		PEInternal::PrintCharArray(this->In, 3);
	}
	void CharMapEntry::PrintOut() const {
		PEInternal::PrintCharArray(this->Out, 3);
	}
	
	CharMapChange::CharMapChange() {
		this->Id = 0;
		this->Destination = CharMapChangeDest::UNINIT;
	}
	CharMapChange::CharMapChange(uint64_t aId, CharMapChangeDest aDest, const char (&aNew)[3]) {
		this->Id = aId;
		this->Destination = aDest;
		for(uint8_t lId = 0; lId < 3; lId++) {
			this->New[lId] = aNew[lId];
		}
	}
	void CharMapChange::Update(uint64_t aId, CharMapChangeDest aDest, const char (&aNew)[3]) {
		this->Id = aId;
		this->Destination = aDest;
		for(uint8_t lId = 0; lId < 3; lId++) {
			this->New[lId] = aNew[lId];
		}
	}
	
	void CharMap::Change(const CharMapChange aChange) {
		switch(aChange.Destination) {
			case(CharMapChangeDest::INPUT):
				this->Map[aChange.Id].UpdateIn(aChange.New);
				break;
			case(CharMapChangeDest::OUTPUT):
				this->Map[aChange.Id].UpdateOut(aChange.New);
				break;
			default:
				std::cout << "Change query empty, no changes made.\n";
		}
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
}
