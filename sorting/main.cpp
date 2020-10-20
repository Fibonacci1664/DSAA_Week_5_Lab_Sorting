// Sorting lab exercise
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>


// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::cout;
using std::endl;
using std::list;
using std::ofstream;
using std::sort;
using std::vector;

// Define the alias "the_clock" for the clock type we're going to use.
// (You can change this to make the code below use a different clock.)
typedef std::chrono::steady_clock the_clock;

float sum = 0;
//ofstream intSortingTimes("intSortingTimes.csv");
ofstream vectorSortingTimes("vectorSortingTimes.csv");


// Put "count" random integers in the range (0, 99) into "collection".
// (This is templated so it'll work with any collection type that has push_back.)
template <typename T>
void MakeRandomValues(T& collection, int count)
{
	for (int i = 0; i < count; i++)
	{
		collection.push_back(rand() % 100);
	}
}

// Print out all the items in "collection".
template <typename T>
void ShowValues(const T& collection)
{
	for (auto item : collection)
	{
		cout << item << " : ";
	}

	cout << "\n";
}

// Check that "collection" is in sorted order.
template <typename T>
void AssertSorted(const T& collection)
{
	auto it = collection.begin();

	if (it == collection.end())
	{
		// The collection is empty. So it's sorted!
		return;
	}

	auto prev = it;
	it++;

	while (it != collection.end())
	{
		// Check that each pair of items is in order.
		assert(*it >= *prev);

		prev = it;
		it++;
	}

	// We've got to the end of the list. So it's sorted!
}

template <typename Col, typename Item>
void insertOrdered(Col& collection, Item& item)
{
	auto it = collection.begin();

	while (it != collection.end())
	{
		if (*it > item)
		{
			// Found the item.
			collection.insert(it, item);
			return;
		}

		++it;
	}

	// Never found place to insert, add item to end of list.
	collection.push_back(item);
}

template <typename T>
T insertionSort(T collection)
{
	T output;

	for (auto& item : collection)
	{
		insertOrdered(output, item);
	}

	return output;
}

void implementingSorting()
{
	int num_values = 100;

	cout << "Number of Items\t\tTime 1\t\tTime 2\t\tTime 3\n\n";
	//moreSortingTimes << "Number of Items, Time 1, Time 2, Time 3\n";

	while (num_values <= 2000)
	{
		cout << num_values << "\t\t\t";
		//moreSortingTimes << num_values << ",";

		// Sort each number of items 3 times before incrementing by another 10,000;
		for (int i = 0; i < 3; ++i)
		{
			list<int> input;
			MakeRandomValues(input, num_values);

			// Start timing
			the_clock::time_point start = the_clock::now();
			// Sort the list.
			list<int> output = insertionSort(input);
			// Stop timing
			the_clock::time_point end = the_clock::now();

			// Compute the difference between the two times in milliseconds
			auto time_taken = duration_cast<milliseconds>(end - start).count();
			//cout << "Time taken to sort " << num_values << " intergers = " << time_taken << " ms.\n\n";

			cout << time_taken << "ms\t\t";
			//moreSortingTimes << time_taken << ", ";

			if (i == 2)
			{
				cout << '\n';
				//moreSortingTimes << ",\n";
			}

			//cout << "After sorting: ";
			//ShowValues(output);
			//AssertSorted(output);
		}

		// Increment by 10,000
		num_values += 100;
	}

	// Add values.
	/*shopping.push_back("Milk");
	shopping.push_back("Bread");
	shopping.push_back("Cookies");
	shopping.push_back("Sausages");
	shopping.push_back("Coffee");
	shopping.push_back("Sugar");
	shopping.push_back("Tea");*/

	//ShowValues(nums);
	//shopping.sort();

	//list<int> sorted = insertionSort(nums);

	//ShowValues(shopping);

	//AssertSorted(orderedShopping);

	/*insertOrdered(sorted, "Apples");
	insertOrdered(sorted, "Brisket");
	insertOrdered(sorted, "Peas");
	insertOrdered(sorted, "Yoghurts");*/

	//ShowValues(sorted);
	//AssertSorted(shopping);
}

void implementingSortingVector()
{
	int num_values = 100;

	cout << "Number of Items\t\tTime 1\t\tTime 2\t\tTime 3\n\n";
	vectorSortingTimes << "Number of Items, Time 1, Time 2, Time 3\n";

	while (num_values <= 2000)
	{
		cout << num_values << "\t\t\t";
		vectorSortingTimes << num_values << ",";

		// Sort each number of items 3 times before incrementing by another 10,000;
		for (int i = 0; i < 3; ++i)
		{
			vector<int> input;
			MakeRandomValues(input, num_values);

			// Start timing
			the_clock::time_point start = the_clock::now();
			// Sort the list.
			vector<int> output = insertionSort(input);
			// Stop timing
			the_clock::time_point end = the_clock::now();

			// Compute the difference between the two times in milliseconds
			auto time_taken = duration_cast<milliseconds>(end - start).count();
			//cout << "Time taken to sort " << num_values << " intergers = " << time_taken << " ms.\n\n";

			cout << time_taken << "ms\t\t";
			vectorSortingTimes << time_taken << ", ";

			if (i == 2)
			{
				cout << '\n';
				vectorSortingTimes << ",\n";
			}

			//cout << "After sorting: ";
			//ShowValues(output);
			//AssertSorted(output);
		}

		// Increment by 10,000
		num_values += 100;
	}
}

void writingToCSV()
{
	srand((unsigned int)time(NULL));		// Seed the rng.

	int num_values = 10000;

	cout << "Number of Items\t\tTime 1\t\tTime 2\t\tTime 3\n\n";
	vectorSortingTimes << "Number of Items, Time 1, Time 2, Time 3\n";

	while (num_values <= 100000)
	{
		//cout << "Sorting " << num_values << " integers\n";

		cout << num_values << "\t\t\t";
		vectorSortingTimes << num_values << ",";

		// Sort each number of items 3 times before incrementing by another 10,000;
		for (int i = 0; i < 3; ++i)
		{
			list<int> input;
			MakeRandomValues(input, num_values);
			//cout << "Before sorting: ";
			//ShowValues(input);

			// Sort the list.
			list<int> output = input;

			// Start timing
			the_clock::time_point start = the_clock::now();
			output.sort();
			// Stop timing
			the_clock::time_point end = the_clock::now();

			// Compute the difference between the two times in milliseconds
			auto time_taken = duration_cast<milliseconds>(end - start).count();
			//cout << "Time taken to sort " << num_values << " intergers = " << time_taken << " ms.\n\n";

			cout << time_taken << "ms\t\t";
			vectorSortingTimes << time_taken << ", ";

			if (i == 2)
			{
				cout << '\n';
				vectorSortingTimes << ",\n";
			}

			//cout << "After sorting: ";
			//ShowValues(output);
			AssertSorted(output);
		}

		// Increment by 10,000
		num_values += 10000;
	}
}

int main(int argc, char *argv[])
{
	//writingToCSV();
	//implementingSorting();
	implementingSortingVector();

	cout << "All OK!\n";

	return 0;
}