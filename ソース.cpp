#include <iostream>>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>

class ClockCounter {
public:
	ClockCounter() {
		Start();
		SetTimeOut(10 * GetClockParSec() + S);
	}
	ClockCounter(std::clock_t In) {
		Start();
		SetTimeOut(In+S);
	}
	bool Start() {
		S = std::clock();
		return true;
	}
	std::clock_t GetStert() {
		return S;
	}
	std::clock_t GetEnd() {
		return E;
	}
	bool TestProgress() {
		return std::clock() > E;
	}
	bool SetTimeOut(std::clock_t C) {
		E = C;
		return true;
	}
	bool Restert(){
		return Start();
	}
	bool Reset() {
		S = 0;
		E = 0;
		return true;
	}
	std::clock_t GetClockParSec() {
		return CLOCKS_PER_SEC;
	}
	std::clock_t GetNow() {
		return std::clock()-S;
	}
	std::clock_t GetTimeLaspe() {
		return E - (std::clock() - S);
	}
	bool SetNow() {
		S = std::clock();
		return true;
	}
	std::clock_t GetSection() {
		return E - S;
	}
protected:
	std::clock_t S = 0;
	std::clock_t E = 0;
};

bool MeesagePassing(std::string S) {
	std::cout << S << std::endl;
	return true;
}
bool WaitS(std::clock_t MS,std::chrono::nanoseconds Sleep,std::string S) {
	ClockCounter C(MS);
		
	do {
		MeesagePassing(S);
		std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::nanoseconds> (Sleep));
	} while (!C.TestProgress());
	return true;
}
bool Wait(std::clock_t MS, std::chrono::nanoseconds Sleep) {
	ClockCounter C(MS);

	do {
		std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::nanoseconds> (Sleep));
	} while (!C.TestProgress());
	return true;
}

int main() {
	ClockCounter C;
	std::chrono::seconds S(1);
	do {
		std::cout << C.GetNow() << std::endl;
		WaitS(10, std::chrono::duration_cast<std::chrono::nanoseconds>(S), "Now Sleeping!");
		std::cout << "Now Nap!" << std::endl;
	} while (!C.TestProgress());

	return 0;
}