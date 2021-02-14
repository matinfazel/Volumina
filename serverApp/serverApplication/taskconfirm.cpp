#include "taskconfirm.h"

/* This is a sample class for tasks related to the server side */

TaskConfirm::TaskConfirm()
{

}

void TaskConfirm::run()
{
    emit result("confirm\r\n");
}
