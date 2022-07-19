<?php

require_once "config.php";

// Membaca sensor dari tabel
$sql = mysqli_query($koneksi, "SELECT * FROM sensordata 
        ORDER BY id DESC");

$data = mysqli_fetch_array($sql);
$kelembapanu = $data['kelembapanu'];

// Debug nilai kelembapan udara belum ada, maka kelembapan udara 0
if($kelembapanu == "") {
    $kelembapanu = 0;
}
// Cetak nilai kelembapan udara
echo $kelembapanu;
?>