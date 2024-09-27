<?php 
define('DB_HOST', 'YAZ_DB_HOST'); 
define('DB_KULLANICI', 'YAZ_DB_KULLANICI'); 
define('DB_PASSWORD', 'YAZ_DB_PASSWORD'); 
define('DB_ISIM', 'YAZ_DB_ISIM');

date_default_timezone_set('Asia/Karachi');

// DB - Veritabanı ile bağlantı kurmak 
$db = new mysqli(DB_HOST, DB_KULLANICI, DB_PASSWORD, DB_ISIM); 
 
// Veritabanın ile bağlatnı başarsız olursa
if ($db->connect_errno) { 
    echo "Bağlantı sağlanamadı ".$db->connect_error;
    exit();
}