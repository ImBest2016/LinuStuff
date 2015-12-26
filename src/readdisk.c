#include "readdisk.h"

int get_hd_sn(const char* szDevName, char* szSN, int nLimit)
{
    struct hd_driveid id;
    int  nRtn = -1;
	int  fd = open(szDevName, O_RDONLY|O_NONBLOCK); 
	if (fd < 0)
	{
		perror(szDevName);
		return nRtn;
	}
	if(!ioctl(fd, HDIO_GET_IDENTITY, &id))
	{
		 strncpy(szSN, (const char*)id.serial_no, nLimit);
		 //printf("Model Number=%s\n",id.model);
		 nRtn = 0;
	}
	close(fd);
    return nRtn;
}
