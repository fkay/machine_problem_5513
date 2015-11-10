#include <cassert>
#include "decode.h"

DecodeStage::DecodeStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == IF);
}

void DecodeStage::process() {
	//Check if need to stall
	AbstractStage* checkStall = nextStage;
	if(!stalled) //only check if not stalled yet
		while(checkStall != NULL) {
			if(checkStall->getInstruction().isDataDependent(ins)) {
				setStalled();
				break;		
			}
			checkStall = checkStall->getNextStage();
	}
	// If not stalled load ALU values
	if(!stalled) {
		if(ins.isAluImm() || ins.isMemory()) {
			ins.setA(getReg(ins.getArg2()));
			ins.setB(ins.getImmidiate());
		}
		if(ins.isAluReg()) {
			ins.setA(getReg(ins.getArg2()));
			ins.setB(getReg(ins.getArg3()));
		}
		if(ins.isBranch()) {
			ins.setA(getReg(ins.getArg1()));
			ins.setB(ins.getImmidiate());
		}
				
		//and finally pass the instruction to next stage
		nextStage->setInstruction(ins);
	} else {
		nextStage->getInstruction().clear();	// insert a bubble
	}
	
}

DecodeStage::~DecodeStage() {
}
