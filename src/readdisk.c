#include "readdisk.h"
#include "mypipe.h"

void print_hard_disk_lisk(void)
{
    PedDevice* dev = 0;
    ped_device_probe_all();
    while((dev = ped_device_get_next(dev))) {
        printf("Device is %s, model is %s\n", dev->path, dev->model);
    }
}

int get_first_hd(char* devName, int len)
{
    PedDevice* dev = 0;
    ped_device_probe_all();
    dev = ped_device_get_next(dev);
    if (dev) {
        strncpy(devName, dev->path, len);
        return (0);
    }
    
    return (-1);
}


int get_hd_sn(const char* szDevName, char* szSN, int nLimit)
{
    struct hd_driveid id;
    int  nRtn = -1;
    int  fd = open(szDevName, O_RDONLY|O_NONBLOCK); 
    if (fd < 0) {
        perror(szDevName);
        return nRtn;
    }
    
    while(1) {
        if(!ioctl(fd, HDIO_GET_IDENTITY, &id)) {
            char* p = (char*)id.serial_no;
            int len = 0;
            
            if (nLimit < (int)strlen(p)) {
                nRtn = -1;
                break;
            }
            
            while(*p) {
                if (!isspace(*p) && len < nLimit - 2)
                    szSN[len++] = *p;
                ++p;
            }
            
            szSN[len] = 0;
            nRtn = 0;
        }
        
        break;
    }    
    close(fd);
    return nRtn;
}


int get_first_hdsn(char* szSN, int nLimit)
{
    char szDevPath[256];

    if (get_first_hd(szDevPath, sizeof(szDevPath)))
        return (-1);

    if (get_hd_sn(szDevPath, szSN, nLimit))
        return (-2);
    
    return (0);
}



int  get_first_hd_via_pipe(char* devName, int len) {
    int found = 0;
    MYPIPE_OPEN("fdisk -l", "r")
    MYPIPE_READ_LINE
        //Disk /dev/sda: 1000.2 GB, 1000204886016 bytes, 1953525168 sectors
        if (!found && !strncmp(the_pipe_buffer, "Disk ", 5)) {
            char* p = strchr(the_pipe_buffer, ':');
            if (p) {
                *p = 0;
                strncpy(devName, (char*)the_pipe_buffer + 5, len);
                *p = ':';
                found = 1;
            } else {
                the_pipe_result = -2;
            }
        }
    MYPIPE_CLOSE
    return (found) ? 0 : the_pipe_result;
}


int  get_hd_sn_via_pipe(const char* szDevName, char* szSN, int nLimit) {
    int found = 0;

    char command[128];
    snprintf(command, 128, "hdparm -i %s", szDevName);
    
    MYPIPE_OPEN(command, "r")
    MYPIPE_READ_LINE
        // Model=WDC WD10EADS-00M2B0, FwRev=01.00A01, SerialNo=WD-WCAV56962982
        if (!found) {
            char *p = strstr(the_pipe_buffer, "SerialNo=");
            if (p) {
                p += strlen("SerialNo=");
                if (strlen(p) < 1)
                    continue;   //read nect line

                if (nLimit < strlen(p))
                    the_pipe_result = -6;
                
                //we got the serial number
                //p1 is SerialNo=WD-WCAV56962982\n
                found = 1;
                int len = 0;
                while(*p) {
                    if (!isspace(*p) && len < nLimit - 2)
                        szSN[len++] = *p;
                    ++p;
                }
                szSN[len] = 0;
            }
        }
    MYPIPE_CLOSE
    MYPIPE_RETURN_PIPE_RESULT
    return (found) ? 0 : the_pipe_result;
}
