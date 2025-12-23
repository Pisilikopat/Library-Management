
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Kategori KategoriOlustur(char *ad, unsigned short kod) {
    Kategori k;
    k.kategoriAdi = malloc(strlen(ad) + 1);
    strcpy(k.kategoriAdi, ad);
    k.kategoriKodu = kod;
    k.kitapSayisi = 0;
    k.kapasite = 2;
    k.kategoriKitaplar = malloc(sizeof(Kitap) * k.kapasite);

    return k;
}

Kitap KitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil) {
    Kitap k;
    k.kitapAdi = malloc(strlen(ad) + 1); // stringlerde +1 kullanılır bitirme biti için
    strcpy(k.kitapAdi, ad);

    k.yazar = malloc(strlen(yazar) + 1);
    strcpy(k.yazar, yazar);

    k.kategoriKodu = kod;
    k.fiyat = fiyat;
    k.basimYili = yil;

    return k;
}

void KitapEkle(Kategori *kategoriDizi, int kategoriSayisi, Kitap yeniKitap) {
    for(int i = 0; i < kategoriSayisi; i++) {
        if(kategoriDizi[i].kategoriKodu == yeniKitap.kategoriKodu) {
            if(kategoriDizi[i].kitapSayisi >= kategoriDizi[i].kapasite) { // eğer kapasite dolmuşsa yeniden hafıza ayır
                kategoriDizi[i].kapasite *= 2;
                kategoriDizi[i].kategoriKitaplar = realloc(kategoriDizi[i].kategoriKitaplar,sizeof(Kitap) * kategoriDizi[i].kapasite);
            }
            kategoriDizi[i].kategoriKitaplar[kategoriDizi[i].kitapSayisi++] = yeniKitap; //kategori dizisinin i'nci elemanının kitap dizisinin sonuna yeni kitabı ekle 
                                                                                        
            return;                                                                   
        }
    }
}

void TumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi) {
   
    for(int i = 0; i < kategoriSayisi; i++) { //tüm kategorileri gez
        printf("Kategori: %s (Kod: %hu)\n", kategoriDizi[i].kategoriAdi, kategoriDizi[i].kategoriKodu); // aktif kategori bilgileri
         for(int j = 0; j < kategoriDizi[i].kitapSayisi; j++) { // kitapları gezen loop 
            Kitap *k = &kategoriDizi[i].kategoriKitaplar[j]; // aktif kitap
            printf("  - %s (%s) %.2f TL %d\n", k->kitapAdi, k->yazar, k->fiyat, k->basimYili); // düzgün formatta yazdır
        }
        printf("\n");
    }
}

float FiyatOrtalamasiHesapla(Kategori *kategori) {
    if(kategori->kitapSayisi == 0) return 0;

    float toplam = 0;
    for(int i = 0; i < kategori->kitapSayisi; i++){
        toplam += kategori->kategoriKitaplar[i].fiyat;
    }
    return toplam / kategori->kitapSayisi;
}

void OrtalamaUstuKitaplariListele(Kategori *kategori) {
    float ort = FiyatOrtalamasiHesapla(kategori);
    for(int i = 0; i < kategori->kitapSayisi; i++)
        if(kategori->kategoriKitaplar[i].fiyat > ort) {
            printf("%s\n", kategori->kategoriKitaplar[i].kitapAdi);
        }
}

void EnPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi) {
    for(int i = 0; i < kategoriSayisi; i++) {
        if(kategoriDizi[i].kitapSayisi == 0) continue;
        Kitap *en = &kategoriDizi[i].kategoriKitaplar[0];
        for(int j = 1; j < kategoriDizi[i].kitapSayisi; j++){
            if(kategoriDizi[i].kategoriKitaplar[j].fiyat > en->fiyat){
                en = &kategoriDizi[i].kategoriKitaplar[j];
            }
        }
        printf("%s en pahali kitap -> %s\n", kategoriDizi[i].kategoriAdi, en->kitapAdi);
    }
}

void EskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat) {
    for(int i = 0; i < kategoriSayisi; i++)
        for(int j = 0; j < kategoriDizi[i].kitapSayisi; j++)
            if(kategoriDizi[i].kategoriKitaplar[j].basimYili < yil){
                kategoriDizi[i].kategoriKitaplar[j].fiyat = yeniFiyat;
            }

}

void DiziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi) {
    FILE *kategoriDosya = fopen("kategoriler.txt", "w");
    FILE *kitapDosya = fopen("kitaplar.txt", "w");

    for(int i = 0; i < kategoriSayisi; i++) {
        fprintf(kategoriDosya, "%hu %s\n", kategoriDizi[i].kategoriKodu, kategoriDizi[i].kategoriAdi);
        for(int j = 0; j < kategoriDizi[i].kitapSayisi; j++) {
            Kitap *k = &kategoriDizi[i].kategoriKitaplar[j];
            fprintf(kitapDosya, "%hu %.2f %d %s %s\n",
                    k->kategoriKodu, k->fiyat, k->basimYili, k->kitapAdi, k->yazar);
        }
    }
    fclose(kategoriDosya);
    fclose(kitapDosya);
}

void DosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr) {
    FILE *kategoriDosya = fopen("kategoriler.txt", "r"); //dosya aç 
    if(!kategoriDosya) {
        printf("dosya açilamadi");
        return;  // dosya bulunamadıysa geri dön 
    }

    int max = 5;
    *kategoriDiziPtr = malloc(sizeof(Kategori) * max); // dosyadaki kategoriler için başlangıç hafızası
    *kategoriSayisiPtr = 0; 
    unsigned short kod;
    char ad[50];

    while(fscanf(kategoriDosya, "%hu %s", &kod, ad) != EOF) { // dosyanın sonuna gelene kadar oku
        if(*kategoriSayisiPtr >= max) { // 
            max *= 2;
            *kategoriDiziPtr = realloc(*kategoriDiziPtr, sizeof(Kategori) * max);
        }

        Kategori yeniKategori = KategoriOlustur(ad, kod);  // Yeni kategori oluştur
        int index = *kategoriSayisiPtr;                     // Mevcut indeks
        (*kategoriDiziPtr)[index] = yeniKategori;          // Dizinin ilgili indeksine ata
        (*kategoriSayisiPtr)++;                             // Kategori sayısını artır

    }

    fclose(kategoriDosya);

    FILE *kitapDosya = fopen("kitaplar.txt", "r");
    if(!kitapDosya) {
        printf("Dosya açma hatasi");
        return;
    }
    
    char yazar[50];
    float fiyat;
    int yil;

    while(fscanf(kitapDosya, "%hu %f %d %s %s", &kod, &fiyat, &yil, ad, yazar) != EOF) {
        Kitap k = KitapOlustur(ad, yazar, kod, fiyat, yil); 
        KitapEkle(*kategoriDiziPtr, *kategoriSayisiPtr, k); //kategori dizini verdim kaç kategori var onu verdim ve eklemek istediğim kitabı verdim
    }
    fclose(kitapDosya);
}

void BellekleriBosalt(Kategori *kategoriDizi, int kategoriSayisi)
{ // kategorileri gez
    for(int i = 0; i < kategoriSayisi; i++) {
        for(int j = 0; j < kategoriDizi[i].kitapSayisi; j++) { // kitapları gez
            free(kategoriDizi[i].kategoriKitaplar[j].kitapAdi);
            free(kategoriDizi[i].kategoriKitaplar[j].yazar);
        }
        free(kategoriDizi[i].kategoriKitaplar);
        free(kategoriDizi[i].kategoriAdi);
    }
    free(kategoriDizi);
}
