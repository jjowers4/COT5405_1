#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point start;
high_resolution_clock::time_point stop;
high_resolution_clock::duration run_time;
high_resolution_clock::duration addition_total = high_resolution_clock::duration::zero();
high_resolution_clock::duration subtraction_total = high_resolution_clock::duration::zero();
high_resolution_clock::duration multiplication_total = high_resolution_clock::duration::zero();

string addition(string num_1, string num_2, int num_length)
{
	start = high_resolution_clock::now();
	string sum_l = ""; //string for storing sum of addition
	int carry_num = 0; //carry number - left over number if addition is greater than 9
	int sum_1 = 0; //sum used to track addition of each placeholder
	int sum_2 = 0; //additional sum used for modulo only

	reverse(num_1.begin(), num_1.end()); //reverse strings to calculate addition properly
	reverse(num_2.begin(), num_2.end());

	for (int i = 0; i < num_length; i++) //iterate through calculations
	{
		sum_1 = ((int)num_1[i] - 48) + ((int)num_2[i] - 48) + carry_num; //add two digits plus carry digit. Subtracting 48 to get the correct number using ascii table
		sum_2 = sum_1 % 10; //removes carry number
		sum_l = sum_l + to_string(sum_2); //inserts number to string
		carry_num = sum_1 / 10; //update carry_num for next iteration
	}

	if (carry_num > 0)
	sum_l = sum_l + to_string(carry_num);//push last carry_num if greater than 0

	reverse(sum_l.begin(), sum_l.end()); //reverse sum string to get output in correct order

	stop = high_resolution_clock::now();
	run_time = duration_cast<nanoseconds>(stop - start);
	addition_total = addition_total + run_time;

	//cout << addition_total.count() << endl;

	return sum_l;
}

string subtraction(string num_1, string num_2, int num_length)
{
	start = high_resolution_clock::now();
	string diff_l = "";
	int carry_num = 0;
	int diff_1 = 0;

	for (int i = 0; i < num_length; i++) //check if num_1 value is smaller than num_2
	{
		if (((int)num_1[i] - 48) < ((int)num_2[i] - 48)) //if larger then swap the numbers
			swap(num_1, num_2);
		else if (((int)num_1[i] - 48) >= ((int)num_2[i] - 48)) //if smaller or equal to then keep the same
			break;
	}

	reverse(num_1.begin(), num_1.end()); //reverse strings to calculate subtraction properly
	reverse(num_2.begin(), num_2.end());

	for (int i = 0; i < num_length; i++)
	{
		diff_1 = ((int)num_1[i] - 48) - ((int)num_2[i] - 48) - carry_num; //subtract two digits plus carry digit

		if (diff_1 < 0) //if diff_1 is less than zero then we need to steal the next number by one
		{
			diff_1 = diff_1 + 10;
			carry_num = 1;
		}
		else
			carry_num = 0;

		diff_l = diff_l + to_string(diff_1);	//pushing numbers onto string
	}

	reverse(diff_l.begin(), diff_l.end()); //reverse string to get correct order

	for (int i = 0; i < num_length; i++) //work through string and remove all zeros that are place holders
	{
		if (diff_l[0] == '0')
		{
			diff_l.erase(diff_l.begin());
		}
		else
			break;
	}

	stop = high_resolution_clock::now();
	run_time = duration_cast<nanoseconds>(stop - start);
	subtraction_total = subtraction_total + run_time;

	//cout << subtraction_total.count() << endl;

	return diff_l;
}

