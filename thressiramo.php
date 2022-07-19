<?php

require_once "config.php";


$sql = mysqli_query($koneksi, "SELECT * FROM threshold 
        ORDER BY id DESC");

$data = mysqli_fetch_array($sql);
$siramo = $data['siramo'];

if($siramo == "") {
    $siramo = 0;
}

echo $siramo;
?>