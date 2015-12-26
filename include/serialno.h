#ifndef __SERIAL_NUMBER_H_INCLUDE__
#define __SERIAL_NUMBER_H_INCLUDE__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifdef __cplusplus
extern "C" {
#endif

int get_machine_code(char* szMachineCode, unsigned int maxlen);
int verify_code(const char* szVerifyCode);
    
#ifdef __cplusplus
}
#endif

#endif /* __SERIAL_NUMBER_H_INCLUDE__ */
