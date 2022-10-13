//MuffleSpeech Statistics Viewer
//Should be compatible with MFSP-Core 2.0.0+
//
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

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#endif

namespace StatsViewer {
	void CreateFile(std::ofstream* aOfstream, const std::string aFilename) {
		std::cout << "Creating new and empty MFSP statistics file.\n";
		aOfstream->open(aFilename, std::ios::trunc | std::ios::binary);
		*aOfstream << "0\n0\n0\n0\n0\n0\n"; //6 values
		aOfstream->close();
	}
	std::string GetCurrentTime() {
		std::time_t lTime;	   //temp variable for holding time
		std::string lTimeProc; //temp variable for removing newline
		lTime = std::chrono::high_resolution_clock::to_time_t(std::chrono::high_resolution_clock::now());
		lTimeProc = std::ctime(&lTime);
		lTimeProc.pop_back();
		return lTimeProc;
	}
}

int main(void) {
#ifdef _WIN32
	SetConsoleTitle(_T("MuffleSpeech Statistics Viewer (MFSP 2.0.0)"));
#endif
	
	char lBuffer;
	std::ifstream lIfstream;
	std::ofstream lOfstream;
	std::string lTemp;
	lIfstream.open("mfsp.sts", std::ios::binary);
	
	std::cout << "MFSP StatsViewer for MFSP 2.0.0 \"Commander-in-chief\"\n";
	
	if(!lIfstream.is_open()) {
		std::cout << "Failed to open file: mfsp.sts\n";
		lIfstream.close();
		StatsViewer::CreateFile(&lOfstream, "mfsp.sts");
		std::cin >> lBuffer;
		exit(EXIT_FAILURE);
	}
	
	std::cout <<
	          "--Statistics:-----------------\n"
	          ;
	          
	uint64_t lLineNo = 1;
	while(std::getline(lIfstream, lTemp)) {
		if(lTemp.empty()) {
			std::cout << "File value no." << lLineNo << " is empty.\n";
			lIfstream.close();
			StatsViewer::CreateFile(&lOfstream, "mfsp.sts");
			std::cin >> lBuffer;
			exit(EXIT_FAILURE);
		}
		std::cout << "Amount of ";
		switch(lLineNo) {
			case(1):
				std::cout << "times MuffleSpeech was opened";
				break;
			case(2):
				std::cout << "characters processed";
				break;
			case(3):
				std::cout << "times _BUF_OPEN called";
				break;
			case(4):
				std::cout << "times the HELP menu was opened";
				break;
			case(5):
				std::cout << "times the ABOUT menu was opened";
				break;
			case(6):
				std::cout << "times the _RELOAD command was called";
				break;
			default:
				std::cout << "Line overflow: too many lines.\n";
				lIfstream.close();
				StatsViewer::CreateFile(&lOfstream, "mfsp.sts");
				exit(EXIT_FAILURE);
		}
		std::cout << ": " << lTemp << "\n";
		lLineNo++;
	}
	lIfstream.close();
	
	std::cout <<
	          "--Options:--------------------\n"
	          "(S) - Save statistics snapshot as custom format\n"
	          "(C) - Save statistics snapshot as a CSV table\n"
	          "(R) - Reset current statistics\n"
	          "Press any other key to exit.\n";
	std::cin >> lBuffer;
	
	switch(lBuffer) {
		case('s'): case('S'):
			std::cout << "Please enter filename (with extension): ";
			std::cin >> lTemp;
			if(lTemp == "mfsp.sts") {
				std::cout << "Cannot write to mfsp.sts - reserved file.\n";
				std::cin >> lBuffer;
				exit(EXIT_FAILURE);
			}
			
			lIfstream.open("mfsp.sts", std::ios::binary);
			lOfstream.open(lTemp, std::ios::app | std::ios::binary);
			
			lOfstream << '[' << StatsViewer::GetCurrentTime() << "]\n";
			while(std::getline(lIfstream, lTemp)) { //file copying
				lOfstream << lTemp << "\n";
			}
			
			lOfstream.close();
			lIfstream.close();
			
			std::cout << "Snapshot saved.\n";
			break;
		case('c'): case('C'):
			std::cout << "Please enter filename: ";
			std::cin >> lTemp;
			if(lTemp == "mfsp.sts") {
				std::cout << "Cannot write to mfsp.sts - reserved file.\n";
				std::cin >> lBuffer;
				exit(EXIT_FAILURE);
			}
			
			lIfstream.open("mfsp.sts", std::ios::binary);
			lOfstream.open(lTemp + ".csv", std::ios::trunc | std::ios::binary);
			
			lOfstream << "MFSP Info,Value,\n"; //CSV first row
			lOfstream << "MFSP_TIME," << StatsViewer::GetCurrentTime() << ",\n";
			lOfstream << "MFSP_VER,SV-2.0.0,\n";
			lOfstream << "\nMFSP Info,Value,\n"; //CSV main stats separator
			
			//file copying
			std::getline(lIfstream, lTemp);
			lOfstream << "AM_OPEN," << lTemp << ",\n";
			std::getline(lIfstream, lTemp);
			lOfstream << "CHAR_PROC," << lTemp << ",\n";
			std::getline(lIfstream, lTemp);
			lOfstream << "COM_BUF," << lTemp << ",\n";
			std::getline(lIfstream, lTemp);
			lOfstream << "COM_HELP," << lTemp << ",\n";
			std::getline(lIfstream, lTemp);
			lOfstream << "COM_ABOUT," << lTemp << ",\n";
			std::getline(lIfstream, lTemp);
			lOfstream << "COM_RELOAD," << lTemp << ",\n";
			
			lIfstream.close();
			lOfstream.close();
			
			std::cout << "Snapshot saved.\n"; break;
		case('r'): case('R'):
			StatsViewer::CreateFile(&lOfstream, "mfsp.sts"); break;
	}
	
	lIfstream.close();
	
	std::cout << "Press any key and ENTER to exit.\n";
	std::cin >> lBuffer;
}
