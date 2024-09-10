# Program pengelolaan buku sederhana

# Inisialisasi daftar buku
book_list = []

# Fungsi untuk menambah buku
def add_book(title, author):
    book = {
        'title': title,
        'author': author
    }
    book_list.append(book)
    print(f"Buku '{title}' oleh {author} telah ditambahkan!")

# Fungsi untuk menampilkan daftar buku
def view_books():
    if len(book_list) == 0:
        print("Belum ada buku yang ditambahkan.")
    else:
        print("\nDaftar Buku:")
        for idx, book in enumerate(book_list, 1):
            print(f"{idx}. {book['title']} oleh {book['author']}")

# Fungsi untuk menghapus buku berdasarkan indeks
def delete_book(index):
    if index <= 0 or index > len(book_list):
        print("Indeks buku tidak valid.")
    else:
        removed_book = book_list.pop(index - 1)
        print(f"Buku '{removed_book['title']}' oleh {removed_book['author']} telah dihapus!")

# Fungsi utama untuk menampilkan menu
def main_menu():
    while True:
        print("\n--- Menu Pengelolaan Buku ---")
        print("1. Tambah Buku")
        print("2. Lihat Daftar Buku")
        print("3. Hapus Buku")
        print("4. Keluar")
        
        choice = input("Pilih opsi (1-4): ")
        
        if choice == '1':
            title = input("Masukkan judul buku: ")
            author = input("Masukkan nama penulis: ")
            add_book(title, author)
        elif choice == '2':
            view_books()
        elif choice == '3':
            view_books()
            if len(book_list)

