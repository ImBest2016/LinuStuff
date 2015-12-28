#include "readdisk.h"
#include "des.h"
#include "base64.h"
#include "serialno.h"

static const unsigned char the_key[24] =
{
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01,
    0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23
};

unsigned char gszHdsn[1025];
unsigned char gszEntext[8193];

#define times_for_encrypt   1

/**
 * return the length of ecrypt code
 */
static int _encode_hd_sn_() {
    int result = 0;
    int j = 0;
    unsigned char* p = gszHdsn;
    int len = (int)strlen((char*)gszHdsn);
    int i = 0;
    
    mbedtls_des3_context ctx3;
    mbedtls_des3_init( &ctx3 );
    mbedtls_des3_set3key_enc( &ctx3, the_key );
    
    
    for (; !result && j < times_for_encrypt; ++j) {
        for (; i < len; i += 8, p += 8) {
            result = mbedtls_des3_crypt_ecb(&ctx3, p, p);
        }
    }

    mbedtls_des3_free( &ctx3 );
    return (result) ? -1 : len;
}

char* append_char(char* buffer, size_t maxlen, char c, size_t n) {
    size_t i = 0;
    size_t len = strlen(buffer);
    if (maxlen < len  + n + 1)
        return (0);
    for (; i < n; ++i)
        buffer[len + i] = c;
    
    buffer[len + i] = 0;
    return buffer;
}


char* append_string(char* buffer, size_t maxlen, const char* str, size_t n) {
    size_t i = 0;
    size_t blen = strlen(buffer);
    size_t slen = strlen(str);
    
    if (maxlen < blen + n * slen + 1)
        return (0);
    
    for (; i < n; ++i) {
        strncpy(buffer + blen, str, maxlen - blen - 1);
        blen += slen;
    }
    
    buffer[blen + slen] = 0;
    return buffer;
}


/**
 * 
 */
int align_multi_8(char* szHdsn, size_t maxlen) {
    char * p = (char*)gszHdsn;

    memset(gszHdsn, 0, sizeof(gszHdsn));
    if (!(strlen(szHdsn) % 8))
        p = append_char(szHdsn, maxlen, ' ', 3);
    
    if (p)
        p = append_string((char*)gszHdsn, sizeof(gszHdsn), szHdsn, 8);
    
    return (p) ? 0 : (-1);
}

int encode_hd_sn(const char* szHdsn) {
    int result = 0;
    int maxlen = strlen(szHdsn) + 9;
    char* buf = (char*)malloc(maxlen);
    
    memset(gszEntext, 0, sizeof(gszEntext));

    strncpy(buf, szHdsn, maxlen);
    if (0 != (result = align_multi_8(buf, maxlen)))
        return -1;
    
    return _encode_hd_sn_();
}

int encode_hd_sn_base64(const char* szHdsn) {
    int result = 0;
    size_t n = 0;
    if (0 > (result = encode_hd_sn(szHdsn)))
        return -2;
    
    result = mbedtls_base64_encode(gszEntext, sizeof(gszEntext), &n, gszHdsn, result);
    if (result != 0 || n != strlen((char*)gszEntext))
        return -3;
    
    return (0);
}


int decode_hd_sn_base64(const char* szEnText) {
    strncpy((char*)gszEntext, szEnText, sizeof(gszEntext));
    //mbedtls_base64_encode()
    
    return (0);
}
