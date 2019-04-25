<?php
// This is the file that the doorbell runs when pressed.
// It sends an email, with the date and time.
// If there is an 'id' on the querystring, the request must have come from a device.
// If not, just print the logs.

date_default_timezone_set("Australia/Hobart");
$filename = "logs/doorbell.log";

if(isset($_GET['id'])) {
    // Construct message
    $text = $_GET['id'] . ": " . date("l jS \of F Y h:i:s A") . "";
    // Send the email
    $to = "me@example.com";
    $from = "doorbell@example.com";
    $subject ="DING DONG!";
    mail($to, "$subject", $text, "From:" .$from);
    // Log the doorbell press to a file
    $file = fopen($filename, 'a');
    fwrite($file, $text."\n"); 
    fclose($file);
}

// Read the file and display the contents
$file = fopen($filename, "r");
$lines = fread($file, filesize($filename));
fclose($file);
echo "<h1>Doorbell</h1>";
echo "<pre>" . $lines . "</pre>";
?>
