
<?php
// Enable error reporting for debugging
ini_set('display_errors', 1);
error_reporting(E_ALL);

// Database connection
$servername = "localhost";

// REPLACE with your Database name
$dbname = "dormcheck";
// REPLACE with Database user
$username = "root";
// REPLACE with Database user password
$password = "MilkaCsoki22";
$conn = new mysqli($servername, $username, $password, $dbname);

// Check for connection errors
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);  // Display connection error
}

// Check if cardid is provided
if (!empty($_GET['cardid'])) {
    $cardid = $_GET['cardid'];

    // Log the incoming cardid for debugging
    error_log("Received cardid: " . $cardid);

    // Check if card exists in ACCESSCARD
    $sql = "SELECT cardid FROM ACCESSCARD WHERE cardid = ?";
    $stmt = $conn->prepare($sql);
    if (!$stmt) {
        error_log("Prepare failed for card existence check: " . $conn->error);  // Log any preparation issues
        die("-2");
    }
    $stmt->bind_param("s", $cardid);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows == 0) {
        // Log unauthorized card access attempt (card does not exist in ACCESSCARD)
        log_event($cardid, -1, "UNAUTHORIZED - Card does not exist");
        echo "0"; // Card does not exist
        $stmt->close();
        $conn->close();
        exit();
    }
    $stmt->close();

    // Card exists, now check if it is assigned and valid
    $sql = "SELECT userid FROM ASSIGNMENT WHERE cardid = ? AND valid_start <= CURDATE() AND valid_end >= CURDATE()";
    $stmt = $conn->prepare($sql);
    if (!$stmt) {
        error_log("Prepare failed for assignment check: " . $conn->error);  // Log any preparation issues
        die("-2");
    }
    $stmt->bind_param("s", $cardid);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        // Card is authorized (assigned to a user and within valid dates)
        $row = $result->fetch_assoc();
        $userid = $row['userid'];
        log_event($cardid, $userid, "AUTHORIZED");  // Log authorized event
        echo "1"; // Authorized card
    } else {
        // Card is not assigned to any user but exists in the database
        log_event($cardid, -1, "UNAUTHORIZED");
        echo "0"; // No valid assignment
    }

    $stmt->close();
} else {
    echo "-2"; // Missing cardid
}

$conn->close();

// Function to log events into the CARDCHECKS table
function log_event($cardid, $userid, $event_type) {
    global $conn;

    // Check if the cardid exists in the ACCESSCARD table before logging the event
    $sql_check = "SELECT cardid FROM ACCESSCARD WHERE cardid = ?";
    $stmt_check = $conn->prepare($sql_check);
    $stmt_check->bind_param("s", $cardid);
    $stmt_check->execute();
    $result_check = $stmt_check->get_result();

    if ($result_check->num_rows > 0) {
        // Card exists in ACCESSCARD, proceed with logging
        $sql = "INSERT INTO CARDCHECKS (cardid, userid, cevent, check_time)
                VALUES (?, ?, ?, NOW())";  // Using NOW() for current timestamp
        $stmt = $conn->prepare($sql);

        if ($stmt) {
            // Bind parameters based on event type
            $stmt->bind_param("sis", $cardid, $userid, $event_type); // Pass the event type as a string

            // Execute the query and check if it was successful
            if ($stmt->execute()) {
                error_log("Logged event: cardid = " . $cardid . ", userid = " . $userid . ", event = " . $event_type);
            } else {
                error_log("Failed to log event for cardid: " . $cardid . " Error: " . $stmt->error);
            }
            $stmt->close();
        } else {
            error_log("Prepare failed for logging event for cardid: " . $cardid . " Error: " . $conn->error);
        }
    } else {
        // Card does not exist, directly insert with 'UNKNOWN' and '-1' userid for UNAUTHORIZED
        $sql = "INSERT INTO CARDCHECKS (cardid, userid, cevent, check_time)
                VALUES ('UNKNOWN', -1, 'UNAUTHORIZED', NOW())";  // Insert for unknown card
        $stmt = $conn->prepare($sql);

        if ($stmt) {
            // Execute the query and check if it was successful
            if ($stmt->execute()) {
                error_log("Logged event for unknown card: cardid = UNKNOWN, userid = -1, event = UNAUTHORIZED");
            } else {
                error_log("Failed to log event for unknown card Error: " . $stmt->error);
            }
            $stmt->close();
        } else {
            error_log("Prepare failed for logging event for unknown card Error: " . $conn->error);
        }
    }

    $stmt_check->close();
}
?>
