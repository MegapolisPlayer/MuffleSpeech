#ifndef MUFFLESPEECH_ARGUMENT_HANDLER
#define MUFFLESPEECH_ARGUMENT_HANDLER
#include "StdInclude.h"

namespace MuffleSpeech {
	struct Arguments {
		bool DisabledAsciiArt;
		//more later
		
		Arguments();
	};
	
	void ProcessArgs(int argv, char* argc[], Arguments* aArgs);
}

#endif