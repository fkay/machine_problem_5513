#include <cassert>
#include "execute.h"

ExecuteStage::ExecuteStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == ID);
}

void ExecuteStage::process() {
	bool branch=false;
	switch(ins.getType()){
		case NOP:
			break;
		case ADD:
		case ADDI:
		case LD:
		case ST:
			ins.setAluOut(ins.getA()+ins.getB());
			break;
		case SUB:
		case SUBI:
			ins.setAluOut(ins.getA()-ins.getB());
			break;
		case XOR:
			ins.setAluOut(ins.getA() ^ ins.getB());
			break;
		case AND:
			ins.setAluOut(ins.getA() & ins.getB());
			break;
		case OR:
			ins.setAluOut(ins.getA() | ins.getB());
			break;
		case MUL:
			ins.setAluOut(ins.getA() * ins.getB());
			break;
		case DIV:
			ins.setAluOut(ins.getA() / ins.getB());
			break;
		case HLT:
			//setStalled();		//Stall previous stages
			//stopSimulation();
			break;
		case BEQZ:
			if(ins.getA() == 0)
				branch = true;
			break;
		case BNEQZ:
			if(ins.getA() != 0)
				branch = true;
			break;			
	}
	if(branch) {
		// calc new PC
		setPc(ins.getAddress()+4+ins.getImmidiate()*4);
		//clear instruction fetched
		AbstractStage *previousStages = prevStage;
		while(previousStages != NULL) {
			previousStages->getInstruction().clear();
			previousStages = previousStages->getPrevStage();
		}
		//free stalled stages
		setUnstalled();
	}
	// pass instruction to next stage
	nextStage->setInstruction(ins);
}

ExecuteStage::~ExecuteStage() {
}
