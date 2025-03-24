<?php
// Database connection
$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "dormcheck";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Database Connection failed: " . $conn->connect_error);
}

// Get parameters from URL
if (!empty($_GET['cardid'])) {
    $cardid = $_GET['cardid'];

    // Check if card exists in ACCESSCARD table
    $sql = "SELECT cardid FROM ACCESSCARD WHERE cardid = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $cardid);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        echo "1"; // Card exists
    } else {
        echo "0"; // Card does not exist
    }

    $stmt->close();
} else {
    echo "Missing cardid";
}

$conn->close();
?>