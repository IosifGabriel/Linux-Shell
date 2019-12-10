#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void launchProcess(char **args);

#endif