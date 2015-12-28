#include "readdisk.h"
#include "des.h"
#include "serialno.h"

static const unsigned char the_key[24] =
{
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01,
    0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23
};

static char gszHdsn[256];
static char gszEntext[1024];


static int _encode_hd_sn_() {
    int result = 0;
    mbedtls_des3_context ctx3;
    mbedtls_des3_init( &ctx3 );
    
    while(!result) {
        char* buf = 0;
        int j = 0;

        mbedtls_des3_set3key_enc( &ctx3, the_key );
        for (j = 0; j < 1; ++j)
            mbedtls_des3_crypt_ecb(&ctx3, buf, buf);
    }
    
    mbedtls_des3_free( &ctx3 );    
    return (0);
}

const char*  encode_hd_sn() {
    int result = 0;
    while(!result) {
        char devName[256];
        char szHdsn[256];
        
        if (0 != (result = get_first_hd(devName, sizeof(devName))))
            break;
        
        if (0 != (result = get_hd_sn(devName, szHdsn, sizeof(szHdsn))))
            break;
        
        {//align 8* with ' '
            int align_len = 8 - strlen(szHdsn) % 8;
            int new_length = align_len + strlen(szHdsn);
            if (new_length + 1 > sizeof(szHdsn)) {
                result = -100;
                break;
            }
        }
        result = _encode_hd_sn_();
        break;
    }
    
    return (result) ? NULL : (const char*)gszEntext;
}

