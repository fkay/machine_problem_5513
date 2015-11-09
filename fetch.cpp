#include <cassert>
#include "fetch.h"

FetchStage::FetchStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage == NULL);
}

void FetchStage::process() {
	// process for this step
  	if(!stalled) {
		ins = getNextIns();
		ins.setFetchedAtCycle(getCycle());
		nextStage->setInstruction(ins); // send instruction to next stage
  	}
}

FetchStage::~FetchStage() {
}
