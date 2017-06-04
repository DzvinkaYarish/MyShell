#ifndef SH_TOOLS_HEADER_INCLUDED
#define SH_TOOLS_HEADER_INCLUDED

#include <string>
#include <unistd.h>
#include <stdlib.h>



//! �����
//! get_current_dir_name() -- ������� ������������, 
// � �� �� ��� ������� � ������ #define _GNU_SOURCE  ����� <unistd.h>
// ��� ����, ����:
// cout << get_current_dir_name();
// �� ��������������� �� �����! ���� ������ ���'��� malloc() -- ���. https://linux.die.net/man/3/getcwd
// ��� ���� ����� ��������.
std::string my_get_current_dir_name();

#endif 