#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 
void yazma_islemi(const char *komut, FILE *cikisDosyasi) {
    const char *ptr = komut;
    while (*ptr != '\0') {
        if (*ptr == ':') {
            ptr++;
            continue;
        }
        if (*ptr == ' ') {
            ptr++;
            continue;
        }
        if (*ptr >= '0' && *ptr <= '9') {
            int sayi = atoi(ptr);
            while (*ptr >= '0' && *ptr <= '9') {
                ptr++;
            }
            if (*ptr == ' ') {
                ptr++;
            }
            if (*ptr == 'a') {
                for (int i = 0; i < sayi; i++) {
                    fprintf(cikisDosyasi, "a");
                }
            } else if (*ptr == 'b') {
                fprintf(cikisDosyasi, " ");
            } else if (*ptr == 'k') {
                for (int i = 0; i < sayi; i++) {
                    fprintf(cikisDosyasi, "k");
                }
            } else if (*ptr == 'u') {
                for (int i = 0; i < sayi; i++) {
                    fprintf(cikisDosyasi, "u");
                }
            }
        } else {
            fprintf(stderr, "Hatalı komut: %c\n", *ptr);
            exit(EXIT_FAILURE);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Kullanım: %s <giris_dosyasi> <cikis_dosyasi>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *girisDosyasi = fopen(argv[1], "r");
    if (girisDosyasi == NULL) {
        perror("Giris dosyasi acilirken hata olustu");
        return EXIT_FAILURE;
    }

    FILE *cikisDosyasi = fopen(argv[2], "w");
    if (cikisDosyasi == NULL) {
        perror("Cikis dosyasi acilirken hata olustu");
        fclose(girisDosyasi);
        return EXIT_FAILURE;
    }

    char satir[100];
    while (fgets(satir, sizeof(satir), girisDosyasi) != NULL) {
        if (strncmp(satir, "yaz:", 4) == 0) {
            yazma_islemi(satir + 4, cikisDosyasi);
        }
    }

    fclose(girisDosyasi);
    fclose(cikisDosyasi);
    return EXIT_SUCCESS;
}
