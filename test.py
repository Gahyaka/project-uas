def add_book(title, author):
    book = {
        'title': title,
        'author': author
    }
    book_list.append(book)
    print(f"Buku '{title}' oleh {author} telah ditambahkan!")
