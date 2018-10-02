#include <iostream>
#include <functional>
#include "MessageBus.hpp"
#include "FunctionTraits.hpp"

using std::cout;
using std::endl;
using namespace std;
using namespace func_traits;

int f5(double k) {
	return 55;
}

int main() {
	//int i = 1;
	//std::function<int(double)> f1 = [i](double d) -> int {return 2;};
	//std::function<int(double)> f2 = [&](double d) -> int {return 1;};

	std::function<int(double)> f3 = f5;
	//auto f4 = FunctionTraits<f5>::return_type;
	//cout << typeid(f5).name() << endl;


	//cout << "f1: " << typeid(f1).name() << endl;
	//cout << "f2: " << typeid(f2).name() << endl;

	//cout << ((typeid(f1).name() == typeid(f2).name()) ? "equal" : "not equal") << endl;

	return 0;
}
