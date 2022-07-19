<?php

require_once "config.php";

// Membaca sensor dari tabel
$sql = mysqli_query($koneksi, "SELECT * FROM sensordata 
        ORDER BY id DESC");

$data = mysqli_fetch_array($sql);
$kelembapant = $data['kelembapant'];

// Debug nilai kelembaban tanah belum ada, maka kelembaban tanah 0
if($kelembapant == "") {
    $kelembapant = 0;
}
// Cetak nilai kelembaban tanah
echo $kelembapant;
?>