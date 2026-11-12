#include <stdio.h>
#include <string.h>

void bit_stuff_sender(const char *data, char *stuffed)
{
    int j = 0, ones = 0;
    for (int i = 0; data[i] != '\0'; i++)
    {
        stuffed[j++] = data[i];
        if (data[i] == '1')
        {
            ones++;
            if (ones == 5)
            {
                stuffed[j++] = '0';
                ones = 0;
            }
        }
        else
        {
            ones = 0;
        }
    }
    stuffed[j] = '\0';
}
void bit_stuff_receiver(const char *stuffed, char *original)
{
    int j = 0, ones = 0, i = 0;
    while (stuffed[i] != '\0')
    {
        original[j++] = stuffed[i];

        if (stuffed[i] == '1')
        {
            ones++;
            if (ones == 5)
            {
                i++; // Skip stuffed 0
                ones = 0;
            }
        }
        else
        {
            ones = 0;
        }

        i++;
    }

    original[j] = '\0';
}

void add_frame(char *frame, const char *data)
{
    const char *FLAG = "01111110";
    char stuffed[256];
    bit_stuff_sender(data, stuffed);
    strcpy(frame, FLAG);
    strcat(frame, stuffed);
    strcat(frame, FLAG);
}
void remove_frame(const char *frame, char *data)
{
    const char *FLAG = "01111110";
    int flag_len = strlen(FLAG);
    int frame_len = strlen(frame);
    if (strncmp(frame, FLAG, flag_len) != 0 ||
        strncmp(frame + frame_len - flag_len, FLAG, flag_len) != 0)
    {
        printf("Error: Invalid frame!\n");
        return;
    }
    char temp[256];
    strncpy(temp, frame + flag_len, frame_len - 2 * flag_len);
    temp[frame_len - 2 * flag_len] = '\0';
    bit_stuff_receiver(temp, data);
}
int main()
{
    char data[256], frame[512], received[256];

    printf("Enter data: ");
    scanf("%255s", data);

    add_frame(frame, data);

    printf("Transmitted Frame: %s\n", frame);

    remove_frame(frame, received);

    printf("Received Data: %s\n", received);

    return 0;
}
