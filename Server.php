<?php

class sensor_reading{
 public $link='';
 function __construct($humidity){
  $this->connect();
  $this->storeInDB($humidity);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'capacitive_sensor') or die('Cannot select the DB');
 }
 
 function storeInDB($humidity){
  $query = "insert into sensor_reading set humidity='".$humidity."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}

set_time_limit(30);

$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
	
	socket_bind($socket, "192.168.2.15", 50) or onSocketFailure("Failed to bind to 0.0.0.0:9000", $socket);
	$socket2 = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
	while (true) {
	socket_recvfrom($socket, $buffer, 32768, 0, $ip, $port);
    
	echo $buffer;
	sleep(2);
	if ($buffer.count != 0)
	{
		 $sensor_reading=new sensor_reading($buffer);
		// socket_sendto($socket2 , $buffer , strlen($buffer), 0, "192.168.2.3", 82 );
		 $buffer = "";
	}
	
}
socket_close($socket);
?>