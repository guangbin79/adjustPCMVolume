#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * adjustPCMVolume(char *audioSamples, int size, float volume) {
        char *array = (char *)malloc(sizeof(char) * size);

        if (!array) return NULL;

        for (int i = 0; i < size; i += 2) {
                // convert byte pair to int
                short buf1 = audioSamples[i + 1];
                short buf2 = audioSamples[i];

                buf1 = (short) ((buf1 & 0xff) << 8);
                buf2 = (short) (buf2 & 0xff);

                short res= (short) (buf1 | buf2);
                long data = (long)res * volume;

                if (data > 0x7FFF) {
                        res = 0x7FFF;
                } else {
                        res = (short)data;
                }

                // convert back
                array[i] = (char) res;
                array[i + 1] = (char) (res >> 8);
        }

        return array;
}

int main(int argc, char *argv[]) {
        char filename[100] = "adjusted_";
        FILE *fp, *fp_adjusted;
        int size;
        char *buffer, *buffer_adjusted;

        fp = fopen(argv[1], "r");
        fp_adjusted = fopen(strcat(filename, argv[1]), "w");

        fseek(fp, 0, SEEK_END);  
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buffer = (char *)malloc(size);
        fread(buffer, size, 1, fp);
        buffer_adjusted = adjustPCMVolume(buffer, size, atof(argv[2]));
        fwrite(buffer_adjusted, size, 1, fp_adjusted);

        fclose(fp_adjusted);
        free(buffer_adjusted);
        free(buffer);
        fclose(fp);
        exit(0);
}

