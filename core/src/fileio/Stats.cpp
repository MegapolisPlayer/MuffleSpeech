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
	
	void Statistics::Load(File* aFile) {
		aFile->ResetRead(); //set to beginning
		aFile->LoadFile();
	}
	void Statistics::Save(File* aFile) {
		for(uint8_t lId = 0; lId < 6; lId++) {
			aFile->AppendNL(std::to_string(this->Stats[lId]));
		}
	}
	
	Statistics::~Statistics() {
	
	}
}
