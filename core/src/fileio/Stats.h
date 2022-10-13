#ifndef MUFFLESPEECH_CONFIG
#define MUFFLESPEECH_CONFIG
#include "File.h"

//MFSP STS file format
//
//AmountOpened
//CharsProcessed
//Com_BUF_OPEN
//Com_HELP
//Com_ABOUT
//Com_RELOAD
//
//Separated by just newline characters.

namespace MuffleSpeech {
	enum struct StatisticsValue {
		AMOUNT_OPENED = 0,
		CHARS_PROCESSED,
		
		COM_BUF,
		COM_HELP,
		COM_ABOUT,
		COM_RELOAD
	};
	//MuffleSpeech statistics
	struct MFFN Statistics {
		//AmountOpened
		//CharsProcessed
		//Com_BUF_OPEN
		//Com_HELP
		//Com_ABOUT
		//Com_RELOAD
		
		uint64_t Stats[6];
		
		Statistics();
		
		void Add(StatisticsValue aMember, uint64_t aValueAdd);
		void Increment(StatisticsValue aMember);
		
		void Load(File* aFile);
		void Save(File* aFile);
		
		~Statistics();
	};
}

#endif
