#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[])
{
	std::string prog("/home/nick/.config/scripts/aesth ");
	std::string argument(argv[1]);
	std::string command = prog + argument;
	system(command.c_str());
	return 0;
}
