#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <fstream>
#include <chrono>

std::string changeVolume(std::string diffString, bool increasing)
{
	// Yes, I'm better than you.
	return (increasing) ? std::string("pactl set-sink-volume alsa_output.pci-0000_00_1f.3.analog-stereo +") + diffString + std::string("%")
						: std::string("pactl set-sink-volume alsa_output.pci-0000_00_1f.3.analog-stereo -") + diffString + std::string("%");;
}

std::string printVolume()
{
	// TODO: Learn what this actually means and why it works
	return std::string("amixer get Master | awk -F\"[][]\" '/Left:/ { print $2 }'");
}

int main(int argc, char* argv[])
{
	// store the command to run here
	std::string command;

	// Read the contents of the file into a string. This file contains the system time of the last time this point was reached in the code.
	// This is a temporary solution until I learn how to do this in the xmonad.hs file instead
	std::ifstream fs_in("/home/nick/.config/lastvolpress");
	std::string str( (std::istreambuf_iterator<char>( fs_in )), (std::istreambuf_iterator<char>()) );

	long long last_ms = std::stoll( str ); // Convert the last press time to a long long (probably the type that will be exported by count function later)

	fs_in.close();

	const auto now = std::chrono::system_clock::now(); // get the current time I actually don't know the type and I don't need to know
	long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch() ).count(); // Number of milliseconds since 01-01-1970 0:00
	if(now_ms - last_ms < 15) return 0; // If 15ms has not passed since the last time the volume was adjusted from this program, exit.
	else
	{
		std::ofstream fs_out("/home/nick/.config/lastvolpress", std::ios::trunc); // don't just write to the file but overwrite (trunc)
		fs_out << now_ms;
		fs_out.close();
		// If there is no argument, print the master volume
		if(argc == 1) command = printVolume();
		else 
		{
			// This is not production code and I am using it in a very limited case on my system.
			// Minimal security implemented!!
			// ssume only 2 arguments


			// I'm reading this next line now and it's really obtuse but I'm going to leave it here just to keep future Nick on his toes. Check key bindings in xmonad if you're stuck
			auto action = std::make_pair( std::string(argv[1]), std::string(argv[2]) );

			// if you ain't up, you're down ... or whatever ricky bobby said
			if(action.first == "up") command = changeVolume( action.second, true);
			else command = changeVolume( action.second, false);

		}
	}
	std::system(command.c_str()); // run the command
	return 0;
}
