<?php

// require_once "config.php";

// Membaca sensor dari tabel
// $sql = mysqli_query($koneksi, "SELECT * FROM sensordata 
//         ORDER BY id DESC");
// $sql2 = mysqli_query($koneksi, "SELECT * FROM threshold 
//         ORDER BY id DESC");

// $data = mysqli_fetch_array($sql);
// $data2 = mysqli_fetch_array($sql2);


// $kelembapant = $data['kelembapant'];
// $keterangan = $data['keterangan'];
// $siramo = $data2['siramo'];
// $tanahk = $data2['tanahk'];
// $normal = $data2['normal'];

// if($kelembapant >= $siramo) {
//     $keterangan = "SIRAM OTOMATIS";
// } else if($kelembapant >= $tanahk && $kelembapant < $siramo) {
//     $keterangan = "TANAH KERING";
// } else if($kelembapant >= $normal && $kelembapant < $tanahk) {
//     $keterangan = "NORMAL";
// } else if($kelembapant < $normal) {
//     $keterangan = "TANAH BASAH";
// }

// Cetak nilai keterangan
// echo $keterangan;



?>