#include "Buffer.h"

namespace MuffleSpeech {
	Buffer::Buffer() {
		this->mAmountAllocated = 0;
	}
	
	void Buffer::Append(const char aNew) {
		if(this->mAmountAllocated > BUFFER_MAXSIZE) { ScopedColor lSC(COLOR_RED); std::cout << "Buffer error: No empty space.\n"; }
		this->mBuffer[this->mAmountAllocated] = aNew;
		this->mAmountAllocated++;
	}
	void Buffer::Append(const char* aNew, const uint64_t aNewSize) {
		for(uint64_t lId = 0; lId < aNewSize; lId++) { this->Append(aNew[lId]); }
	}
	void Buffer::Append(const std::string aNew) {
		for(uint64_t lId = 0; lId < aNew.size(); lId++) { this->Append(aNew[lId]); }
	}
	void Buffer::RemoveLast() {
		if(this->mAmountAllocated == 0) { ScopedColor lSC(COLOR_RED); std::cout << "Buffer error: Already empty.\n"; }
		this->mBuffer[this->mAmountAllocated - 1] = 0;
	}
	void Buffer::RemoveLast(const uint64_t aAmount) {
		for(uint64_t lId = 0; lId < aAmount; lId++) {
			this->RemoveLast();
		}
	}
	void Buffer::RemoveFirst() {
		this->ShiftLeft(1);
	}
	void Buffer::RemoveFirst(const uint64_t aAmount) {
		this->ShiftLeft(aAmount);
	}
	void Buffer::Clear() {
		for(uint64_t lId = 0; lId < this->mAmountAllocated; lId++) {
			this->mBuffer[lId] = 0;
		}
		this->mAmountAllocated = 0;
	}
	void Buffer::ShiftLeft(const uint64_t aAmount) {
		if(aAmount == 0) { return; }
		for(uint64_t lId = 0; lId < this->mAmountAllocated - aAmount; lId++) {
			this->mBuffer[lId] = this->mBuffer[lId + aAmount];
		}
		this->RemoveLast(aAmount);
	}
	void Buffer::operator<<(const uint64_t aAmount) { this->ShiftLeft(aAmount); }
	
	int8_t Buffer::Save(File* aFile) {
		ScopeTimer lST("BufferSave");
		if(!aFile->IsOpen()) { return -1; }
		aFile->ResetRead();
		for(uint64_t lId = 0; lId <= this->mAmountAllocated; lId++) {
			aFile->Append(this->mBuffer[lId]);
		}
		return 0;
	}
	void Buffer::CopyBuffer(Buffer* aBuffer) {
		for(uint64_t lId = 0; lId < Min64(aBuffer->GetAllocAmount(), BUFFER_MAXSIZE - this->mAmountAllocated); lId++) {
			this->Append(aBuffer->Get(lId));
		}
	}
	
	void Buffer::Print() {
		for(uint64_t lId = 0; lId < this->mAmountAllocated; lId++) { std::putchar(this->mBuffer[lId]); }
	}
	void Buffer::PrintFormatted() {
		for(uint64_t lId = 0; lId < uint64_t(std::ceil(double(this->mAmountAllocated) / 20.0f)); lId++) {
			std::cout << lId << ": ";
			for(uint64_t llId = 0; llId < 20; llId++) {
				std::putchar(this->mBuffer[(lId * 20 - 1) + llId]);
			}
			std::putchar('\n');
		}
	}
	void Buffer::PrintAll() {
		for(uint64_t lId = 0; lId < BUFFER_MAXSIZE; lId++) {
			if(this->mBuffer[lId] == 0) { break; }
			std::putchar(this->mBuffer[lId]);
		}
	}
	void Buffer::PrintFormattedAll() {
		for(uint64_t lId = 0; lId < uint64_t(std::ceil(double(BUFFER_MAXSIZE) / 20.0f)); lId++) {
			std::cout << lId << ": ";
			for(uint64_t llId = 0; llId < 20; llId++) {
				std::putchar(this->mBuffer[(lId * 20 - 1) + llId]);
			}
			std::putchar('\n');
		}
	}
	
	uint64_t Buffer::GetAllocAmount() {
		return this->mAmountAllocated;
	}
	double Buffer::GetAllocPercentage() { return (double(this->GetAllocAmount()) / BUFFER_MAXSIZE) * 100; }

	char Buffer::Get(uint64_t aId) {
		if(aId > this->mAmountAllocated) { ScopedColor lSC(COLOR_RED); std::cout << "Buffer error: ID larger than allocated amount.\n"; return 0; }
		return this->mBuffer[aId];
	}
	void Buffer::Get(OUT char* aArray, uint64_t aIdBegin, uint64_t aAmount) {
		if(aIdBegin + aAmount - 1 > this->mAmountAllocated) { ScopedColor lSC(COLOR_RED); std::cout << "Buffer error: Requesting values with ID larger than allocated amount.\n"; return;}
		for(uint64_t lId = 0; lId < aAmount; lId++) {
			aArray[lId] = this->mBuffer[aIdBegin + lId];
		}
	}
	
	Buffer::~Buffer() {}
	
	Buffer MFSP_STRBUF;
	Buffer MFSP_FINBUF;
	Buffer MFSP_ECHOBUF;
}
