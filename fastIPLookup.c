#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define MAX_BASE    256
#define FREE_IP     0x00
#define LKP_FREE    0x00
#define LKP_VALD    0x0F
#define LKP_DEL     0xFF
#define NXT_INVLD   0xFFFF

typedef struct ip_base_t
{
    uint16_t    head;
    uint16_t    tail;
} ip_base;

typedef struct ip_pivot_t
{
    ip_base     ip_base [MAX_BASE];
} ip_pivot;

typedef struct ip_elements_t
{
    uint8_t     state;
    uint8_t     ip_ele [3];
    uint16_t    next;
} ip_elements;


typedef struct fastIpLkp_1024
{
    ip_pivot    base;  
    ip_elements elements [1024];
} FASTIP_1024;


int32_t fastIpInit (FASTIP_1024 *ipPtr)
{
    uint16_t index = 1;

    //printf ("\n DBEUG: %s ptr %p", __func__, ipPtr);

    if (NULL == ipPtr)
        return -1;

    /* set up base */
    for (; index < 256; index++)
    {
        //printf ("\n index %d setup pivot", index);
        (*ipPtr).base.ip_base[index].head = NXT_INVLD;
        (*ipPtr).base.ip_base[index].tail = NXT_INVLD;
    }

    index = 0;

    /* set up elements */
    for (; index < 1024; index++)
    {
        //printf ("\n index %d setup elements", index);
        (*ipPtr).elements [index].state      = LKP_FREE;
        (*ipPtr).elements [index].ip_ele [0] = FREE_IP;
        (*ipPtr).elements [index].ip_ele [1] = FREE_IP;
        (*ipPtr).elements [index].ip_ele [2] = FREE_IP;
        (*ipPtr).elements [index].next       = (index + 1);
    }

    (*ipPtr).base.ip_base[0].head = 0;
    (*ipPtr).base.ip_base[0].tail = index - 1;
    (*ipPtr).elements [index - 1].next = NXT_INVLD;
    return 0;
}

int32_t fastIpShow (FASTIP_1024 *ipPtr)
{
    uint16_t index = 0, subIndex = 0;
    uint16_t nxtIndex = 0;

    /* display free elemnts */
    //printf ("\n\n Free - Head: start Index %u", (*ipPtr).base.ip_base[index].head);
    //printf ("\n Free - Tail: end Index%u", (*ipPtr).base.ip_base[index].tail);

    for (index = 1; index < 256; index++)
    {
        subIndex = (*ipPtr).base.ip_base[index].head;
        
        //printf ("\n Base IP Index %u subIndex %x", index, subIndex);

        if (NXT_INVLD == subIndex)
            continue;

        printf ("\n Base IP Index %u", index);
        printf ("\n Head: %u", (*ipPtr).base.ip_base[index].head);
        printf ("\n Tail: %u", (*ipPtr).base.ip_base[index].tail);

        do {

            if (LKP_FREE != (*ipPtr).elements [subIndex].state)
            {
                printf ("\n - IP: %u.%u.%u.%u", index, \
                            (*ipPtr).elements [subIndex].ip_ele [0], \
                            (*ipPtr).elements [subIndex].ip_ele [1], \
                            (*ipPtr).elements [subIndex].ip_ele [2]);

                subIndex = (*ipPtr).elements [subIndex].next;
            }
            else
                break;
        } while (subIndex != (*ipPtr).base.ip_base[index].tail);

    }

    return 0;
}

int32_t fastIpAdd (FASTIP_1024 *ipPtr, uint32_t ip)
{
    uint8_t  baseIndex = ip & 0xFF;
    uint16_t freeIndex = 0, nextIndex = 0, headIndex = 0;

    //printf ("\n\n IP %x base Index %x", ip, baseIndex);

    if (ip == 0)
        return -1;

    if (NULL == ipPtr)
        return -1;

    freeIndex = (*ipPtr).base.ip_base[0].head;
    //printf ("\n %s Free Index starts from %u", __func__, freeIndex);

    /* check if index is occupied */
    //printf ("\n is baseIndex Head occupied %u", (*ipPtr).base.ip_base [baseIndex].head);
    if (NXT_INVLD == (*ipPtr).base.ip_base [baseIndex].head)
    {
        //printf ("\n first element for %u!", baseIndex);
        (*ipPtr).base.ip_base [baseIndex].head = freeIndex;
        (*ipPtr).base.ip_base [baseIndex].tail = NXT_INVLD;
    }
    else
    {
        //printf ("\n fetching tail element!!");
        
        headIndex = (*ipPtr).base.ip_base [baseIndex].tail;
        if (NXT_INVLD != headIndex)
        {
            uint16_t temp = (*ipPtr).base.ip_base [baseIndex].tail;
            //printf ("\n more than 2 elements under %u!", baseIndex);
            
            (*ipPtr).elements [temp].next = freeIndex;
        }
        (*ipPtr).base.ip_base [baseIndex].tail = freeIndex;
    }

    nextIndex = (*ipPtr).elements [freeIndex].next;
    //printf ("\n %s Next Free Index position: %u", __func__, nextIndex);

    (*ipPtr).elements [freeIndex].ip_ele [0] = (ip >>  8);
    (*ipPtr).elements [freeIndex].ip_ele [1] = (ip >> 16);
    (*ipPtr).elements [freeIndex].ip_ele [2] = (ip >> 24);
    (*ipPtr).elements [freeIndex].state = LKP_VALD ;

    (*ipPtr).base.ip_base [0].head = nextIndex;
    return 0;
}

int main ()
{
    printf ("------------- BEGIN -------------");

#if 0
    printf ("\n Start: %d", (1 << 0));
    printf ("\n End: %d", (1 << 1));
    printf ("\n Max Value: %d\n", (3 << 0));

    printf ("\n Start: %d", (1 << 1));
    printf ("\n End: %d", (1 << 2));
    printf ("\n Max Value: %d\n", (3 << 1));

    printf ("\n Start: %d", (1 << 2));
    printf ("\n End: %d", (1 << 3));
    printf ("\n Max Value: %d\n", (3 << 2));

    printf ("\n Start: %d", (1 << 3));
    printf ("\n End: %d", (1 << 4));
    printf ("\n Max Value: %d\n", (3 << 3));

    printf ("\n Start: %d", (1 << 4));
    printf ("\n End: %d", (1 << 5));
    printf ("\n Max Value: %d\n", (3 << 4));

    printf ("\n Start: %d", (1 << 5));
    printf ("\n End: %d", (1 << 6));
    printf ("\n Max Value: %d\n", (3 << 5));

    printf ("\n Start: %d", (1 << 6));
    printf ("\n End: %d", (1 << 7));
    printf ("\n Max Value: %d\n", (3 << 6));
#endif

    FASTIP_1024 temp;
    fastIpInit (&temp);
    fastIpShow (&temp);
    
    fastIpAdd (&temp, 0x010A0A0A);    
    fastIpAdd (&temp, 0x020A0A0A);    
    fastIpAdd (&temp, 0x030A0A0A);    
    fastIpAdd (&temp, 0x040A0A0A);    
    fastIpAdd (&temp, 0x040A0A0B);    
    fastIpAdd (&temp, 0x040A0A0C);    
    fastIpAdd (&temp, 0x040A0A0D);    
    fastIpAdd (&temp, 0x040A0A0E);    
    fastIpAdd (&temp, 0x040A0A0F);    
        
    fastIpShow (&temp);

    printf ("\n ------------- END -------------\n");

    printf ("\n");
    return 0;
}
