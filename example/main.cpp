#include <wdm.hpp>
#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

float some_func(float arg1, float arg2)
{
	return arg1+arg2;
}

PYBIND11_MODULE(module_name_example, handle )
{
	handle.doc()= "This is the first example of porting";
	handle.def("some_fn_python_name", &some_func);
}

int main() {

	// input vectors
	std::vector<double> x{1, 3, 2, 5, 3, 2, 20, 15};
	std::vector<double> y{2, 12, 4, 7, 8, 14, 17, 6};

	// weights
	std::vector<double> w{1, 1, 2, 2, 1, 0, 0.5, 0.3};

	std::cout << "unweighted Kendall's tau: "
			  << wdm::wdm(x, y, "kendall") << std::endl;
	std::cout << "weighted Kendall's tau: "
			  <<  wdm::wdm(x, y, "kendall", w) << std::endl;

	// weighted independence test
	wdm::Indep_test test(x, y, "kendall", w);
	std::cout << "statistic: " << test.statistic() << std::endl;
	std::cout << "p-value: " << test.p_value() << std::endl;

    return 0;
}
