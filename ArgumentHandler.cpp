#include "ArgumentHandler.h"

namespace MuffleSpeech {
	Arguments::Arguments() {
		this->DisabledAsciiArt = false;
	}
	
	void ProcessArgs(int argc, char* argv[], Arguments* aArgs) {
		for(int32_t i = 1; i < argc; i++) { //skipping argv[0] - just command/gibberish
			if(strcmp(argv[i], "-disable_ascii_art") == 0) {
				aArgs->DisabledAsciiArt = true;
			}
			//more later
		}
	}
}
