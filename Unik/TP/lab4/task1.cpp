
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
	srandom(time(NULL));

	std::vector<int> v(random() % 100);
	std::generate(v.begin(), v.end(), [](){ return rand() % 200 - 100; });
	std::cout << "vector: ";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

	int find;
	std::cout << "\ninput number to find >> ";
	std::cin >> find;

	std::cout << "number to find: " << find << '\n';
	auto it = std::find_if(v.begin(), v.end(), [find](int x) { return x == find; });
	if (it == v.end()) {
		std::cout << "not found\n";
	} else {
		std::cout << "found: " << *it << '\n';
	}
}

