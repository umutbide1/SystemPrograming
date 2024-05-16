#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dllist.h"
#include "fields.h"

int main() {
    IS is;
    Dllist list, tmp, cursor;
    int i, num;
    char *element;

    // Listeyi başlat
    list = new_dllist();
    cursor = NULL;  // Başlangıçta cursor yok.

    // Giriş dosyasını aç
    is = new_inputstruct("giris.dat");
    if (is == NULL) {
        perror("giris.dat açılamadı");
        exit(1);
    }

    // Giriş dosyasından satır oku
    while (get_line(is) >= 0) {
        if (strcmp(is->fields[0], "yaz:") == 0) {
            for (i = 1; i < is->NF; i += 2) {
                num = atoi(is->fields[i]);
                element = is->fields[i + 1];
                while (num > 0) {
                    char *full_element = strdup(element);
                    if (cursor == NULL || dll_next(cursor) == NULL) {
                        dll_append(list, new_jval_v((void *) full_element));
                        cursor = dll_last(list);
                    } else {
                        dll_insert_b(dll_next(cursor), new_jval_v((void *) full_element));
                        cursor = dll_next(cursor);
                    }
                    num--;
                }
            }
        } else if (strcmp(is->fields[0], "sil:") == 0) {
            for (i = 1; i < is->NF; i += 2) {
                num = atoi(is->fields[i]);
                element = is->fields[i + 1];
                cursor = dll_last(list);  // Cursor'u listenin sonuna taşı
                while (num > 0 && cursor != NULL) {
                    if (strcmp((char *) cursor->val.v, element) == 0) {
                        Dllist to_delete = cursor;
                        cursor = cursor->blink;  // Cursor'u bir önceki düğüme taşı
                        dll_delete_node(to_delete);
                        num--;
                    } else {
                        if (cursor == dll_first(list)) {
                            // Cursor listenin başında ise ve eleman bulunamazsa daha fazla geri gitme
                            break;
                        } else {
                            cursor = cursor->blink;  // Aranan eleman bulunamazsa cursor geriye taşınır
                        }
                    }
                }
            }
        } else if (strcmp(is->fields[0], "sonagit:") == 0) {
            cursor = dll_last(list);  // Cursor'u listenin sonuna taşı
        }
    }

    // Cursor'un son konumunu yazdır
    if (cursor != NULL) {
        char *content = (char *) cursor->val.v;
        printf("Cursor son olarak \"%s\" düğümünde.\n", content);
    } else {
        printf("Cursor hiçbir elemanı göstermiyor.\n");
    }
    // cursor islemleri cok dikkatli yapılmali anil buralara dikkat et
    // Çıkış dosyasına yaz
    FILE *out = fopen("cikis.dat", "w");
    if (out == NULL) {
        perror("cikis.dat açılamadı");
        exit(1);
    }
    dll_traverse(tmp, list) {  // bahsettigim o dllist ve fonkiyonları kısmı burası da 
        char *content = (char *) tmp->val.v;
        for (int i = 0; content[i] != '\0'; i++) {
            if (content[i] == '\\' && content[i + 1] == 'b') {
                // \b görürse boşluk yazdır
                fputc(' ', out);
                i++; // 'b' karakterini atla
            } else if (content[i] == '\\' && content[i + 1] == 'n') {
                // \n görürse yeni satıra geç
                fputc('\n', out);
                i++; // 'n' karakterini atla
            } else {
                // Normal karakterleri yazdır
                fputc(content[i], out);
            }
        }
    }
    fclose(out);

    // Temizlik
    free_dllist(list);   // c de en sıkıntılı yerler buralara dikkat et bellek sızıntılarının önüne geç 
    jettison_inputstruct(is);

    return 0;
}