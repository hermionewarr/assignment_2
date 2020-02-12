// PHYS 30762 Programming in C++ Assignment 2 
// Hermione Warr
// Start: 04/02/2020 Completed: 12/02/2020

// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<sstream>

// Functions to compute mean and standard deviation and error on the mean
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
	std::string line{};
	
	// Ask user to enter filename
	std::cout << "Please enter the filename: " << std::endl;
	std::cin >> file_name;

	// Open file and check if successful
	std::fstream my_file{ file_name };
	if (!my_file.good()) {
		// Print error message and exit
		std::cerr << "Error: file could not be opened" << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
		exit(1);
		return(0);
	}
	std::cout << "File Successfully opened!" << std::endl;

	//finding the number of data points
	int no_of_lines{};
	while (std::getline(my_file, line)) {
		std::stringstream line_input(line);
		double is_line_a_double;
		line_input >> is_line_a_double;
		no_of_lines++;
		if (line_input.fail()) {
			std::cerr << "Found not a number" << std::endl;
			std::cout << "Error on line: " << no_of_lines << std::endl;
			line_input.clear(); // take stream out of fail state
			line_input.ignore(100, '\n'); // ignore unwanted characters
		}
		else if (line_input.good()) {
			number_data_points++;
		}
	}

	std::cout << "Number of data points: " << number_data_points << std::endl;

	//return to beginning of file
	my_file.clear();
	my_file.seekg(0, std::ios::beg);
	
	// Allocate memory for data 
	double* milikan_data{ new double[number_data_points] };

	//allocate data to an arrays
	int data_number{};
	std::cout << "Data: " << std::endl;
	while (std::getline(my_file, line)) {
		std::stringstream line_input(line);
		double is_line_a_double;
		line_input >> is_line_a_double;
		if (line_input.good()) {
			milikan_data[data_number] = is_line_a_double;
			std::cout << milikan_data[data_number] << std::endl;
			data_number++;
		}
		else {
			line_input.clear(); // take stream out of fail state
			line_input.ignore(100, '\n'); // ignore unwanted characters
		}
	}

	// Close file
	my_file.close();

	// Compute mean
	double mean = calculate_mean(number_data_points, milikan_data);
	std::cout << "The mean of your data is: " << mean << "eV" << std::endl;
	// Compute standard deviation
	double standard_deviation = calculate_standard_deviation(number_data_points, mean, milikan_data);
	std::cout << "The standard deviation of your data is: " << standard_deviation << std::endl;
	// Compute standard error of mean
	double std_error_on_mean = calculate_standard_er_on_mean(standard_deviation, number_data_points);
	std::cout << "The standard error on your mean is: +/- " << std_error_on_mean << std::endl;
	
	//set precesion
	std::cout << "To three decimal places: " << std::endl;
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << "mean = " << std::setprecision(3) << mean << "+/-" << std_error_on_mean << " eV" << std::endl;
	std::cout << "The standard deviation of your data is: " << std::setprecision(3) << standard_deviation << "eV" << std::endl;
	
	// Free memory
	delete[] milikan_data;
	std::cout << "Freed memory" << std::endl;
		
	return 0;
}