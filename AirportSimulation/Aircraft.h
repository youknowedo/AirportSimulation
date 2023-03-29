#pragma once
#include <deque>

class Aircraft {
public:
	Aircraft(bool startsInAir, int createTime);

	bool startsInAir() const { return _startsInAir; }
	int createTime() const { return _createTime; }

private:
	bool _startsInAir;
	int _createTime;
};
