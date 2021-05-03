#include <Arduino.h>
#include "Lazy_script.h"

LazyScript::LazyScript(LazyScript_action *action_setting)
{
    actions_pt = action_setting;
    action_num = sizeof(action_setting); //if use arduino is num of element
}

void LazyScript::parser(uint8_t byte_in)
{
    if (byte_in == CONSOLE_LF)
    {
        //Completed! Do some "things"
        for (uint16_t i = 0; i < action_num; i++)
        {
            if (strcmp(buf.cmd, actions_pt[i].cmd) == 0)
            {
                actions_pt[i].function(&buf);
            }
        }

        //clear buffer and cnt
        memset(&buf, 0, CMD_SIZE + PARAM_SIZE * PARAM_NUM); //cannot use sizeof to get size, calculate by manual
        byte_cnt = 0;
        state = decode_cmd;
        return;
    }
    else if (byte_in == CONSOLE_SPACE)
    {
        byte_cnt = 0;
        state += 1;
        return;
    }

    switch (state)
    {
    case decode_cmd:
        if (byte_cnt < CMD_SIZE - 1)
        {
            buf.cmd[byte_cnt] = byte_in;
        }
        break;
    case decode_param_1:
        if (byte_cnt < PARAM_SIZE - 1)
        {
            buf.params[0][byte_cnt] = byte_in;
        }
        break;
    case decode_param_2:
        if (byte_cnt < PARAM_SIZE - 1)
        {
            buf.params[1][byte_cnt] = byte_in;
        }
        break;
    case decode_param_3:
        if (byte_cnt < PARAM_SIZE - 1)
        {
            buf.params[2][byte_cnt] = byte_in;
        }
        break;
    case decode_param_4:
        if (byte_cnt < PARAM_SIZE - 1)
        {
            buf.params[3][byte_cnt] = byte_in;
        }
        break;
    case decode_invalid:
    default:
        break;
    }

    byte_cnt++;
}
