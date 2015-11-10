#include <cassert>
#include "memaccess.h"

MemaccessStage::MemaccessStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == EX);
}

void MemaccessStage::process() {
	if(ins.isLoad()) {
		ins.setLoadMemData(getData(ins.getAluOut()));
	}
	if(ins.isStore()) {
		setData(ins.getAluOut(),ins.getArg1());
	}
	//pass instruction to next stage
	nextStage->setInstruction(ins);
}

MemaccessStage::~MemaccessStage() {
}
