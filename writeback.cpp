#include <cassert>
#include "writeback.h"

WritebackStage::WritebackStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == MEM);
}

void WritebackStage::process() {
	if(ins.isAluImm() || ins.isAluReg()) {
		setReg(ins.getArg1(),ins.getAluOut());
	}
	if(ins.isLoad()) {
		setReg(ins.getArg1(),ins.getLoadMemData());
	}
	if(ins.isHlt()) {
		stopSimulation();
	}
	if(ins.getFetchedAtCycle()!=0) {
		incStatistics(FINISHEDINS);
	}
	//sweep instructions that depends on result from this instruction
	updateDependences(ins.getFetchedAtCycle());
}

WritebackStage::~WritebackStage() {
}
