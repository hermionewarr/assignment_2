// PHYS 30762 Programming in C++ Assignment 2 
// Hermione Warr
// Start: 04/02/2020 Completed:

// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>

// Functions to compute mean and standard deviation
// Mean
double calculate_mean(int num_elements_in_array, double * data_from_file) {
	double sum{};
	for (int i{}; i < num_elements_in_array; i++) {
		sum = sum + data_from_file[i];
	}
	double mean{sum / num_elements_in_array };
	return mean;
}
//standard deviation
double calculate_standard_deviation(double num_elements_in_array, double mean, double * data_from_file){
	double sum_of_xi_minus_mu_squared{};
	for (int i{}; i < num_elements_in_array; i++) {
		sum_of_xi_minus_mu_squared = sum_of_xi_minus_mu_squared + pow((data_from_file[i] - mean), 2);
	}
	double standard_deviation{ sqrt((sum_of_xi_minus_mu_squared / (num_elements_in_array - 1))) };
	return standard_deviation;
}
//standard error on the mean
double calculate_standard_er_on_mean(double sd, double num_elements_in_array){
	double standard_er_on_mean{ sd / sqrt(num_elements_in_array) };
	return standard_er_on_mean;
}

// Main function
int main()
{
	// Define variables
	int number_data_points{};
	std::string y_n{};
	std::string file_name{};
	
	// Ask user to enter filename
	std::cout << "Please enter the filename: " << std::endl;
	std::cin >> file_name;

	// Open file and check if successful
	std::fstream my_file{ file_name };
	while (!my_file.good()) {
		// Print error message and exit
		std::cerr << "Error: file could not be opened" << std::endl;
		std::cout << "Please enter a valid file name: " << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cin >> file_name;
		return(0);
	}
	//finding the number of data points
	std::string line{};
	while (std::getline(my_file, line)) {
		//doesnt work omg
		std::stringstream streak{};
		if (my_file.fail() && !my_file.eof()) {
			std::cerr << "found not a number" << std::endl;
			my_file.clear(); // take stream out of fail state
			my_file.ignore(100, '\n'); // ignore unwanted characters
			number_data_points-=1;
		}
		//works a bit but messes up everything
		//while (my_file >> ) {
		//	number_data_points++;
		//}
		number_data_points++;
	}
	std::cout << "Number of data points: " << number_data_points << std::endl;

	//return to beginning of file
	my_file.clear();
	my_file.seekg(0, std::ios::beg);

	std::cout << "File Successfully opened!" << std::endl;

	// Allocate memory for data 
	double* milikan_data{ new double[number_data_points] };

	// Read data from file, ignoring any additional bad data	
	for (int i{}; i < number_data_points; i++) {
		if (my_file.fail() && !my_file.eof()) {
			std::cerr << "Found a not number" << std::endl;
			my_file.clear(); // take stream out of fail state
			my_file.ignore(100, '\n'); // ignore unwanted line
			break;
		}
		//while (std::getline(my_file, line)) {
		//	while (my_file >> line) {
		//		my_file >> milikan_data[i];
		//		std::cout << milikan_data[i] << std::endl;
		//	}
		//}
		my_file >> milikan_data[i];
		std::cout << milikan_data[i] << std::endl;
	}

	// Compute mean
	double mean = calculate_mean(number_data_points, milikan_data);
	std::cout << "The mean of your data is: " << mean << "eV" << std::endl;
	// Compute standard deviation
	double standard_deviation = calculate_standard_deviation(number_data_points, mean, milikan_data);
	std::cout << "The standard deviation of your data is: " << standard_deviation << std::endl;
	// Compute standard error of mean
	double std_error_on_mean = calculate_standard_er_on_mean(standard_deviation, number_data_points);
	std::cout << "The standard error on your mean is: +/- " << std_error_on_mean << std::endl;
	
	// Free memory
	delete[] milikan_data;
	std::cout << "Freed memory" << std::endl;
	// Close file
	my_file.close();
	
	return 0;
}