string multiplication(string num_1, string num_2, int num_length)
{
	start = high_resolution_clock::now();
	vector<int> product_v(num_length * 2, 0); //store product
	string product_l = "";
	int carry_num = 0;
	int pos_1 = 0; //keep track of position in each number
	int pos_2 = 0;
	int index_num1 = 0; //current number in position
	int index_num2 = 0;
	int step_prod = 0;

	reverse(num_1.begin(), num_1.end()); //reverse to calculate in correct order in string
	reverse(num_2.begin(), num_2.end());

	for (int i = 0; i < num_length; i++) //iteration for num_2 digit
	{
		index_num1 = (int)num_1[i] - 48; //store num_1 digit as int
		carry_num = 0; //reset every time we multiple another line
		pos_2 = 0;

		for (int i = 0; i < num_length; i++) //iteration for num_1 digits being mutliplied to all num_1 digits
		{
			index_num2 = (int)num_2[i] - 48; //store num_2 digit as int
			step_prod = (index_num1 * index_num2) + product_v[pos_1 + pos_2] + carry_num;
			carry_num = step_prod / 10;
			product_v[pos_1 + pos_2] = step_prod % 10;
			pos_2++;
		}

		if (carry_num > 0)
			product_v[pos_1 + pos_2] = product_v[pos_1 + pos_2] + carry_num;

		pos_1++;
	}

	for (int i = 0; i < product_v.size(); i++) //move contents of vector into string
	{
		product_l = product_l + to_string(product_v[i]);
	}

	reverse(product_l.begin(), product_l.end());

	for (int i = 0; i < num_length; i++) //work through string and remove all zeros that are place holders
	{
		if (product_l[0] == '0')
		{
			product_l.erase(product_l.begin());
		}
		else
			break;
	}

	stop = high_resolution_clock::now();
	run_time = duration_cast<nanoseconds>(stop - start);
	multiplication_total = multiplication_total + run_time;

	//cout << multiplication_total.count() << endl;

	return product_l;
}

string division(string num_1, string num_2, int num_length)
{
	string quotient_l = "";

	if ((num_1.length()) < num_2.length()) //when num_2 length is smaller than num_1 then the int division is always 0
	{
		quotient_l = quotient_l + to_string(0);
		return quotient_l;
	}

	// Division calculation was note completed because the whole divisor, which
	// is contained as a string, needs to be accessed in order to divide properly.
	// The instructor, Sumit, was emailed and he stated that i could leave division
	// out of the assignment because of this issue.
	return quotient_l;
}


int main()
{
	string number_1 = "";
	string number_2 = "";
	int first;
	int second;

	// 4-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 4; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 4);
		subtraction(number_1, number_2, 4);
		multiplication(number_1, number_2, 4);

		// Gather Memory Usage
		//     - Amount of memory used for each individual calculation
		//     - Total memory used for each function being ran
		//     - Average amount of memory used for each function being ran
	}

	cout << "4-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;;

	// 8-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 8; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 8);
		subtraction(number_1, number_2, 8);
		multiplication(number_1, number_2, 8);
	}

	cout << "8-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;

	// 16-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 16; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 16);
		subtraction(number_1, number_2, 16);
		multiplication(number_1, number_2, 16);
	}

	cout << "16-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;

	// 32-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 32; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 32);
		subtraction(number_1, number_2, 32);
		multiplication(number_1, number_2, 32);
	}

	cout << "32-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;

	// 64-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 64; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 64);
		subtraction(number_1, number_2, 64);
		 multiplication(number_1, number_2, 64);
	}

	cout << "64-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;

	// 128-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 128; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 128);
		subtraction(number_1, number_2, 128);
		multiplication(number_1, number_2, 128);
	}

	cout << "128-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;

	// 256-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 256; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 256);
		subtraction(number_1, number_2, 256);
		multiplication(number_1, number_2, 256);
	}

	cout << "256-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;

	// 512-Digit Calculations
	for (int i = 0; i < 1000; i++)
	{
		for (int i = 0; i < 512; i++) // randomly assign numbers to both strings
		{
			number_1 = number_1 + to_string(rand() % 10);
			number_2 = number_2 + to_string(rand() % 10);
		}

		addition(number_1, number_2, 512);
		subtraction(number_1, number_2, 512);
		multiplication(number_1, number_2, 512);
	}

	cout << "512-Digits" << endl;
	cout << "Addition: " << endl;
	cout << "Average Time: " << addition_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << addition_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Subtraction: " << endl;
	cout << "Average Time: " << subtraction_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << subtraction_total.count() / 1000000.0 << " milliseconds" << endl << endl;

	cout << "Multiplication: " << endl;
	cout << "Average Time: " << multiplication_total.count() / 1000000000.0 << " milliseconds" << endl;
	cout << "Total Time: " << multiplication_total.count() / 1000000.0 << " milliseconds" << endl << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl << endl;
	
	return 0;
}