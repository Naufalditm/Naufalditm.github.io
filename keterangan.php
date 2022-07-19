<?php

require_once "config.php";

// Membaca sensor dari tabel
$sql = mysqli_query($koneksi, "SELECT * FROM sensordata 
        ORDER BY id DESC");

$data = mysqli_fetch_array($sql);

$keterangan = $data['keterangan'];


// Cetak nilai keterangan
echo $keterangan;



?>