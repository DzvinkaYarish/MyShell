#include "sh_tools.h"

std::string my_get_current_dir_name()
{
	char* cur_dir = getcwd(NULL, 0);
	std::string res(cur_dir);
	free(cur_dir);
	return res;
}
