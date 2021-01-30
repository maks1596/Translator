#pragma once

struct LabelData {
	int value;
	bool isCounted;

	LabelData(const int &initValue, bool initIsCounted) {
		value = initValue;
		isCounted = initIsCounted;
	}
};
