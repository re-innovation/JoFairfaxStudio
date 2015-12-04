#ifndef _COMMANDS_H_
#define _COMMANDS_H_

bool command_is_ready();
void clear_command_ready_flag();

int command_get_motor();
bool command_get_direction();

void command_add_char(char new_char);

#endif
