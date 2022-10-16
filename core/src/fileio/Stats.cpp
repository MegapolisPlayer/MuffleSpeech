#include "Stats.h"

namespace MuffleSpeech {

	Statistics::Statistics() {
	
	}
	
	void Statistics::Add(StatisticsValue aMember, uint64_t aValueAdd) {
		switch(aMember) {
			case(StatisticsValue::AMOUNT_OPENED):
				this->Stats[0] += aValueAdd;
				break;
			case(StatisticsValue::CHARS_PROCESSED):
				this->Stats[1] += aValueAdd;
				break;
			case(StatisticsValue::COM_BUF):
				this->Stats[2] += aValueAdd;
				break;
			case(StatisticsValue::COM_HELP):
				this->Stats[3] += aValueAdd;
				break;
			case(StatisticsValue::COM_ABOUT):
				this->Stats[4] += aValueAdd;
				break;
			case(StatisticsValue::COM_RELOAD):
				this->Stats[5] += aValueAdd;
				break;
		}
	}
	void Statistics::Increment(StatisticsValue aMember) {
		switch(aMember) {
			case(StatisticsValue::AMOUNT_OPENED):
				this->Stats[0]++;
				break;
			case(StatisticsValue::CHARS_PROCESSED):
				this->Stats[1]++;
				break;
			case(StatisticsValue::COM_BUF):
				this->Stats[2]++;
				break;
			case(StatisticsValue::COM_HELP):
				this->Stats[3]++;
				break;
			case(StatisticsValue::COM_ABOUT):
				this->Stats[4]++;
				break;
			case(StatisticsValue::COM_RELOAD):
				this->Stats[5]++;
				break;
		}
	}
	
	int8_t Statistics::Load(File* aFile) {
		if(!aFile->IsOpen()) {
			ScopedColor lSC(COLOR_RED);
			std::cout << "Error: File " << aFile->GetFilename() << " does not exist.\n";
			return -1;
		}
		aFile->ResetRead(); //set to beginning
		std::string lTemp;
		for(uint8_t lId = 0; lId < 6; lId++) {
			lTemp = aFile->LoadLine();
			if(IsNumber(lTemp) && !lTemp.empty()) { this->Stats[lId] = std::stoi(lTemp); }
			else {
				ScopedColor lSC(COLOR_RED);
				std::cout << "Error: Line " << uint16_t(lId) << " of mfsp.sts is not a number.\n";
				return -1;
			}
		}
		aFile->ResetRead();
		return 0;
	}
	int8_t Statistics::Save(File* aFile) {
		aFile->Empty(); //will also create the file
		aFile->ResetRead();
		for(uint8_t lId = 0; lId < 6; lId++) {
			aFile->AppendNL(std::to_string(this->Stats[lId]));
		}
		return 0;
	}
	
	Statistics::~Statistics() {
	
	}
}
