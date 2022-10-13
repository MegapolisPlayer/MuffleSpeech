//MuffleSpeech Profile Editor
//Should be compatible with MFSP-Core 2.0.0+
//
//MFSP PROFILE FILE FORMAT
//
//------
//In]Out
//
//IN, OUT - 3 letters
//empty marked with hyphons -
//

#include "routines/Routines.h"

int main(void) {
#ifdef _WIN32
	SetConsoleTitle(_T("MuffleSpeech Profile Editor (MFSP 2.0.0)"));
#endif
	
	char lBuffer;
	std::string lInput;
	std::fstream lFile;
	std::string lFileName;
	ProfileEditor::CharMap lCMap;
	
	std::cout << "MFSP ProfileEditor for MFSP 2.0.0 \"Commander-in-chief\"\nby MegapolisPlayer, 2022. Licensed under CC-BY 4.0\n" //add your name here!
	          "Please select an action:\n"
	          "(C) - Create new profile\n"
	          "(L) - Load and edit existing profile\n"
	          "(G) - Load legacy MFSP profile\n"
	          "(D) - Detect existing profiles\n"
	          "Press any other key to exit.\n";
	std::cin >> lBuffer;
	switch(lBuffer) {
		case('c'): case('C'):
			lFileName = ProfileEditor::PromptFilename("mfsp2");
			lFile.open(lFileName, std::ios::binary | std::ios::out | std::ios::trunc);
			if(!lFile.is_open()) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "Failed to create file: " << lFileName << "\n";
				ProfileEditor::Exit(EXIT_FAILURE);
			}
			{
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
				std::cout << "New file created.\n";
			}
			lFile.close();
			break;
		case('l'): case('L'):
			lFileName = ProfileEditor::PromptFilename("mfsp2");
			lFile.open(lFileName, std::ios::binary | std::ios::in);
			ProfileEditor::LoadFile(lFile, &lCMap);
			lFile.close();
			if(lCMap.Map.empty()) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_YELLOW);
				std::cout << "File loaded was empty.\n";
			}
			break;
		case('g'): case('G'):
			lFileName = ProfileEditor::PromptFilename("mfsp");
			lFile.open(lFileName, std::ios::binary | std::ios::in);
			ProfileEditor::LoadFileLegacy(lFile, &lCMap);
			lFileName += '2'; //convert to new
			lFile.close();
			if(lCMap.Map.empty()) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_YELLOW);
				std::cout << "File loaded was empty.\n";
			}
			break;
		case('d'): case('D'): {
			ProfileEditor::FileMap lFM;
			lFM.Detect();
			if(lFM.Map.empty()) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "No profiles found, exiting.\n";
				ProfileEditor::Exit(EXIT_FAILURE);
			}
			lFM.Print();
			
			int64_t lId = ProfileEditor::PromptFileSelect();
			if(lId == -1) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "Input not numeric, exiting.\n";
				ProfileEditor::Exit(EXIT_FAILURE);
			}
			if(lId > int64_t(lFM.Map.size())) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "Input out of range, exiting.\n";
				ProfileEditor::Exit(EXIT_FAILURE);
			}
			lFileName = lFM.Map[lId].Name;
			
			lFile.open(lFileName, std::ios::binary | std::ios::in);
			if(!lFile.is_open()) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "Failed to open file: " << lFileName << "\n";
				ProfileEditor::Exit(EXIT_FAILURE);
			}
			switch(lFM.Map[lId].Type) {
				case(ProfileEditor::FileMapEntryType::MFSP1):
					ProfileEditor::LoadFileLegacy(lFile, &lCMap);
					lFileName += '2'; //convert to new
					break;
				case(ProfileEditor::FileMapEntryType::MFSP2):
					ProfileEditor::LoadFile(lFile, &lCMap);
					break;
				default: break;
			}
			lFile.close();
			if(lCMap.Map.empty()) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_YELLOW);
				std::cout << "File loaded was empty.\n";
			}
			break;
		}
		default: ProfileEditor::Exit(0);
	}
	
	std::vector<std::string> lListCommands;
	lListCommands.reserve(11);
	lListCommands.push_back("ADD");
	lListCommands.push_back("CHANGE");
	lListCommands.push_back("REMOVE");
	lListCommands.push_back("SAVE");
	lListCommands.push_back("LOAD");
	lListCommands.push_back("CLEAR");
	lListCommands.push_back("CLEARFILE");
	lListCommands.push_back("LIST");
	lListCommands.push_back("HELP");
	lListCommands.push_back("EXIT");
	lListCommands.push_back("QUIT");
	
	lCMap.Print();
	std::cout << "--Profile Editor:-------------\nType the ID of the character map entry to change it.\nType HELP to open the help menu.\nType EXIT or QUIT and exit the editor and/or its menus.\n";
	while(true) {
		ProfileEditor::SetColor(ProfileEditor::COLOR_CYAN);
		std::cout << "profedit>";
		ProfileEditor::SetColor(ProfileEditor::COLOR_LIGHT_BLUE);
		std::cin >> lInput;
		ProfileEditor::ResetColor();
		
		for(uint64_t lId = 0; lId < lInput.size(); lId++) { lInput[lId] = toupper(lInput[lId]); } 
		
		if(lInput == "ADD") {
			lCMap.Map.push_back(ProfileEditor::PromptNew());
			ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
			std::cout << "New entry added.\n"; //add scoped color to ADD and REMOVE (green on success), change version 2.0.1 to And here comes the rainbow!
		}
		elif(lInput == "CHANGE") {
			std::cout << "Please enter the ID of the entry you want to modify: ";
			std::cin >> lInput;
			if(!ProfileEditor::IsNumber(lInput)) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "Input not numeric.\n"; loopover;
			}
			lCMap.Change(ProfileEditor::PromptChange(std::stoi(lInput)));
			
			ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
			std::cout << "Entry changed.";
		}
		elif(lInput == "REMOVE") {
			int64_t lId = ProfileEditor::PromptRemove();
			if(lId == -1) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "Input not numeric.\n"; loopover;
			}
			lCMap.Map.erase(lCMap.Map.begin() + lId);
			
			ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
			std::cout << "Entry removed.\n";
		}
		elif(lInput == "SAVE") {
			lFile.open(lFileName, std::ios::binary | std::ios::out | std::ios::trunc);
			if(!lFile.is_open()) {
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
				std::cout << "Failed to open file.";
			}
			
			ProfileEditor::SaveFile(lFile, &lCMap);
			lFile.close();
			
			ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
			std::cout << "Profile saved to " << lFileName << ".\n"; loopover;
		}
		elif(lInput == "LOAD") {
			{
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_YELLOW);
				std::cout << "WARNING: This will clear the current character map. Any unsaved progress will be lost.\nPress Y to continue and any other key to return.\n";
				std::cin >> lBuffer;
			}
			if(lBuffer == 'y' || lBuffer == 'Y') {
				ProfileEditor::FileMap lFM;
				lFM.Detect();
				if(lFM.Map.empty()) {
					ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
					std::cout << "No profiles found.\n"; loopover;
				}
				lFM.Print();
				int64_t lId = ProfileEditor::PromptFileSelect();
				if(lId == -1) {
					ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
					std::cout << "Input not numeric.\n"; loopover;
				}
				if(lId > int64_t(lFM.Map.size())) {
					ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_RED);
					std::cout << "Input out of range.\n"; loopover;
				}
				lFileName = lFM.Map[lId].Name;
				lFile.open(lFileName, std::ios::binary | std::ios::in);
				lCMap.Map.clear();
				switch(lFM.Map[lId].Type) {
					case(ProfileEditor::FileMapEntryType::MFSP1):
						ProfileEditor::LoadFileLegacy(lFile, &lCMap);
						break;
					case(ProfileEditor::FileMapEntryType::MFSP2):
						ProfileEditor::LoadFile(lFile, &lCMap);
						break;
					default: break;
				}
				lFile.close();
				ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
				std::cout << "New profile loaded.\n";
			}
			else { loopover; }
			ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
			std::cout << "New profile loaded from " << lFileName << ".\n"; loopover;
		}
		elif(lInput == "CLEAR") {
			lCMap.Map.clear();
			ProfileEditor::ScopedColor lSC(ProfileEditor::COLOR_GREEN);
			std::cout << "Profile cleared.\n"; loopover;
		}
		elif(lInput == "CLEARFILE") {
			lCMap.Map.clear();
			ProfileEditor::OverwriteFile(lFile, lFileName);
		}
		elif(lInput == "LIST") { lCMap.Print(); loopover; }
		elif(lInput == "HELP") { std::cout << ProfileEditor::gHelpMenu; loopover; }
		elif(lInput == "EXIT" || lInput == "QUIT") { ProfileEditor::Exit(EXIT_SUCCESS); }
		else { std::cout << "Command \"" << lInput << "\" not found. Did you mean " << lListCommands[ProfileEditor::FindMostSimilarC(lInput, lListCommands)] << "?\n"; loopover; }
		
		lCMap.Print(); //if no loopover/continue
	}
	ProfileEditor::Exit(0);
}
