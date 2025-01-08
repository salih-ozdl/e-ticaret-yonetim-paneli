#include <stdio.h>
#include <string.h>
#include <locale.h>
struct Urun {
    char ad[100];
    float fiyat;
    int stok;
    char aciklama[200];
};

int stringEsitMi(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;  
        }
        i++;
    }
    return (str1[i] == str2[i]);  
}

int girisYap(float *deger) {
    int kontrol;
    while ((kontrol = scanf("%f", deger)) != 1) { 
        printf("Geçersiz giriþ! Lütfen bir sayi girin: ");
        while (getchar() != '\n');  
    }
    return 1;
}

void urunEkle(struct Urun urunler[], int *urunSayisi) {
    struct Urun yeniUrun;

    printf("\nUrun Adini Girin: ");
    scanf(" %[^\n]", yeniUrun.ad);

    printf("Urun Fiyatini Girin: ");
    girisYap(&yeniUrun.fiyat);  

    printf("Urun Stok Miktarini Girin: ");
    while (scanf("%d", &yeniUrun.stok) != 1) { 
        printf("Geçersiz giriþ! Lütfen bir sayi girin: ");
        while (getchar() != '\n');  
    }

    printf("Urun Aciklamasini Girin: ");
    scanf(" %[^\n]", yeniUrun.aciklama);

    urunler[*urunSayisi] = yeniUrun;  
    (*urunSayisi)++; 
}

void urunYazdir(struct Urun urun) {
    printf("\nUrun Adi: %s\n", urun.ad);
    printf("Fiyat: %.2f TL\n", urun.fiyat);
    printf("Stok Durumu: %d adet\n", urun.stok);
    printf("Aciklama: %s\n", urun.aciklama);
}

void fiyatGuncelle(struct Urun urunler[], int urunSayisi) {
    char urunAdi[100];
    float yeniFiyat;
    int bulundu = 0;

    printf("\nFiyatini guncellemek istediginiz urunun adini girin: ");
    scanf(" %[^\n]", urunAdi);

    for (int i = 0; i < urunSayisi; i++) {
        if (stringEsitMi(urunler[i].ad, urunAdi)) {  
            urunYazdir(urunler[i]);
            printf("\nYeni fiyati girin: ");
            girisYap(&yeniFiyat);  
            urunler[i].fiyat = yeniFiyat;
            printf("%s urununun yeni fiyati: %.2f TL\n", urunler[i].ad, urunler[i].fiyat);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu) {
        printf("Urun bulunamadi!\n");
    }
}

void dolarKurunuGuncelle(struct Urun urunler[], int urunSayisi, float eskiKur, float yeniKur) {
    printf("\nFiyatlar guncelleniyor...\n");
    for (int i = 0; i < urunSayisi; i++) {
        urunler[i].fiyat = urunler[i].fiyat / eskiKur * yeniKur;
        printf("%s urununun yeni fiyati: %.2f TL\n", urunler[i].ad, urunler[i].fiyat);
    }
    printf("\nDolar kuru %.2f'den %.2f'ye guncellendi.\n", eskiKur, yeniKur);
}

void tumUrunleriYazdir(struct Urun urunler[], int urunSayisi) {
    printf("\n--- Urun Listesi ---\n");
    for (int i = 0; i < urunSayisi; i++) {
        urunYazdir(urunler[i]);
    }
}

int main() {
	
	setlocale(LC_ALL,"Turkish");
    struct Urun urunler[10];
    int urunSayisi = 0;
    int secim;
    float dolarKur = 27.0;

    while (1) {
        printf("\n--- E-Ticaret Urun Yonetimi ---\n");
        printf("1. Urun Ekle\n");
        printf("2. Urun Listesi Goruntule\n");
        printf("3. Fiyat Guncelle\n");
        printf("4. Dolar Kurunu Guncelle ve Fiyatlari Yeniden Hesapla\n");
        printf("5. Cik\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                urunEkle(urunler, &urunSayisi);
                break;
            case 2:
                tumUrunleriYazdir(urunler, urunSayisi);
                break;
            case 3:
                fiyatGuncelle(urunler, urunSayisi);
                break;
            case 4: {
                float yeniKur;
                printf("Mevcut dolar kuru: %.2f\n", dolarKur);
                printf("Yeni dolar kurunu girin: ");
                girisYap(&yeniKur);  
                if (yeniKur > 0) {
                    dolarKurunuGuncelle(urunler, urunSayisi, dolarKur, yeniKur);
                    dolarKur = yeniKur;
                } else {
                    printf("Gecersiz dolar kuru!\n");
                }
                break;
            }
            case 5:
                printf("Cikiliyor...\n");
                return 0;
            default:
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
        }
    }

    return 0;
}
