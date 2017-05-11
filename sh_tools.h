#ifndef SH_TOOLS_HEADER_INCLUDED
#define SH_TOOLS_HEADER_INCLUDED

#include <string>
#include <unistd.h>
#include <stdlib.h>

//! УВАГА
//! get_current_dir_name() -- функція нестандартна, 
// є не на всіх система і вимагає #define _GNU_SOURCE  перед <unistd.h>
// Крім того, отак:
// cout << get_current_dir_name();
// її використовувати не можна! Вона виділяє пам'ять malloc() -- див. https://linux.die.net/man/3/getcwd
// яку потім треба звільняти.
std::string my_get_current_dir_name();

#endif 