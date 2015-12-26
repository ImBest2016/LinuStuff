#ifndef __READ_HARD_DISK_H_INCLUDE__
#define __READ_HARD_DISK_H_INCLUDE__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


extern int get_hd_sn(const char* szDevName, char* szSN, int nLimit);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__READ_HARD_DISK_H_INCLUDE__

