#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "readfile.h"

bool read( vector<vector<double>> &data,const char* file_path)
{
	std::string str(file_path);
	std::ifstream file(str);
	if (!file.is_open())return false;
	std::string   line;
	// Read one line at a time into the variable line:
	
	while (std::getline(file, line))
	{
		std::vector<double>   lineData;
		std::stringstream  linestream(line);

		double value;
		// Read an integer at a time from the line
		while (linestream >> value)
		{
			// Add the integers from a line to a 1D array (vector)
			lineData.push_back(value);
		}
		// When all the integers have been read add the 1D array
		// into a 2D array (as one line in the 2D array)
		data.push_back(lineData);
	}
	
}