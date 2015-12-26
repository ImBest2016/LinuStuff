/*************************************************************************************
 * 
 * VERY VERY IMPORTANT
 * 
 * --- prequest : ---
 * 1. before you do this test, you must install two libraries and develop libraries
 *    libparted, libuuid and libparted-devel, libuuid-devel
 * 2. you must install the command hdparm
 * 3. make sure you have 'fdisk' command and run as well
 * 4. you must run this programm as root
 * 
 *************************************************************************************/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "readdisk.h"
#include "mypipe.h"
#include "des.h"


int read_and_print_pipe(const char* cmd, const char* model) {
    MYPIPE_OPEN(cmd, model)
    MYPIPE_READ_LINE
        printf("%s", the_pipe_buffer);
    MYPIPE_CLOSE
    MYPIPE_RETURN_PIPE_RESULT
}


TEST_CASE( "Teset for Read Hard Disk Serial Number", "ReadDiskSN") {
    printf("Warning: You must run me as root!\n");
    
    /////////////////////////////////////////////////////////////
    // read hard disk sn
    // printf("Get Hard Disk and Partition:\n");
    // read_and_print_pipe("fdisk -l", "r");
    // printf("\n\n");
    // 
    // get the identify of hard disk
    // printf("Get Hard Disk Identify:\n");
    // read_and_print_pipe("hdparm -i /dev/sda", "r");
    // printf("\n\n");
    /////////////////////////////////////////////////////////////

    char myFirstHD_1[128];
    int result = get_first_hd_via_pipe(myFirstHD_1, 128);
    REQUIRE( result == 0 );
    
    char myFirstHD_2[128];
    result = get_first_hd(myFirstHD_2, 128);   
    REQUIRE( result == 0 );
    
    printf("-Hard Disk path - 1: %s, 2: %s\n", myFirstHD_1, myFirstHD_2);
    REQUIRE( !strcmp(myFirstHD_1, myFirstHD_2) );
    
    
    char szSerialNo_1[256];
    result = get_hd_sn_via_pipe(myFirstHD_1, szSerialNo_1, 256);
    REQUIRE( result == 0 );
    
    char szSerialNo_2[256];
    result = get_hd_sn(myFirstHD_1, szSerialNo_2, 256);
    REQUIRE( result == 0 );
    
    printf("-Serial Number- 1: %s, 2: %s\n", szSerialNo_1, szSerialNo_2);
    REQUIRE( !strcmp(szSerialNo_1, szSerialNo_2) );    
}


TEST_CASE( "Teset for DES, 3DES", "DES") {
    printf("test des\n");
    
    int result = mbedtls_des_self_test(8);
    
    REQUIRE(result == 0);
    
    
    char *path = getenv("HOME");
    printf("path = %s\n",path);
    
    REQUIRE(!strcmp(path, "/root"));
}
