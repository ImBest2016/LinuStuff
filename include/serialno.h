#ifndef __SERIAL_NUMBER_H_INCLUDE__
#define __SERIAL_NUMBER_H_INCLUDE__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief encode the serial number of first hard disk with the default key
 * \return if succssed return the encoded - text, else return NULL
 */
const char* encode_hd_sn();
int decode_hd_sn(const char* szEntext, char* szHdsn, size_t maxlen);
int encode_expire(const char* szHdsn, const char* szDate, char* szDateCode, size_t maxlen);
int decode_expire(const char* szDateCode, const char* szHdsn, time_t* tDate);
int generate_license(const char* filepath, const char* szHdsn, const char* szDate);
/**
 * \brief check the expire that saved in license filepath
 * \param filepath, the path of license file
 * \param szHdsn, the serial number of first hard disk
 * \return 1 if it was expired, else return 0
 */
int check_expire(const char* filepath, const char* szHdsn);

#ifdef __cplusplus
}
#endif

#endif /* __SERIAL_NUMBER_H_INCLUDE__ */
