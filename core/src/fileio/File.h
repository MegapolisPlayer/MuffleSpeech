#ifndef MUFFLESPEECH_FILES
#define MUFFLESPEECH_FILES
#include "../boot/Boot.h"

namespace MuffleSpeech {
	enum struct FilePointerPos {
		BEGIN,
		END
	};
	class MFFN File {
	public:
		File();
		
		void Open(std::string aFilename);
		void Create(std::string aFilename);
		void Close();
		
		//LoadFile() sets pointer to file beginning
		//LoadLine() sets pointer to beginning only if it reached EOF or aLineNo is larger than amount of lines
		//
		
		std::string LoadFile();
		std::string LoadLine(bool* aReachedEOF = nullptr);
		std::string LoadLine(uint64_t aLineNo, bool* aReachedEOF = nullptr);
		
		void Append(char aChar);
		void Append(std::string aString);
		void AppendNL(std::string aString);
		
		void Write(std::string aString);
		void WriteNL(std::string aString);
		
		void Empty();
		
		void MovePointer(FilePointerPos aPos);
		void MovePointerBEG(uint64_t aOffset);
		void MovePointerCUR(uint64_t aOffset);
		void ResetRead(); //resets read so file can be read again
		
		std::string GetFilename();
		uint64_t GetLineNumber();
		bool IsOpen();
		
		~File();
	protected:
		std::fstream mFileStream;
		std::string mFileName;
		uint64_t mLineNo;
	};
}

#endif
