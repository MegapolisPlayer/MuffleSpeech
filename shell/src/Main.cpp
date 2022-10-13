#include "shell/ShellHandler.h"
#include "shell/Grammar.h"

int main(int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleTitle(_T("MuffleSpeech Shell"));
#endif
	
	MuffleSpeech::Arguments lArgs = MuffleSpeech::ProcessArguments(argc, argv);
	MuffleSpeech::Statistics lStats;
	std::string lInput;
	std::string lSavedFile;
	MuffleSpeech::CharMap lCm;
	MuffleSpeech::File lFile;
	
	MuffleSpeech::Shell::About(&lArgs);
	MuffleSpeech::Shell::DetectLoadFile(&lCm, &lFile);
	
	lStats.Increment(MuffleSpeech::StatisticsValue::AMOUNT_OPENED);
	while(true) {
		MuffleSpeech::SetColor(MuffleSpeech::COLOR_CYAN);
		std::cout << "mfsp>";
		MuffleSpeech::SetColor(MuffleSpeech::COLOR_LIGHT_BLUE);
		std::cin >> lInput;
		MuffleSpeech::ResetColor();
		
		for(uint64_t lId = 0; lId < lInput.size(); lId++) { lInput[lId] = toupper(lInput[lId]); } //convert string to uppercase
		
		if(lInput == "APPLY") {
			lCm.Apply(&MuffleSpeech::MFSP_STRBUF, &MuffleSpeech::MFSP_FINBUF);
		}
		elif(lInput == "STRBUF") {
			MuffleSpeech::MFSP_STRBUF.Append(MuffleSpeech::Shell::PromptAppend("STRBUF"));
			if(!lArgs.DisableStats) { lStats.Increment(MuffleSpeech::StatisticsValue::COM_BUF); }
		}
		elif(lInput == "ECHOBUF") {
			MuffleSpeech::MFSP_ECHOBUF.Append(MuffleSpeech::Shell::PromptAppend("ECHOBUF"));
			if(!lArgs.DisableStats) { lStats.Increment(MuffleSpeech::StatisticsValue::COM_BUF); }
		}
		elif(lInput == "COPYBUF") {
			char lTemp = MuffleSpeech::Shell::PromptBufferSelectLite();
			switch(lTemp) {
				case('S'): case('s'):
					MuffleSpeech::MFSP_ECHOBUF.CopyBuffer(&MuffleSpeech::MFSP_STRBUF); break;
				case('F'): case('f'):
					MuffleSpeech::MFSP_ECHOBUF.CopyBuffer(&MuffleSpeech::MFSP_FINBUF); break;
				default: loopover;
			}
		}  //copies buffer to echobuf
		elif(lInput == "CLEARBUF") {
			char lTemp = MuffleSpeech::Shell::PromptBufferSelect();
			switch(lTemp) {
				case('S'): case('s'):
					MuffleSpeech::MFSP_STRBUF.Clear(); break;
				case('F'): case('f'):
					MuffleSpeech::MFSP_FINBUF.Clear(); break;
				case('E'): case('e'):
					MuffleSpeech::MFSP_ECHOBUF.Clear(); break;
				default: loopover;
			}
		}
		elif(lInput == "SAVEBUF") {
			std::string lFilename = MuffleSpeech::Shell::PromptFilename();
			lFile.Create(lFilename);
			char lTemp = MuffleSpeech::Shell::PromptBufferSelect();
			switch(lTemp) {
				case('S'): case('s'):
					MuffleSpeech::MFSP_STRBUF.Save(&lFile); break;
				case('F'): case('f'):
					MuffleSpeech::MFSP_FINBUF.Save(&lFile); break;
				case('E'): case('e'):
					MuffleSpeech::MFSP_ECHOBUF.Save(&lFile); break;
				default: lFile.Close(); break;
			}
		}
		elif(lInput == "PRINT") { MuffleSpeech::MFSP_ECHOBUF.Print(); std::putchar('\n'); } //prints echobuf
		elif(lInput == "RELOAD") {
			if(!lArgs.DisableStats) { lStats.Increment(MuffleSpeech::StatisticsValue::COM_RELOAD); }
			MuffleSpeech::Shell::DetectLoadFile(&lCm, &lFile);
		}
		elif(lInput == "LIST") { lCm.Print(); }
		elif(lInput == "HELP") {
			MuffleSpeech::Shell::Help();
			if(!lArgs.DisableStats) { lStats.Increment(MuffleSpeech::StatisticsValue::COM_HELP); }
		}
		elif(lInput == "ABOUT") {
			MuffleSpeech::Shell::About(&lArgs);
			if(!lArgs.DisableStats) { lStats.Increment(MuffleSpeech::StatisticsValue::COM_ABOUT); }
		}
		elif(lInput == "EXIT" || lInput == "QUIT") { break; }
		else { std::cout << "Command \"" << lInput << "\" not found. Did you mean " << MuffleSpeech::Shell::gConsoleCommands[MuffleSpeech::Shell::FindMostSimilar(lInput.c_str(), MuffleSpeech::Shell::gConsoleCommands, MuffleSpeech::Shell::gConsoleCommandsAmount)] << "?\n"; loopover; }
	}
	if(!lArgs.DisableStats) {
		lFile.Open("mfsp.sts");
		lStats.Save(&lFile);
		lFile.Close();
	}
	
	MuffleSpeech::Exit(0);
}
