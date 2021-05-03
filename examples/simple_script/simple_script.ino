#include "Lazy_script.h"

static void hello_callback(command_s *cmd)
{
  Serial.println("hello ");
  Serial.write(cmd->params[0]);
  Serial.write(cmd->params[1]);
  Serial.write(cmd->params[2]);
  Serial.write(cmd->params[3]);
}
static void showone_callback(command_s *cmd)
{
  Serial.println("one ");
}

LazyScript_action actions[] =
    {
        {"hello", hello_callback},
        {"showone", showone_callback}};

LazyScript console_1(actions);

void setup()
{
  Serial.begin(115200);
  Serial.println("START");
}

void loop()
{
  if (Serial.available())
  {
    console_1.parser(Serial.read());
  }
  else
  {
    //do nothing
  }
}
