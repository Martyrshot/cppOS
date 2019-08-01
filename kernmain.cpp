#include<stdint.h>

enum ProcState {EMBRIO, SLEEPING, RUNNING, RUNNABLE, ZOMBIE, FREE};

uint32_t numProc = 0;


/*
 * A class that contains all information of a process running in the system.
 */

class Proc {
private:
	uint32_t PID;
	bool isKern;
	uint32_t stack;
	ProcState state;

public:
	Proc(uint32_t PID, bool isKproc=true) {
		this->PID = PID;
		this->isKern = isKproc;
		if (isKproc) {
			this->stack = 0x0;
		}
		else {
			//TODO figure out how to do user level memory
		}
		this->state = EMBRIO;
		this->PID = numProc;
		numProc++;
	}
	~Proc() {
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

	/*
	 * returns the PID of this instance of Proc
	 */
	uint32_t getPID() {
		return this->PID;
	}

	/*
	 * returns the current ProcState of this instance of Proc
	 */
	ProcState getState() {
		return this->state;
	}

	/*
         * returns true if this instance of Proc is a kernel proc, false if not
         */
	bool isKproc() {
		return this->isKern;
	}

	/*
	 * returns pointer to stack of current process. If kernel proc, returns 0 or NULL
	 * NOTE: Currently the returned value will need to be type casted... I would like to eventually make
	 * 	 a Stack class, but it's not clear to me how to best do this yet.
	 */
	uint32_t getStackPTR() {
		return this->stack;
	}

	/*
	 * SETTERS
	 * Note: As of now, I don't see a reason to allow anyone to modify isKern, so there is no setter
	 */

	/*
	 * Sets this instance of Proc's PID to provided uint.
	 * Returns True is sucessful, false otherwise
	 */
	bool setPID(uint32_t PID) {
		if (this->state == FREE) {
			return false;
		}
		this->PID = PID;
		return true;
	}
	
	/*
	 * Sets this instance of Proc's state to provided ProcState.
	 * Returns True is sucessful, false otherwise
	 */
	bool setState(ProcState state) {
		this->state = state;
		return true;
	}
	
	 /*
	 * Sets this instance of Proc's stack pointer to provided stack pointer.
	 * Returns True is sucessful, false otherwise
	 */
	bool setStack(uint32_t stack) {
		if (this->state == FREE) {
			return false;
		}
		this->stack = stack;
		return true;
	}
};




Proc *curProc;



Proc *ptable[16];

extern "C" void kmain()
{
	const short color[15] = {0x0100,0x0200,0x0300,0x0400,0x0500,0x0600,0x0700,0x0800,0x0900,0x0A00,0x0B00,0x0C00,0x0D00,0x0E00,0x0F00};
	const char *hello = "Hello cpp world!";
	short *vga = (short *)0xb8000;
	for (int i = 0; i < 16; i++) {
		vga[i+80] = color[i] | hello[i];
	}
}
