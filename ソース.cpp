#include <iostream>
#include <cstdint>

template<class INT>
class CycleTimer {
public:
	CycleTimer() {}
	CycleTimer(const INT& MOD) :M(MOD) {}

	bool IsZero() {
		return (V % M)==0;
	}

	bool IsTail() {
		return (V % M) == (M-1);//take care to -1 method.
	}

	INT Value() {
		return V % M;
	}

	INT Count() { return V; }
	INT MOD() { return M; }

	bool SetMOD(const INT& In) {
		M = In;
		return true;

	}

	bool Reset() {
		V = 0;
		return true;
	}

	bool Update() {
		V++;
		return true;
	}

protected:
	INT V = 0;
	INT M = 7;
};

int main() {
	CycleTimer<int> CT(16);

	//CT.Update();

	do{
		std::cout << CT.Count() << std::endl;
		CT.Update();
	} while (!CT.IsTail());

	return 0;
}