#ifndef _INCLUDE_LAZY_SCRIPT_H_
#define _INCLUDE_LAZY_SCRIPT_H_

#include <stdio.h>
#include <string.h>

#define CMD_SIZE 11
#define PARAM_SIZE 11
#define PARAM_NUM 4

#define CONSOLE_CR 0x0d    // "\r"
#define CONSOLE_LF 0x0a    // "\n"
#define CONSOLE_SPACE 0x20 // " "

typedef struct
{
    char cmd[CMD_SIZE];
    char params[PARAM_NUM][PARAM_SIZE];
} command_s;

typedef struct
{
    char cmd[CMD_SIZE];
    void (*function)(command_s *cmd);
} LazyScript_action;

class LazyScript
{
public:
    LazyScript(LazyScript_action *action_setting);
    void parser(uint8_t data);

private:
    typedef enum
    {
        decode_cmd = 0,
        decode_param_1,
        decode_param_2,
        decode_param_3,
        decode_param_4,

        decode_invalid
    } decode_state_e;

    LazyScript_action *actions_pt;
    uint16_t action_num;
    command_s buf;
    uint8_t state = decode_cmd;
    uint8_t byte_cnt = 0;
};

#endif
