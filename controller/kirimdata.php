<?php

$koneksi = mysqli_connect("localhost", "root", "", "watering_plant");

if ($koneksi->connect_error) {
    die("Connection failed: " . $koneksi->connect_error);
  }
// Membaca sensor dari NodeMCU

$suhu = $_GET['suhu'];
$lembabu = $_GET['kelembapanu'];
$lembabt = $_GET['kelembapant'];


$sql2 = mysqli_query($koneksi, "SELECT * FROM threshold");

$data2 = mysqli_fetch_array($sql2);

$siramo = $data2['siramo'];
$tanahk = $data2['tanahk'];
$normal = $data2['normal'];


if($lembabt >= $siramo) {
    $keterangan = "SIRAM OTOMATIS";
} else if($lembabt >= $tanahk && $lembabt < $siramo) {
    $keterangan = "TANAH KERING";
} else if($lembabt >= $normal && $lembabt < $tanahk) {
    $keterangan = "NORMAL";
} else if($lembabt < $normal) {
    $keterangan = "TANAH BASAH";
}
// Simpan data ke DB

mysqli_query($koneksi, "ALTER TABLE sensordata AUTO_INCREMENT=1");
$simpan = mysqli_query($koneksi, "INSERT INTO sensordata(suhu, kelembapanu, kelembapant, keterangan)values('$suhu', '$lembabu', '$lembabt', '$keterangan')");

if($simpan) {
    echo "Berhasil dikirim";
} else {
    echo "Gagal terkirim";
}
?>