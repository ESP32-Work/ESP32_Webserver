<?php

$servername = "";
$dbname = "";
$username = "";
$password = "";

$api_key_value = "";
$api_key = $sensor	= $location	= $value1	= $value2	= $value3	= $reading_time = "";

// Check if the request method is POST
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value){ 
    // Retrieve the data from the request body
        $sensor = test_input($_POST["sensor"]);
        $location = test_input($_POST["location"]);
        $value1 = test_input($_POST["value1"]);
        $value2 = test_input($_POST["value2"]);
        $value3 = test_input($_POST["value3"]);
    
    // Perform any necessary data validation or sanitization

    //create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        if($conn->connect_error){
            die("Connection failed: " . $conn->connect_error);
        }

        $sql = "INSERT INTO ESPData (SensorData, LocationData, value1, value2, value3)
        VALUES ('".$sensor."', '".$location."', '".$value1."', '".$value2."', '".$value3."')";

        if ($conn->query($sql)  == TRUE){
            echo "New record created";
        }
        else {
            echo "Error: " .$sql . "<br>" . $conn->error;
        }

        $conn->close();
    }
    else {
        echo "Wrong api key";
    }
}
else {
    echo "No data posted";
}

function test_input($data){
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
?>