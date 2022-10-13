#ifndef MUFFLESPEECH_BUFFER
#define MUFFLESPEECH_BUFFER
#include "../fileio/FileIO.h"
#include "../time/Timer.h"

#define BUFFER_MAXSIZE 5000

namespace MuffleSpeech {
	//Base buffer class
	class MFFN Buffer {
	public:
		Buffer();
		
		void Append(const char aNew);
		void Append(const char* aNew, const uint64_t aNewSize);
		void Append(const std::string aNew);
		void RemoveLast();
		void RemoveLast(const uint64_t aAmount);
		void RemoveFirst();
		void RemoveFirst(const uint64_t aAmount);
		void Clear();
		void ShiftLeft(const uint64_t aAmount); //If shifting beyond bounds (0), the content will be lost and a notification will be displayed.
		void operator<<(const uint64_t aAmount);
		
		//File MUST be open. On failure returns -1
		int8_t Save(File* aFile);
		
		//Warning: This will only copy up to buffer max
		void CopyBuffer(Buffer* aBuffer);
		
		void Print();
		void PrintFormatted();
		void PrintAll();
		void PrintFormattedAll();
		
		uint64_t GetAllocAmount(); //return internal counter, should be correct 99% of the time
		double GetAllocPercentage(); //internally calls GetAllocAmount
		
		char Get(const uint64_t aId);
		void Get(OUT char* aArray, const uint64_t aIdBegin, const uint64_t aAmount);
		
		virtual ~Buffer();
	protected:
		char mBuffer[BUFFER_MAXSIZE] = {0};
		uint64_t mAmountAllocated;
	};
	
	MFFN extern Buffer MFSP_STRBUF;
	MFFN extern Buffer MFSP_FINBUF;
	MFFN extern Buffer MFSP_ECHOBUF;
}

#endif
