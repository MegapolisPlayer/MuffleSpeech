#include "File.h"

namespace MuffleSpeech {
	File::File() {
		this->mFileStream = {};
		this->mFileName = "";
		this->mLineNo = 0;
	}
	
	void File::Open(std::string aFilename) {
		this->mFileStream.open(aFilename, std::ios::in | std::ios::out | std::ios::binary);
		this->mFileName = aFilename;
	}
	void File::Create(std::string aFilename) {
		this->mFileStream.open(aFilename, std::ios::out | std::ios::binary | std::ios::trunc);
		this->mFileName = aFilename;
	}
	void File::Close() {
		this->mFileStream.close();
		this->mFileName = "";
		this->mLineNo = 0;
	}
	
	std::string File::LoadFile() {
		std::string lTemp, lBuf;
		this->mFileStream.clear();
		this->mFileStream.seekg(0, this->mFileStream.beg);
		while(std::getline(this->mFileStream, lBuf)) {
			lTemp.append(lBuf + "\n");
		}
		this->mFileStream.clear();
		this->mFileStream.seekg(0, this->mFileStream.beg);
		return lTemp;
	}
	std::string File::LoadLine(bool* aReachedEOF) {
		std::string lTemp;
		std::getline(this->mFileStream, lTemp);
		this->mLineNo++;
		
		if(this->mFileStream.eof()) { //reached eof
			if(aReachedEOF != nullptr) {*aReachedEOF = true;}
			this->ResetRead();
			return "";
		}
		return lTemp;
	}
	std::string File::LoadLine(uint64_t aLineNo, bool* aReachedEOF) {
		std::string lTemp;
		uint64_t lLineNo = 0;
		this->mFileStream.clear();
		this->mFileStream.seekg(0, this->mFileStream.beg);
		while(std::getline(this->mFileStream, lTemp) && lLineNo != aLineNo) {
			lLineNo++;
		}
		this->mFileStream.clear();
		this->mFileStream.seekg(0, this->mFileStream.beg);
		
		if(lLineNo == aLineNo) {
			return lTemp;
		}
		else {   //reached eof
			if(aReachedEOF != nullptr) {*aReachedEOF = true;}
			this->ResetRead();
			return "";
		}
	}
	
	void File::Append(char aChar) {
		this->mFileStream.seekg(0, this->mFileStream.end);
		this->mFileStream << aChar;
	}
	void File::Append(std::string aString) {
		this->mFileStream.seekg(0, this->mFileStream.end);
		this->mFileStream << aString;
	}
	void File::AppendNL(std::string aString) {
		this->mFileStream.seekg(0, this->mFileStream.end);
		this->mFileStream << aString << "\n";
	}
	
	void File::Write(std::string aString) {
		this->mFileStream << aString;
	}
	void File::WriteNL(std::string aString) {
		this->mFileStream << aString << "\n";
	}
	
	void File::Empty() {
		if(this->mFileStream.is_open()) {
			return this->mFileStream.close();
		}
		this->mFileStream.open(this->mFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc); //overwrite
	}
	
	void File::MovePointer(FilePointerPos aPos) {
		switch(aPos) {
			case(FilePointerPos::BEGIN):
				this->mFileStream.seekg(0, this->mFileStream.beg);
				break;
			case(FilePointerPos::END):
				this->mFileStream.seekg(0, this->mFileStream.end);
				break;
		}
	}
	void File::MovePointerBEG(uint64_t aOffset) {
		this->mFileStream.seekg(aOffset, this->mFileStream.beg);
	}
	void File::MovePointerCUR(uint64_t aOffset) {
		this->mFileStream.seekg(aOffset, this->mFileStream.cur);
	}
	void File::ResetRead() {
		this->mFileStream.clear();
		this->mFileStream.seekg(0, this->mFileStream.beg);
		this->mLineNo = 0;
	}
	
	std::string File::GetFilename() {
		return this->mFileName;
	}
	
	uint64_t File::GetLineNumber() {
		return this->mLineNo;
	}
	bool File::IsOpen() {
		return this->mFileStream.is_open();
	}
	
	File::~File() {
		if(this->mFileStream.is_open()) {
			this->mFileStream.close();
		}
	}
}
