#include <iostream>

#include "FrameDelta.h"

namespace Dream     {
namespace Asset     {
namespace Instances {
namespace Animation {
namespace Dream     {
	
	FrameDelta::FrameDelta(int drawableId, int operation) {
		mPositionDelta = std::vector<float>(3);
		mRotationDelta = std::vector<float>(3);
		mScaleDelta = std::vector<float>(3);
		
		mOperation   = operation;
		mDrawableID  = drawableId;
		mOrbitRadius = 0;
		
		mPositionDelta[0] = 0;
		mPositionDelta[1] = 0;
		mPositionDelta[2] = 0;
		
		mRotationDelta[0] = 0;
		mRotationDelta[1] = 0;
		mRotationDelta[2] = 0;
		
		mScaleDelta[0] = 0;
		mScaleDelta[1] = 0;
		mScaleDelta[2] = 0;
	}

	FrameDelta::~FrameDelta() {}

	FrameDelta* FrameDelta::computeFrameDelta(FrameDelta* start, FrameDelta* end, int steps, int stepIndex) {
		FrameDelta* d = new FrameDelta(start->getDrawableID(), start->getOperation());
		std::vector<float> posDelta;
		std::vector<float> rotDelta;
		computeDeltaVector(posDelta, start->getPositionDelta(), end->getPositionDelta());
		computeDeltaVector(rotDelta, start->getRotationDelta(), end->getRotationDelta());

		switch (d->getOperation()) {
		    default:
		    case FRAME_DELTA_OP_LINEAR:
				posDelta [0] /= steps;
				posDelta [1] /= steps;
				posDelta [2] /= steps;
				break;
		    case FRAME_DELTA_OP_ORBIT:
				break;
			case FRAME_DELTA_OP_BEZIER:
				break;
		}

		rotDelta[0] /= steps;
		rotDelta[1] /= steps;
		rotDelta[2] /= steps;
		d->setPositionDelta(posDelta);
		d->setRotationDelta(rotDelta);
		return d;
    }

	void FrameDelta::computeDeltaVector(std::vector<float> buffer, std::vector<float> a, std::vector<float> b) {
	    buffer[0] = a[0] - b[0];
	    buffer[1] = a[1] - b[1];
		  buffer[2] = a[2] - b[2];
	}

	void FrameDelta::showStatus() {
	    std::cout << "Delta for ID: " << mDrawableID << std::endl;
	    std::cout <<"\tPOS: X: " << mPositionDelta[0] << " Y: " << mPositionDelta[1] << " Z: " << mRotationDelta[2] << std::endl;
	    std::cout <<"\tROT: X: " << mRotationDelta[0] << " Y: " << mRotationDelta[1] << " Z: " << mRotationDelta[2] << std::endl;
	}

	int FrameDelta::getDrawableID() {
		return mDrawableID;
	}


	std::vector<float> FrameDelta::getPositionDelta() {
		return mRotationDelta;
	}
	

	std::vector<float> FrameDelta::getRotationDelta() {
		return mRotationDelta;
	}

	int FrameDelta::getOperation() {
		return mOperation;
	}

	void FrameDelta::setPositionDelta(std::vector<float> pos) {
		mPositionDelta[0] = pos[0];
		mPositionDelta[1] = pos[1];
		mPositionDelta[2] = pos[2];
	}

	void FrameDelta::setRotationDelta(std::vector<float> rot) {
		mRotationDelta[0] = rot[0];
		mRotationDelta[1] = rot[1];
		mRotationDelta[2] = rot[2];
	}
	
	void FrameDelta::setScaleDelta(std::vector<float> scaleDelta) {
		mScaleDelta[0] = scaleDelta[0];
		mScaleDelta[1] = scaleDelta[1];
		mScaleDelta[2] = scaleDelta[2];
	}
	
	std::vector<float> FrameDelta::getScaleDelta() {
		return mScaleDelta;
	}
	
} // End of Dream
} // End of Animation
} // End of Instance
} // End of Asset
} // End of Dream
