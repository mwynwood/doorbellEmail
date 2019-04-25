# doorbellEmail
When the doorbell is pressed, an email is sent.

Using a $9 doorbell from Bunnings, a $6 Wemos D1 Mini, a soldering iron, and C++, my doorbell now sends an email.

One side of the LED in the doorbell connects to Pin3 of the Wemos D1 Mini. When the doorbell goes off, the the Wemos D1 Mini detects the flashing LED and sends a GET request off to "doorbell.php", which logs it and sends an email.
