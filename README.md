# Sliding Window
## Petunjuk penggunaan program.
1.
2.

## Cara kerja sliding window dalam program anda. 
Jelaskan juga fungsi yang terkait dengan sliding window pada program anda dan apa yang dilakukan oleh fungsi tersebut.

## Pembagian tugas. 
Sampaikan dalam list pengerjaan untuk setiap mahasiswa. Sebagai contoh: XXXX mengerjakan fungsi YYYY, ZZZZ, dan YYZZ.


## Jawaban Pertanyaan
1. Apa yang terjadi jika advertised window yang dikirim bernilai 0? Apa cara untuk
menangani hal tersebut?  

2. Sebutkan field data yang terdapat TCP Header serta ukurannya, ilustrasikan, dan jelaskan kegunaan dari masing-masing field data tersebut! 

![TCP header](TCPheader.png)

* Source TCP port number (2 bytes) : untuk menyimpan nomor port asal
* Destination TCP port number (2 bytes) : untuk menyimpan nomor port tujuan
* Sequence number (4 bytes) : untuk menandai urutan kelompok pesan
* Acknowledgment number (4 bytes) : untuk meyimpan sequence number dari data yang akan diterima receiver atau yang akan dikirim sender berikutnya
* TCP data offset (4 bits) : untuk mengindikasikan dimana data dimulai.
* Reserved data (6 bits) : untuk reservasi penggunaan mendatang - selalu berisi nol
* Control flags (6 bits) : untuk mengatur data flow pada situasi tertentu
** URG : untuk menentukan apakah urgent pointer diabaikan atau tidak
** ACK : untuk menentukan apakah acknowledgement diabaikan atau tidak
** PSH : untuk memulai fungsi push
** RST : untuk memaksa koneksi di reset
** SYN : untuk melakukan sinkronisasi sequence number
** FIN : untuk mengindikasikan tidak ada lagi data dari sender
* Window size (2 bytes) : untuk menyimpan jumlah data yang dikirimkan sender sebelum menerima ACK
* TCP checksum (2 bytes) : untuk memeriksa integritas segmen
* Urgent pointer (2 bytes) : untuk menandakan lokasi data yang dianggap penting dalam segmen
* TCP optional data (0-40 bytes) : untuk memyimpan beberapa opsi tambahan TCP