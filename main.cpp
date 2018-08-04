#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "gzstream.h"

using namespace std;

void imprimir_uso()
{
	std::cout << "Uso inadequado. \n"
		<< "Use:	contagem --std\n"
		<< "ou: 	contagem --file arquivo [--gz]\n";
}

int main(int argc, char const *argv[])
{
	std::ifstream ifs;
	std::ofstream ofs;
	igzstream igs;
	ogzstream ogs;
	istream* filein_ = nullptr;
	ostream* fileout_ = nullptr;
	std::string filename;

	bool comprimir = false;

	if(argc == 1)
	{
		imprimir_uso();
		return 0;

	}
	for(int c = 1; c < argc; ++c)
	{
		std::string str(argv[c]);
		if(str == "--file")
		{
			++c;
			if(filein_ != nullptr or c == argc)
			{
				imprimir_uso();
				return 0;
			}
			filename = std::string(argv[c]);

		}
		else if(str == "--gz")
		{
			comprimir = true;
		}
		else if(str == "--std")
		{
			if(filein_ != nullptr)
			{
				imprimir_uso();
				return 0;
			}
			filein_ = &std::cin;
			fileout_ = &std::cout;
			break;
		}
		else
		{
			if(filein_ != nullptr)
			{
				imprimir_uso();
				return 0;
			}
		}
	}
	if(filein_ == nullptr)
	{
		if(comprimir)
		{
			igs.open((filename + std::string(".in.gz")).c_str());
			if(igs.fail())
				throw std::runtime_error("Erro ao abrir arquivo.");
			ogs.open((filename + std::string(".out.gz")).c_str());
			if(ogs.fail())
				throw std::runtime_error("Não foi possível criar o arquivo de saída.");
			filein_ = &igs;
			fileout_ = &ogs;
		
		}
		else
		{
			ifs.open(filename + std::string(".in"));
			if(ifs.fail())
				throw std::runtime_error("Erro ao abrir arquivo.");
			ofs.open(filename + std::string(".out"));
			if(ofs.fail())
				throw std::runtime_error("Não foi possível criar o arquivo de saída.");
			filein_ = &ifs;
			fileout_ = &ofs;
		}
	}
	istream& filein = *filein_;
	ostream& fileout = *fileout_;

	std::set<string> ignore;
	auto ord = [](string a, string b){ return a < b;};
	std::map<std::string, int, decltype(ord)> ocor(ord);

	string palavra;
	while(filein.peek() != '\n')
	{
		if(filein_->eof())
		{
			throw std::runtime_error("Arquivo de entrada inválido.");
		}
		filein >> palavra;
		ignore.insert(palavra);
	}

	while(!filein.eof())
	{
		filein >> palavra;
		if(palavra[0] == '\0')
		{
			break;
		}
		auto find = ignore.find(palavra);
		if(find != ignore.end())
			continue;	
		auto r = ocor.insert( std::pair<string,int>(palavra, 1));
		if(!r.second)
		{
			(*r.first).second++;
		}

	}
	char ultimo_char = '\0';
	std::map<string, int>::iterator it = ocor.begin();
	while (it != ocor.end())
	{
		if(ultimo_char == it->first[0])
			fileout << ' ';
		else if(ultimo_char != '\0')
			fileout << '\n';
		fileout << "("<< it->first << ", " << it->second << ")";
		ultimo_char = it->first[0];
		++it;
	}
	fileout << std::endl;
}
