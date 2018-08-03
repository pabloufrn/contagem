#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
int main(int argc, char const *argv[])
{


	vector<string> stop;

	std::ifstream ifs;
	std::ofstream ofs;

	ifs.open("entrada1.in");
	ofs.open("entrada1.out");


	istream& filein = ifs;
	ostream& fileout = ofs;

	string palavra;
	while(filein >>  palavra)
	{
		stop.push_back(palavra);
	}

	ifs.close();
	ofs.close();

	auto ord = [](string a, string b){ return a < b;};

	std::map<std::string, int, decltype(ord)> ocor(ord);

	while(cin >>  palavra)
	{
		

		auto r = ocor.insert( std::pair<string,int>(palavra, 1));

		if(!r.second)
		{
			(*r.first).second++;
		}
		
	}
	auto it = ocur.begin();
	while (it != ocur.end())
	{
		cout << "("<< ocor->first << ", " << ocor->second << ")\n";
	}



}