<?php

require_once "config.php";

// Membaca sensor dari tabel
$sql = mysqli_query($koneksi, "SELECT * FROM sensordata 
        ORDER BY id DESC");

$data = mysqli_fetch_array($sql);
$suhu = $data['suhu'];

// Debug nilai suhu belum ada, maka suhu 0
if($suhu == "") {
    $suhu = 0;
}
// Cetak nilai suhu
echo $suhu;
?>