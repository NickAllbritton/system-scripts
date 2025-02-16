#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[])
{
	std::string script("/home/nick/.config/scripts/screenshot ");
	std::string arg(argv[1]);
	std::string command = script + arg;
	std::system(command.c_str());
	return 0;
}
