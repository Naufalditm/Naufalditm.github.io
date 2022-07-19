<?php

require_once "config.php";


$sql = mysqli_query($koneksi, "SELECT * FROM threshold 
        ORDER BY id DESC");

$data = mysqli_fetch_array($sql);
$tanahk = $data['tanahk'];

if($tanahk == "") {
    $tanahk = 0;
}

echo $tanahk;
?>