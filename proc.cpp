#include<proc.h>

extern uint32_t numProc;

/****************************************************************************************************
 * PROC IMPLEMENTATION
****************************************************************************************************/

Proc::Proc(uint32_t PID, bool isKproc) {
	this->PID = PID;
	this->isKern = isKproc;
	if (isKproc) {
		this->stack = 0x0;
	}
	else {
		//TODO figure out how to do user level memory
	}
	this->state = EMBRIO;
	//this->PID = numProc;
	//numProc++;
}

Proc::~Proc() {
	// TODO, once user stacks have been defined, we will need to free them.
	// we will also need to decide how to manage Procs in the Ptable. Likely
	// make sure it's contiguous on removal... Probably best to have this
	// management mechanism in a Ptable method.
	// I don't know why I didn't make this a comment block....
	this->state = FREE;
}

/*
 * GETTERS
 */

uint32_t Proc::getPID() {
		return this->PID;
}

ProcState Proc::getState() {
	return this->state;
}

bool Proc::isKproc() {
	return this->isKern;
}

uint32_t Proc::getStackPTR() {
	return this->stack;
}

/*
 * SETTERS
 * Note: As of now, I don't see a reason to allow anyone to modify isKern, so there is no setter
 */

bool Proc::setPID(uint32_t PID) {
	if (this->state == FREE) {
		return false;
	}
	this->PID = PID;
	return true;
}
	
bool Proc::setState(ProcState state) {
	this->state = state;
	return true;
}
	
bool Proc::setStack(uint32_t stack) {
	if (this->state == FREE) {
		return false;
	}
	this->stack = stack;
	return true;
}


