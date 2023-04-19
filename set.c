#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int setting_num = 0;
    if(argc!=3){printf(2, "Usage: set x v\nx may be 'd' (demand page), 'i' (info), 's' (syscall trail)\nv is a digit like 0,1\n"); exit();} 
    char setting = argv[1][0];
    char value = argv[2][0] - '0';

    if(setting=='i') {setting_num = 1;} // for printing info / debug mode
    else if(setting == 'd') {setting_num = 2;} // demand paging
    else if(setting == 's') {setting_num = 3;} // trail of syscalls
    else {printf(2, "Usage: set x v\nx may be 'd' (demand page), 'i' (info), 's' (syscall trail)\nv is a digit like 0,1\n"); exit();}
    settings(setting_num, (int)value); //calls syscall "sys_settings"
    exit();
}