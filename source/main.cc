#include <iostream>
#include <functional>
#include <string>
#include "MessageBus.hpp"
#include "FunctionTraits.hpp"

using std::cout;
using std::endl;
using namespace std;
using namespace func_traits;

template <typename Func>
void test(Func&& f) {
	using func_t = FunctionTraits<Func>;
	//cout << typeid(typename func_t::function_wrapper_type).name() << endl;
	auto test_t = LambdaToFuncWrapper(f);

	if (typeid(test_t).name() == typeid(typename func_t::function_wrapper_type).name())
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;

	//return typeid(typename func_t::function_wrapper_type).name();


	//if(typeid(typename func_t::function_wrapper_type).name() == typeid(std::function<double(int, int)>).name() ){
	//	cout << "equal" << endl;
	//}
}

int main() {
	/*
	double i = 1.0;
	int j = 2.0;
	auto f1 = [i](int a,int b) -> double {return i;};
	auto f2 = [j,i](int a,int b) -> double {return j+i;};
	test(std::move(f1));
	test(std::move(f2));
	*/
	std::function<int(int)> f = [](int a) -> int {return 1;};
	test(std::move(f));
	/*
	if(test(std::move(f1)) == test(std::move(f2))){
		cout << "equal" << endl;
	}
	*/
	return 0;
}
