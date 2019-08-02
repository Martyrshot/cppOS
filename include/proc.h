#ifndef __PROC_H__
#define __PROC_H__
#include<stdint.h>
#pragma once

enum ProcState {EMBRIO, SLEEPING, RUNNING, RUNNABLE, ZOMBIE, FREE};


extern uint32_t numProc;


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
	Proc(uint32_t PID, bool isKproc=true);
	~Proc();

	/*
	 * GETTERS
	 */

	/*
	 * returns the PID of this instance of Proc
	 */
	uint32_t getPID();

	/*
	 * returns the current ProcState of this instance of Proc
	 */
	ProcState getState();

	/*
         * returns true if this instance of Proc is a kernel proc, false if not
         */
	bool isKproc();

	/*
	 * returns pointer to stack of current process. If kernel proc, returns 0 or NULL
	 * NOTE: Currently the returned value will need to be type casted... I would like to eventually make
	 * 	 a Stack class, but it's not clear to me how to best do this yet.
	 */
	uint32_t getStackPTR();

	/*
	 * SETTERS
	 * Note: As of now, I don't see a reason to allow anyone to modify isKern, so there is no setter
	 */

	/*
	 * Sets this instance of Proc's PID to provided uint.
	 * Returns True is sucessful, false otherwise
	 */
	bool setPID(uint32_t PID);
	
	/*
	 * Sets this instance of Proc's state to provided ProcState.
	 * Returns True is sucessful, false otherwise
	 */
	bool setState(ProcState state);
	
	 /*
	 * Sets this instance of Proc's stack pointer to provided stack pointer.
	 * Returns True is sucessful, false otherwise
	 */
	bool setStack(uint32_t stack);
};

/*
 * The Process table class. This stores all active processes for the kernel to access
 */
class PTable {
private:
	TrimmingLinkedList<Proc> procs;
	Proc *curProc;
	uint32_t nextPIDtoUse;
public:
	Ptable();
	~Ptable();

	/*
	 * Returns the number of processes active
	 */
	uint32_t numProcs();

	/*
	 * returns the currently running process' PCB
	 */
	Proc *getCurProc();

	/*
	 * Adds a PCB to the process table
	 */
	void addProc(Proc newProc);

	/*
	 * returns the next process' PCB in the process table
	 */
	Proc *nextProc();

	/*
	 * returns the next process' PCB in the process table
	 */
	Proc *prevProc();

	/*
	 * returns the first process' PCB in the process table
	 */
	Proc *firstProc();

	/*
	 * returns the lastt process' PCB in the process table
	 */
	Proc *lastProc();
};
#endif
