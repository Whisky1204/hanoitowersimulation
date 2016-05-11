#include <cstdio>
#include <vector>

#define INFINITE -1
using namespace std;

class configurations {
	public:
		vector<int> *start;
		vector<int> *mid;
		vector<int> *dest;
		int index;
};

class commands {
	public:
		vector<int> *start;
		vector<int> *dest;
};

void move_elem(vector<int> *start, vector<int> *dest) {
	int temp;
	
	temp = start->back();
	start->pop_back();
	(*start)[start->size()] = INFINITE;
	dest->push_back(temp);
}

int main(int argc, char** argv) {
	vector<int> first, second, third;
	int total_elem;
	vector<configurations> list_of_configurations;
	vector<commands> list_of_commands;
	configurations temp_configurations, temp_configurations_2;
	commands temp_commands;
	
	scanf("%d", &total_elem);
	first.reserve(total_elem + 1);
	second.reserve(total_elem + 1);
	third.reserve(total_elem + 1);
	list_of_commands.reserve(total_elem + 1);
	list_of_configurations.reserve(total_elem + 1);
	
	for (int i = total_elem; i > 0; i--) {
		first.push_back(i);
		second[i - 1] = INFINITE;
		third[i - 1] = INFINITE;
	}
	
	temp_commands.start = &first;
	temp_commands.dest = &third;
	list_of_commands.push_back(temp_commands);

	temp_configurations.start = &first;
	temp_configurations.mid = &second;
	temp_configurations.dest = &third;
	temp_configurations.index = total_elem;
	list_of_configurations.push_back(temp_configurations);
	
	while (!(list_of_configurations.empty())) {
		temp_configurations = list_of_configurations.back();
		list_of_configurations.pop_back();

		if (temp_configurations.index <= 1) {
			move_elem(temp_configurations.start, temp_configurations.dest);
			if (!(list_of_commands.empty())) {
				temp_commands = list_of_commands.back();
				list_of_commands.pop_back();
				move_elem(temp_commands.start, temp_commands.dest);
			}
		}
		else {
			temp_commands.start = temp_configurations.start;
			temp_commands.dest = temp_configurations.dest;
			list_of_commands.push_back(temp_commands);

			temp_configurations_2.start = temp_configurations.mid;
			temp_configurations_2.mid = temp_configurations.start;
			temp_configurations_2.dest = temp_configurations.dest;
			temp_configurations_2.index = temp_configurations.index - 1;
			list_of_configurations.push_back(temp_configurations_2);

			temp_configurations_2.start = temp_configurations.start;
			temp_configurations_2.mid = temp_configurations.dest;
			temp_configurations_2.dest = temp_configurations.mid;
			temp_configurations_2.index = temp_configurations.index - 1;
			list_of_configurations.push_back(temp_configurations_2);

		}
	}
	
	for (int i = total_elem; i > 0; i--) {
		printf("%d \t %d \t %d\n", first[i - 1], second[i - 1], third[i - 1]);
	}
	
	return 0;
}
