<?php
$data = "000";
echo $socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
//echo socket_bind($socket, "127.0.0.1", 82) or onSocketFailure("Failed to bind to 192.168.2.57:82", $socket);

//echo socket_sendto($socket, $data , strlen($data), 0, "192.168.2.94", 82 );

echo socket_sendto($socket, $data , strlen($data), 0, "192.168.43.216", 2500 );

?>