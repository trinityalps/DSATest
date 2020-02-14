#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>

const float Clusterdeviation = 7.0;
const int Clustermin = 7;

//Sums up the value and averages them to get the centre. 
std::string findcentre(std::vector<float> cluster) {
	float sum = accumulate(cluster.begin(), cluster.end(), 0);
	float centre = sum / (static_cast<float>(cluster.size()));
	//This is a simple test to make sure that the value is between 0-360
	if (centre > 360.0) {
		centre = centre - 360.0;
	}
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << centre;
	return stream.str();
}

void findClusters(std::string slist)
{
	std::string delim = ",";
	std::vector<float> parsedstring;

	size_t pos = 0;
	std::string token;

	//Iterate through the string and turn it into a vector
	while ((pos = slist.find(delim)) != std::string::npos) {
		token = slist.substr(0, pos);
		//std::cout << token << std::endl;
		slist.erase(0, pos + delim.length());
		float value = std::stof(token);
		parsedstring.push_back(value);
	}
	
	std::vector<std::vector<float>> clustersfound;

	std::vector<float> curfloat;

	//Iterate through the values and check if they are within standard deviation
	//If the value is within the deviation, it adds them to a vector of values
	// If it isn't it pushes the vector to a vector of vectors and creates a new vector
	for (int i = 0; i < parsedstring.size(); i++) {
		//Edge case to catch the last element
		if ((i + 1) == parsedstring.size()) {
			float ii = parsedstring.at(i) - parsedstring.at(i - 1);
			if (ii < Clusterdeviation) {
				curfloat.push_back(parsedstring.at(i));
				clustersfound.push_back(curfloat);
			}
			else {
				clustersfound.push_back(curfloat);
				curfloat.clear();
				curfloat.push_back(parsedstring.at(i));
				clustersfound.push_back(curfloat);
			}
		}
		else {
			float ii = parsedstring.at(i + 1) - parsedstring.at(i);
				if (ii < Clusterdeviation) {
					curfloat.push_back(parsedstring.at(i));
				}
				else {
					curfloat.push_back(parsedstring.at(i));
					clustersfound.push_back(curfloat);
					curfloat.clear();
				}
		}
	}

	//This section checks if the first point found and the last point are within range of each other
	if (clustersfound.size() > 1) {
		float distoend = 360.0 - clustersfound.back().back();
		float disttostart = clustersfound.front().front() - 0;

		if ((disttostart + distoend) < Clusterdeviation) {
			std::vector<float> combinedStartEnd;
			std::vector<float> front = clustersfound.front();
			//The centre won't be accurate unless you have the front values greater than 360
			for (float& f : front)
				f += 360.0;
			std::vector<float> back = clustersfound.back();
			combinedStartEnd.insert(combinedStartEnd.end(), back.begin(), back.end());
			combinedStartEnd.insert(combinedStartEnd.end(), front.begin(), front.end());
			clustersfound.erase(clustersfound.begin());
			clustersfound.pop_back();
			clustersfound.push_back(combinedStartEnd);
		}
	}
	
	std::string result = "";

	//For each of the vectors of floats, we find the centres
	for(std::vector<float>& cluster : clustersfound) {
		if (cluster.size() > Clustermin) {
			std::string centre = findcentre(cluster);
			result = result + centre + ",";
		}
	}

	//Prints out the centres as a string
	std::cout << result + "\n";
}


int main()
{
	//Iterates through all given test inputs
	for (int i = 0; i < 5; i++) {
		std::string file = "input" + std::to_string(i) + ".txt";
		std::ifstream ifs(file);
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		std::cout << "output" + std::to_string(i) + "\n";
		findClusters(content);

	}

	std::cout << "Press Enter To Exit \n";
	std::getchar();
}
