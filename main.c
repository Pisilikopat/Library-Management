#include "project.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Kategori *kategoriDizisi = NULL;
    int kategoriSayisi = 0;

    DosyadanDiziyeAktar(&kategoriDizisi, &kategoriSayisi);

    if(kategoriSayisi == 0) {
        kategoriDizisi = malloc(sizeof(Kategori) * 2);
        kategoriDizisi[0] = KategoriOlustur("BilimKurgu", 101);
        kategoriDizisi[1] = KategoriOlustur("Tarih", 102);
        kategoriSayisi = 2;

        KitapEkle(kategoriDizisi, kategoriSayisi,KitapOlustur("Dune", "Frank_Herbert", 101, 250, 1965));
        KitapEkle(kategoriDizisi, kategoriSayisi,KitapOlustur("Vakif", "Isaac_Asimov", 101, 150, 1951));
        KitapEkle(kategoriDizisi, kategoriSayisi,KitapOlustur("Nutuk", "Ataturk", 102, 300, 1927));
    }

    TumKategorileriYazdir(kategoriDizisi, kategoriSayisi);
    for (int i = 0; i < kategoriDizisi->kapasite; i++)
    {
        
    }
    
    KitapEkle(kategoriDizisi, kategoriSayisi,KitapOlustur("Alchermist", "Paulo_Coelho", 101, 250, 1965));
    printf("\n");
    EnPahaliKitaplariYazdir(kategoriDizisi, kategoriSayisi);
    printf("\n");
    OrtalamaUstuKitaplariListele(&kategoriDizisi[0]);
    printf("\n");

    float a = FiyatOrtalamasiHesapla(&kategoriDizisi[0]);

    printf("BilimKurgu kategorisinin ortalama fiyati: %.2f \n", a);
    printf("\n");

    EskiKitapFiyatGuncelle(kategoriDizisi, kategoriSayisi, 2000, 50);
    TumKategorileriYazdir(kategoriDizisi, kategoriSayisi);

    DiziyiDosyayaYaz(kategoriDizisi, kategoriSayisi);
    BellekleriBosalt(kategoriDizisi, kategoriSayisi);

    return 0;
}
