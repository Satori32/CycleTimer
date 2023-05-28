#include <iostream>
#include <cstdint>
#include <chrono>
#include <thread>
#include <future>

class StopWatch {
	std::chrono::high_resolution_clock::time_point S;
	std::chrono::high_resolution_clock::time_point E;
public:

	typedef std::chrono::milliseconds TimeType;

	StopWatch() { Start(); };

	bool Start() {
		S = E = std::chrono::high_resolution_clock::now();
		return true;
	}
	bool ReStart() {
		return Start();
	}
	bool Stop() {
		E = std::chrono::high_resolution_clock::now();
		return true;
	}

	bool Reset() {
		S = E = std::chrono::high_resolution_clock::now();
		return true;
	}
	template<class T = TimeType>
	T Ellipse() {
		return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - S);
	}
	template<class T = TimeType>
	T Result() {
		return std::chrono::duration_cast<T>(E - S);
	}

};

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

template<class INT>
class TimeTimer :public CycleTimer<INT> {
public:
	TimeTimer(const INT& Mod, std::chrono::nanoseconds NS) :CycleTimer<INT>(Mod), Wait(NS) {}


	bool Start() {
		auto Fun = [this]() { while (IsRunning_) { this->Update(); std::this_thread::sleep_for(Wait); }};
		IsRunning_ = true;
		Fu = std::async(std::launch::async, Fun);

		return true;
	}
	bool Stop() {
		IsRunning_ = false;
		return true;
	}

	virtual ~TimeTimer() {
		Stop();
	}

	bool IsRunning() {
		return IsRunning_;
	}
protected:
	template<class T>
	T MakeCopy(T In) { return In; }

protected:
	bool IsRunning_ = false;
	std::chrono::nanoseconds Wait = { 0 };
	std::future<void> Fu;
};

int main() {

	TimeTimer<std::uintmax_t> TT(7, std::chrono::seconds(2));

	TT.Start();

	while (TT.IsRunning()){
		std::cout << TT.Count() << std::endl;

		if (TT.IsTail()) {
			std::cout << "to end thread." << std::endl;
			TT.Stop();
		}
	}

	std::cout << "end the app." << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(3));
	
	return 0;

}
/** /
int main() {
	CycleTimer<int> CT(16);

	//CT.Update();

	do{
		std::cout << CT.Count() << std::endl;
		CT.Update();
	} while (!CT.IsTail());

	return 0;
}
/**/