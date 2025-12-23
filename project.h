#ifndef PROJE1_H
#define PROJE1_H

typedef struct {
    char *kitapAdi;
    char *yazar;
    unsigned short kategoriKodu;
    float fiyat;
    int basimYili;
} Kitap;

typedef struct {
    char *kategoriAdi;
    unsigned short kategoriKodu;
    Kitap *kategoriKitaplar;
    int kitapSayisi;
    int kapasite;
} Kategori;

Kategori KategoriOlustur(char *ad, unsigned short kod);
Kitap KitapOlustur(char *ad, char *yazar, unsigned short kod, float fiyat, int yil);

void KitapEkle(Kategori *kategoriDizi, int kategoriSayisi, Kitap yeniKitap);

void TumKategorileriYazdir(Kategori *kategoriDizi, int kategoriSayisi);
void EnPahaliKitaplariYazdir(Kategori *kategoriDizi, int kategoriSayisi);
void EskiKitapFiyatGuncelle(Kategori *kategoriDizi, int kategoriSayisi, int yil, float yeniFiyat);

float FiyatOrtalamasiHesapla(Kategori *kategori);
void OrtalamaUstuKitaplariListele(Kategori *kategori);

void DiziyiDosyayaYaz(Kategori *kategoriDizi, int kategoriSayisi);
void DosyadanDiziyeAktar(Kategori **kategoriDiziPtr, int *kategoriSayisiPtr);

void BellekleriBosalt(Kategori *kategoriDizi, int kategoriSayisi);

#endif

