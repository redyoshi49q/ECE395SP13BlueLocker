#ifndef __IO_EXPERIMENT_H__
#define	__IO_EXPERIMENT_H__
#include "LPC11xx.h"
#include "gpio.h"
#include "uart.h"
#include "stdlib.h"
#include "sha1.h"
#include "spio.h"
#include "storage.h"
#include "hasher.h"
#include "password.h"

#define DEBUG 1

void test(char*);
void set_step_2(char*);
void open(char*);
void close(char*);
void set_step_1(char*);

#endif
