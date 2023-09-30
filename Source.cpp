using namespace std;
#include <iostream>
#include<vector>
#include<algorithm>
#include<map>
string DataSet[21][4];
vector<string>CustomerSequence;
vector<char>ItemPurchased;
vector<char>ItemSet;
void get_item_set() {
	ItemSet.push_back(ItemPurchased[0]);
	// loop to get items in ItemsPurchased without repetion 
	for (int i = 0; i < ItemPurchased.size(); i++) { //loop at each character in ItemPurchased
		bool FindChar = false;
		for (int j = 0; j < ItemSet.size(); j++) {
			if (ItemSet[j] == ItemPurchased[i]) {
				FindChar = true;
				break;
			}
		}
		if (!FindChar) {
			ItemSet.push_back(ItemPurchased[i]);
		}
	}
	sort(ItemSet.begin(), ItemSet.end());// to sort charechters alphapitaclly
}
void display_item_set() {
	cout << "Item Set :\n";
	for (char c : ItemSet) {
		cout << c << endl;
	}
	cout << "-----------------------------------------------\n";
}
vector<char>FreqSequence1;
void display_candidate1(int min_sup) {
	cout << "Frequrnt 1-item Sequence:\n";
	cout << "Item:\t" << "Supportcount:\n";
	for (char c : ItemSet) {
		int sup_count = 0;
		for (string s : CustomerSequence) {
			if (s.find(c) != string::npos) {
				sup_count++;
			}
		}
		if (sup_count >= min_sup) {
			FreqSequence1.push_back(c);
			cout << c << "\t" << sup_count << endl;
		}

	}
	cout << "-----------------------------------------------\n";
}
vector<string>candidate2;
vector<string> generate_c2() {
	for (int i = 0; i < FreqSequence1.size(); i++) {
		for (int j = 0; j < FreqSequence1.size(); j++) {
			string g;
			g += FreqSequence1[i];
			g += FreqSequence1[j];
			candidate2.push_back(g);
		}
	}
	return candidate2;
}
map<string, int>FreqSequence2;
map<string, int>support_count2(int m, vector<string> c) {
	for (string item : c) {
		int counter = 0;
		string str = " ";
		for (string seq : CustomerSequence) {
			bool f1 = 0, f2 = 0;
			int t = 0;
			for (int i = 0; i < seq.size(); i++) {
				if (seq[i] == item[0]) {
					f1 = 1;
					t = i;
					break;
				}
			}
			if (f1) {
				for (int j = t + 1; j < seq.size(); j++) {
					if (seq[j] == item[1]) {
						f2 = 1;
						break;
					}
				}
			}
			if (f1 && f2) {
				if (t < seq.size()) {
					if ((seq[t + 1] == item[1])) {
						if ((seq[t + 2] == ')')) {
							continue;
						}
						else if ((seq[t + 2] == '(')) {
							str = "(";
							str += item[0];
							str += item[1];
							str += ")";
						}
					}
				}

				counter++;

			}

		}
		if (counter >= m) {
			if (str != " ") {
				FreqSequence2.insert({ str,counter });
			}
			FreqSequence2.insert({ item,counter });
		}

	}
	return FreqSequence2;
}
void display_Frequent2Item(map<string, int>f) {
	cout << "Frequent 2 item set :\n";
	cout << "Item:\t" << "Supportcount:\n";
	for (auto itr = f.begin(); itr != f.end(); ++itr) {
		cout << itr->first << "\t" << itr->second << endl;
	}
	cout << "-----------------------------------------------\n";
}
vector<string>c3;
vector<string>generate_c3(map<string, int>ff) {
	for (auto itr1 = ff.begin(); itr1 != ff.end(); ++itr1) {
		string str = "(";
		str += itr1->first;
		str += ")";
		for (auto itr2 = ff.begin(); itr2 != ff.end(); ++itr2) {
			string  st = "";
			if (itr1->first == itr2->first) {
				continue;
			}
			//    second char in item1 == first char in item2
			if (itr1->first[1] != '(') { //AB BC ->ABC 
				if (itr1->first[1] == itr2->first[0]) {
					string str = itr1->first;
					str += itr2->first[1];
					c3.push_back(str);
				}
			}
			if ((itr2->first[0] == '(') && (itr1->first[1] == itr2->first[1])) {//FA (AB) --> F(AB)
				st += itr1->first[0];//st=F
				st += itr2->first;//st=F(AB)
				c3.push_back(st);
			}
			if (str == itr2->first) {//AB (AB) --> A(AB)
				st += itr1->first[0];
				st += itr2->first;
				c3.push_back(st);
			}
		}
	}
	return c3;
}
map<string, int>supc3;
map<string, int>support_count3(int min_sup, vector<string>candidate3) {
	for (string item : candidate3) {
		int counter = 0;
		string str = " ";
		for (string seq : CustomerSequence) {
			bool f1 = 0, f2 = 0, f3 = 0;
			int t = 0, l = 0, k = 0;
			//to find first char
			for (int i = 0; i < seq.size(); i++) {
				if (seq[i] == item[0]) {
					f1 = 1;
					t = i;
					break;
				}
			}
			//to find second char
			if (f1) {
				if (t < seq.size()) {
					for (int i = t + 1; i < seq.size(); i++) {
						if (seq[i] == item[1]) {
							f2 = 1;
							l = i;
							break;
						}
					}
				}
			}
			if (f1 && f2) {
				if (l < seq.size()) {
					for (int i = l + 1; i < seq.size(); i++) {
						if (seq[i] == item[2]) {
							f3 = 1;
							k = i;
							break;
						}
					}
				}
			}
			if (f3) {
				//(AB) ||(BC)
				if (seq[t + 1] == item[1] && seq[t + 2] == ')' || (seq[l + 1] == item[2] && seq[l + 2] == ')')) {
					continue;
				}

				counter++;
			}
		}
		if (counter >= min_sup)
			supc3.insert({ item,counter });
	}
	return supc3;
}
void display_Frequent3Item(map<string, int>f) {
	cout << "Frequent 3 item set :\n";
	cout << "Item:\t" << "Supportcount:\n";
	for (auto itr = f.begin(); itr != f.end(); ++itr) {
		cout << itr->first << "\t" << itr->second << endl;
	}
	cout << "-----------------------------------------------\n";

}
vector<string>c4;
vector<string>generate_c4(map<string, int>supc3) {
	for (auto itr1 = supc3.begin(); itr1 != supc3.end(); ++itr1) {
		string last2Chr = itr1->first.substr(1, 2);//str=holds last 2 char in item
		for (auto itr2 = supc3.begin(); itr2 != supc3.end(); ++itr2) {
			string first2Chr = itr2->first.substr(0, 2);//str=holds last 2 char in item
			string str = "";
			if (first2Chr == last2Chr) {
				str = itr1->first;
				str += itr2->first[2];
				c4.push_back(str);
			}
		}
	}
	return c4;
}
map<string, int>supc4;
map<string, int>support_count4(int min_sup, vector<string>candidate4) {
	for (string item : c4) {
		int counter = 0;
		for (string seq : CustomerSequence) {
			bool f1 = 0, f2 = 0, f3 = 0, f4 = 0;
			int t = 0, l = 0, k = 0;
			//to find first char
			for (int i = 0; i < seq.size(); i++) {
				if (seq[i] == item[0]) {
					f1 = 1;
					t = i;
					break;
				}
			}
			//to find second char
			if (f1) {
				if (t < seq.size()) {
					for (int i = t + 1; i < seq.size(); i++) {
						if (seq[i] == item[1]) {
							f2 = 1;
							l = i;
							break;
						}
					}
				}
			}
			//to find third char
			if (f1 && f2) {
				//find third char
				if (l < seq.size()) {
					for (int i = l + 1; i < seq.size(); i++) {
						if (seq[i] == item[2]) {
							f3 = 1;
							k = i;
							break;
						}
					}
				}
			}
			//to fing fourth char
			if (f3 && k < seq.size()) {
				for (int i = k + 1; i < seq.size(); i++) {
					if (seq[i] == item[3]) {
						f4 = 1;
						break;
					}
				}

			}
			if (f4) {
				if (seq[t + 1] == item[1] && seq[t + 2] == ')') {
					continue;
				}
				counter++;
			}
		}
		if (counter >= min_sup)
			supc4.insert({ item,counter });
	}
	return supc4;
}
void display_Frequent4Item(map<string, int>supc) {
	cout << "Frequent 4 item set :\n";
	cout << "Item:\t" << "Supportcount:\n";
	for (auto itr = supc.begin(); itr != supc.end(); ++itr) {
		cout << itr->first << "\t" << itr->second << endl;
	}
	cout << "-----------------------------------------------\n";

}
int main() {
	string DataSet[21][4] =
	{ {"1",  "01",  "A" , "AB(FG)CD"},
	  {"3",  "01",  "B",  "AB(FG)CD"},
	  {"7",  "01",  "FG", "AB(FG)CD"},
	  {"9",  "01",  "C",  "AB(FG)CD"},
	  {"10", "01",  "D",  "AB(FG)CD"},
	  {"1",  "02",  "B",  "BGD"},
	  {"4",  "02",  "G",  "BGD"},
	  {"6",  "02",  "D",  "BGD"},
	  {"1",  "03",  "B",  "BFG(AB)"},
	  {"5",  "03",  "F",  "BFG(AB)"},
	  {"8",  "03",  "G",  "BFG(AB)"},
	  {"9",  "03",  "AB", "BFG(AB)"},
	  {"2",  "04",  "F",  "F(AB)CD"},
	  {"6",  "04",  "AB", "F(AB)CD"},
	  {"8",  "04",  "C",   "F(AB)CD"},
	  {"10", "04",  "D",   "F(AB)CD"},
	  {"3",  "05",  "A",   "A(BC)GF(DE)"},
	  {"4",  "05",  "BC",  "A(BC)GF(DE)"},
	  {"7",  "05",  "G",   "A(BC)GF(DE)"},
	  {"9",  "05",  "F",   "A(BC)GF(DE)"},
	  {"10", "05",  "DE",  "A(BC)GF(DE)"}
	};
	int min_sup = 2;
	//get third colmn (item purchased)
	for (int row = 0; row < 21; row++) {
		string str = DataSet[row][2];
		for (int i = 0; i < str.length(); i++) {
			ItemPurchased.push_back(str[i]);
		}
	}
	//get  fourth colmn
	CustomerSequence.push_back(DataSet[0][3]);
	int i = 0;
	for (int row = 0; row < 21; row++) {
		if (DataSet[row][3] == CustomerSequence[i]) {
			continue;
		}
		CustomerSequence.push_back(DataSet[row][3]);
		i++;
	}
	cout << "Customer Sequence :\n";
	for (string s : CustomerSequence) {
		cout << s << endl;
	}
	cout << "-----------------------------------------------\n";
	get_item_set();
	display_item_set();
	display_candidate1(min_sup);
	vector<string>c2;
	c2 = generate_c2();
	map<string, int>supc2;
	supc2 = support_count2(min_sup, c2);
	display_Frequent2Item(supc2);
	vector<string>candidate3;
	candidate3 = generate_c3(supc2);
	// display_c3();
	map<string, int>supc3;
	supc3 = support_count3(min_sup, candidate3);
	display_Frequent3Item(supc3);
	vector<string>candidate4;
	candidate4 = generate_c4(supc3);
	map<string, int>sup4;
	sup4 = support_count4(min_sup, candidate4);
	display_Frequent4Item(sup4);
	return 0;
}
