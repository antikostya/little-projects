
#ifndef DNF_HPP
#define DNF_HPP

#include <Impl.hpp>
#include <vector>

class DNF
{
private:
	std::string input;
	std::vector<Impl> data;

	int step();
	std::string minimize_table(void);
	bool full_coverage(const std::string &bitmask);

public:
	DNF(const std::string &input);
	~DNF();

	void minimize(void);
	void dump(void);
	void print(void);
	void table(void);
	void table(const std::string &bitmask);
};

#endif /* DNF_HPP */
