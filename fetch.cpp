#include <cassert>
#include "fetch.h"

FetchStage::FetchStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage == NULL);
}

void FetchStage::process() {
	// process for this step
	if(!stalled) {
		setInstruction(getNextIns());
		ins.setFetchedAtCycle(getCycle());
		setPc(getPc()+4);	// advance PC
		
		if(ins.isHlt()) {
			setStalled();	// stall this stage only
		}
		
		nextStage->setInstruction(ins); 	// send instruction to next stage
		incStatistics(FETCHEDINS);
		
  	}
  	else {
  		incStatistics(STALLCYCLE);
	}
	
}

FetchStage::~FetchStage() {
}
