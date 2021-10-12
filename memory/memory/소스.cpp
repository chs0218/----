#include <iostream>
#include <string>
#include <crtdbg.h>

class Champion {
	std::string name;
};

class LolDic {
	Champion* head = new Champion;
public:
	~LolDic() {
		delete head;
	}
};

int main()
{
	LolDic loldic;



	_CrtDumpMemoryLeaks();

	return 0;
}