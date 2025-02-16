#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[])
{
	std::string prog("/home/nick/.config/scripts/random ");
	// No argument means random is set to true.
	std::string argument((argc > 1) ? argv[1] : "-true");
	std::string command = prog + argument;
	system(command.c_str());
	return 0;
}
