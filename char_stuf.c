#include <stdio.h>
#include <string.h>
#define FLAG 0x7E
#define ESC 0x7D
void char_stuff_sender(const unsigned char *data, int len,unsigned char *stuffed, int *stuffed_len)
{
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (data[i] == FLAG || data[i] == ESC)
        {
            stuffed[j++] = ESC;
            stuffed[j++] = data[i] ^ 0x20;
        }
        else
        {
            stuffed[j++] = data[i];
        }
    }
    *stuffed_len = j;
}
void char_stuff_receiver(const unsigned char *stuffed, int len,unsigned char *data, int *data_len)
{
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (stuffed[i] == ESC)
        {
            i++;
            data[j++] = stuffed[i] ^ 0x20;
        }
        else
        {
            data[j++] = stuffed[i];
        }
    }
    *data_len = j;
}
void print_bytes(const unsigned char *bytes, int len, const char *label)
{
    printf("%s: ", label);
    for (int i = 0; i < len; i++)
    {
        printf("%02X ", bytes[i]);
   }
    printf("\n");
}
int main()
{
    printf("\n============================================================\n");
    printf("       CHARACTER STUFFING - C Implementation\n");
    printf("============================================================\n");
    unsigned char original[] = {
        0x01, 0x7E, 0x02, 0x7D, 0x03, 0x7E, 0x04
    };
    int original_len = sizeof(original);
    unsigned char stuffed[100];
    unsigned char recovered[100];
    int stuffed_len, recovered_len;
    printf("\n[1] ORIGINAL DATA:\n");
    print_bytes(original, original_len, " ");
    char_stuff_sender(original, original_len, stuffed, &stuffed_len);
    printf("\n[2] AFTER STUFFING (Sender):\n");
    print_bytes(stuffed, stuffed_len, " ");
    char_stuff_receiver(stuffed, stuffed_len, recovered, &recovered_len);
    printf("\n[3] AFTER UNSTUFFING (Receiver):\n");
    print_bytes(recovered, recovered_len, " ");
    if (original_len == recovered_len &&
        memcmp(original, recovered, original_len) == 0)
    {
        printf("\nSUCCESS: Original data recovered!\n");
    }
    else
    {
        printf("\nERROR: Data mismatch!\n");
    }
    printf("\n============================================================\n");
    return 0;
}
