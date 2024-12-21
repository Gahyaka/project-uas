#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum KategoriTransaksi {
    INFAK_JUMAT,
    ZAKAT_FITRAH,
    ZAKAT_MAL,
    OPERASIONAL_MASJID,
    KEGIATAN_SOSIAL,
    PEMBANGUNAN
};


union SumberDana {
    char donatur[50];     
    char lembaga[100];    
    char zakat[50];       
};


typedef struct {
    enum KategoriTransaksi kategori;
    int nominal;
    char tanggal[20];
    union SumberDana sumber;
} Transaksi;


typedef struct {
    char nama_masjid[100];
    Transaksi *daftar_transaksi;  
    int jumlah_transaksi;
    int kapasitas;
} ManajemenKeuangan;


ManajemenKeuangan* inisialisasi_keuangan(char *nama_masjid) {

    ManajemenKeuangan *keuangan = malloc(sizeof(ManajemenKeuangan));
    if (keuangan == NULL) {
        printf("Gagal mengalokasikan memori!\n");
        exit(1);
    }

    strcpy(keuangan->nama_masjid, nama_masjid);
    
    
    keuangan->kapasitas = 10;
    keuangan->jumlah_transaksi = 0;
    keuangan->daftar_transaksi = malloc(keuangan->kapasitas * sizeof(Transaksi));
    
    if (keuangan->daftar_transaksi == NULL) {
        printf("Gagal mengalokasikan memori untuk transaksi!\n");
        free(keuangan);
        exit(1);
    }

    return keuangan;
}


void tambah_transaksi(ManajemenKeuangan *keuangan, 
                      enum KategoriTransaksi kategori, 
                      float nominal, 
                      char *tanggal, 
                      union SumberDana sumber) {
    
    if (keuangan->jumlah_transaksi >= keuangan->kapasitas) {
        keuangan->kapasitas *= 2;
        keuangan->daftar_transaksi = realloc(keuangan->daftar_transaksi, 
                                              keuangan->kapasitas * sizeof(Transaksi));
        
        if (keuangan->daftar_transaksi == NULL) {
            printf("Gagal realokasi memori!\n");
            exit(1);
        }
    }

    
    Transaksi *transaksi = &keuangan->daftar_transaksi[keuangan->jumlah_transaksi];
    transaksi->kategori = kategori;
    transaksi->nominal = nominal;
    strcpy(transaksi->tanggal, tanggal);
    transaksi->sumber = sumber;

    keuangan->jumlah_transaksi++;
}


void input_transaksi(ManajemenKeuangan *keuangan) {
    enum KategoriTransaksi kategori;
    float nominal;
    char tanggal[20];
    union SumberDana sumber;
    int pilihan_sumber;

    printf("Masukkan kategori transaksi (0: INFAK_JUMAT, 1: ZAKAT_FITRAH, 2: ZAKAT_MAL, 3: OPERASIONAL_MASJID, 4: KEGIATAN_SOSIAL, 5: PEMBANGUNAN): ");
    scanf("%d", &kategori);
    if (kategori < 0 || kategori > 5) {
        printf("Kategori tidak valid!\n");
        return;
    }
    printf("Masukkan nominal: ");
    scanf("%i", &nominal);
    printf("Masukkan tanggal (DD-MM-YYYY): ");
    scanf("%s", tanggal);
    printf("Pilih sumber dana (1: Donatur, 2: Lembaga, 3: Zakat): ");
    scanf("%d", &pilihan_sumber);

    if (pilihan_sumber == 1) {
        printf("Masukkan nama donatur: ");
        scanf("%s", sumber.donatur);
    } else if (pilihan_sumber == 2) {
        printf("Masukkan nama lembaga: ");
        scanf("%s", sumber.lembaga);
    } else if (pilihan_sumber == 3) {
        printf("Masukkan jenis zakat: ");
        scanf("%s", sumber.zakat);
    } else {
        printf("Pilihan sumber tidak valid!\n");
        return;
    }

    tambah_transaksi(keuangan, kategori, nominal, tanggal, sumber);
}


void output_transaksi(ManajemenKeuangan *keuangan) {
    for (int i = 0; i < keuangan->jumlah_transaksi; i++) {
        Transaksi *transaksi = &keuangan->daftar_transaksi[i];
        printf("Transaksi %d:\n", i + 1);
        printf("Kategori: %d\n", transaksi->kategori);
        printf("Nominal: %.2f\n", transaksi->nominal);
        printf("Tanggal: %s\n", transaksi->tanggal);
        printf("Sumber: ");
        if (transaksi->kategori == ZAKAT_FITRAH || transaksi->kategori == ZAKAT_MAL) {
            printf("%s\n", transaksi->sumber.zakat);
        } else if (transaksi->kategori == OPERASIONAL_MASJID || transaksi->kategori == KEGIATAN_SOSIAL || transaksi->kategori == PEMBANGUNAN) {
            printf("%s\n", transaksi->sumber.lembaga);
        } else {
            printf("%s\n", transaksi->sumber.donatur);
        }
        printf("\n");
    }
}

int main() {
    char nama_masjid[100];
    printf("Masukkan nama masjid: ");
    fgets(nama_masjid, sizeof(nama_masjid), stdin);
   
    nama_masjid[strcspn(nama_masjid, "\n")] = '\0';

    ManajemenKeuangan *keuangan = inisialisasi_keuangan(nama_masjid);

    int pilihan;
    do {
        printf("Menu:\n");
        printf("1. Tambah Transaksi Pemasukan\n");
        printf("2. Tampilkan Transaksi Pemasukan\n");
        printf("3. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                input_transaksi(keuangan);
                break;
            case 2:
                output_transaksi(keuangan);
                break;
            case 3:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while (pilihan != 3);

    
    free(keuangan->daftar_transaksi);
    free(keuangan);

    return 0;
}

