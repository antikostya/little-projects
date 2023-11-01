
#include <common.hpp>
#include <DNF.hpp>

static int log2(unsigned long n)
{
	unsigned long i = 1;
	unsigned long ans = 0;

	while (i < n) {
		i *= 2;
		++ans;
	}
	return ans;
}

DNF::DNF(const std::string &input)
	: input(input)
{
	if (not powerof2(input.size())) {
		panic("input size not power of two");
	}

	for (unsigned int i = 0; i < input.size(); ++i) {
		switch (input.at(i)) {
		case '1':
			data.push_back(Impl(i, false));
			break;
		case '0':
			break;
		case '-':
			data.push_back(Impl(i, true));
			break;
		default:
			break;
		}
	}
}

DNF::~DNF()
{
}

int DNF::step()
{
	std::vector<Impl> next;
	int patched = 0;

	for (unsigned int i = 0; i < data.size(); ++i) {
		for (unsigned int j = 0; j < data.size(); ++j) {
			if (Impl::can_patch(data.at(i), data.at(j))) {
				std::cerr << "patching " << i << ' ' << j << std::endl;
				Impl impl = Impl::patch(data.at(i), data.at(j));
				if (std::find(next.begin(), next.end(), impl) == next.end()) {
					next.push_back(impl);
				}
				++patched;
			}
		}
	}
	for (unsigned int i = 0; i < data.size(); ++i) {
		if (data.at(i).pw == false) {
			next.push_back(data.at(i));
		}
	}

	data.swap(next);

	std::cerr << "patched " << patched << " implicants" << std::endl;
	return patched;
}

bool DNF::full_coverage(const std::string &bitmask)
{
	std::vector<int> covered(input.size(), 0);
	int sum = 0;

	for (int di = 0; di < data.size(); ++di) {
		Impl &d = data.at(di);

		if (bitmask.at(di) == 1) {
			continue;
		}

		for (int i = 0; i < input.size(); ++i) {
			if (input.at(i) == '1') {
				covered.at(i) += d.was_overlap(i);
			} else {
				covered.at(i) = 1;
			}
		}
	}

	for (int i : covered) {
		sum += !!i;
	}

	return sum == covered.size();
}

std::string DNF::minimize_table(void)
{
	std::string max_removed(data.size(), 0);

	for (int i = 1; i < data.size(); ++i) {
		std::string removed(i, 1);
		bool success = false;

		removed.resize(data.size());

		do {
			if (full_coverage(removed)) {
				std::cerr << "minimized table down to " << data.size() - i << " rows" << std::endl;
				max_removed = removed;
				success = true;
				break;
			}

		} while (std::prev_permutation(removed.begin(), removed.end()));

		if (not success) {
			std::cerr << "minimizing done" << std::endl;
			break;
		}
	}
	return max_removed;
}

void DNF::minimize(void)
{
	std::string bitmask(input.size(), 0);
	std::vector<Impl> data_min;

	while (true) {
		if (step() == 0) {
			break;
		}
		std::cerr << "new implicants number: " << data.size() << std::endl;
		dump();
		std::cerr << std::endl;
	}
	std::cerr << "patching done" << std::endl;

	std::cerr << std::endl;
	std::cerr << "implicant table" << std::endl;
	table(bitmask);

	std::cerr << std::endl;
	bitmask = minimize_table();
	std::cerr << "\nminimized implicant table" << std::endl;
	table(bitmask);
	std::cerr << std::endl;

	for (int di = 0; di < data.size(); ++di) {
		if (bitmask.at(di) == 0) {
			data_min.push_back(data.at(di));
		}
	}
	data.swap(data_min);
}

void DNF::dump(void)
{
	const int w = 3;

	std::cerr << "num |";
	for (auto &i : data) {
		std::cerr << std::setw(w);
		std::cerr << i.num << " |";
	}
	std::cerr << std::endl;

	std::cerr << "ind |";
	for (auto &i : data) {
		std::cerr << std::setw(w);
		std::cerr << i.ind << " |";
	}
	std::cerr << std::endl;

	std::cerr << "p   |";
	for (auto &i : data) {
		std::cerr << std::setw(w);
		std::cerr << i.p << " |";
	}
	std::cerr << std::endl;

	std::cerr << "pw  |";
	for (auto &i : data) {
		std::cerr << std::setw(w);
		std::cerr << i.pw << " |";
	}
	std::cerr << std::endl;

	std::cerr << "inf |";
	for (auto &i : data) {
		std::cerr << std::setw(w);
		std::cerr << i.inf << " |";
	}
	std::cerr << std::endl;
}

void DNF::table(void)
{
	std::string bitmask(data.size(), 0);

	table(bitmask);
}

void DNF::table(const std::string &bitmask)
{
	const int w = 3;

	std::cerr << "N   \t|";
	for (int i = 0; i < input.size(); ++i) {
		if (input.at(i) == '1') {
			std::cerr << std::setw(w);
			std::cerr << i + 1 << " |";
		}
	}

	std::cerr << '|';
	for (int i = 0; i < input.size(); ++i) {
		if (input.at(i) == '-') {
			std::cerr << std::setw(w);
			std::cerr << i + 1 << " |";
		}
	}
	std::cerr << std::endl;

	for (int di = 0; di < data.size(); ++di) {
		Impl &i = data.at(di);

		if (bitmask.at(di) == 1) {
			continue;
		}

		std::cerr << '(' << i.num << ", " << i.p << ")\t|";

		for (int j = 0; j < input.size(); ++j) {
			if (input.at(j) == '1') {
				std::cerr << std::setw(w);
				if (i.was_overlap(j)) {
					std::cerr << '+';
				} else {
					std::cerr << ' ';
				}
				std::cerr << " |";
			}
		}

		std::cerr << '|';
		for (int j = 0; j < input.size(); ++j) {
			if (input.at(j) == '-') {
				std::cerr << std::setw(w);
				if (i.was_overlap(j)) {
					std::cerr << '+';
				} else {
					std::cerr << ' ';
				}
				std::cerr << " |";
			}
		}
		std::cerr << std::endl;
	}
}

void DNF::print(void)
{
	int nr_var = log2(input.size());

	for (int i = 0; i < nr_var; ++i) {
		std::cout << (char)('a' + i);
	}
	std::cout << std::endl;

	for (auto &d : data) {
		for (int v = nr_var - 1; v >= 0; --v) {
			if (d.p & (1u << v)) {
				std::cout << "-";
			} else if (d.num & (1u << v)) {
				std::cout << "1";
			} else {
				std::cout << "0";
			}
		}
		std::cout << std::endl;
	}
}
