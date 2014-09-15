#include "readfile.h"

bool read(std::vector<std::vector<double>> &data, const char* file_path)
{
	std::string str(file_path);
	std::ifstream file(str);
	// if file cannot be read, return false;
	if (!file.is_open())
		return false;
	//read one line per time
	std::string line;
	
	while (std::getline(file, line))
	{
		std::vector<double>   lineData; //vector of double variables 
		std::stringstream  linestream(line); 
		double value; // single double variable 
		while (linestream >> value)
		{
			lineData.push_back(value);
		}
		data.push_back(lineData);//push vector<double> into dataset
	}
	return true;
}