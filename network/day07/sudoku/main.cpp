#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

string hash_table[26];
int state[26];

bool FWord(string word, int &index) {
	int idx = word[word.size() - 1] - 'a';
	for(int i = idx;i != (idx - 1) % 26;i = (i + 1) % 26) {
		if(state[i] != 2) {
			index = i;
			return false;
		}
		if(hash_table[i] == word) {
			index = i;
			return true;
		}
	}
	index = -1;
	return false;
}

void AWord(string word) {
	int index;
	if(FWord(word, index))
		return;
	if(index == -1)
		return;
	state[index] = 2;
	hash_table[index] = word;
}

void DWord(string word) {
	int index;
	if(!FWord(word, index))
		return;
	state[index] = 1;
	hash_table[index] = "";
}

void printWord() {
	bool flag = false;
	for(int i = 0;i < 26;i++) {
		if(state[i] == 2) {
			if(flag) {
				cout << " ";
			} else {
				flag = true;
			}
			cout << hash_table[i];
		}
	}
	cout << endl;
}

int main() {
	string line;
	getline(cin, line);
	string command;
	istringstream iss(line);
	while(getline(iss, command, ' ')) {
		if(command[0] == 'A') {
			AWord(command.substr(1));
		} else if(command[0] == 'D') {
			DWord(command.substr(1));
		} else {
			cout << "invalid input" << endl;
			return 1;
		}
	}
	printWord();
	
	return 0;
}
