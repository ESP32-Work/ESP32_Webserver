#include <ESP_Mail_Client.h>
#include <WiFi.h>

const char* ssid = "";
const char* password = "";

#define emailReciever ""
#define emailPassword ""
#define emailAccount ""
#define emailServer "smtp.gmail.com"
#define emailServerPort 465

// Declare the global used SMTPSession object for SMTP transport
SMTPSession smtp;

// Declare the global used Session_Config for user defined session credentials
Session_Config config;

// Callback function to get the Email sending status
void smtpCallback(SMTP_Status status);

void setup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Set the session config
  config.server.host_name = emailServer; 
  config.server.port = emailServerPort; // for TLS with STARTTLS or 25 (Plain/TLS with STARTTLS) or 465 (SSL)
  config.login.email = emailAccount;
  config.login.password = emailPassword;
  config.login.user_domain = F("127.0.0.1");

  config.time.ntp_server =  F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 5;
  config.time.day_light_offset = 0;

  // Declare the SMTP_Message class variable to handle to message being transport
  SMTP_Message message;

  // Set the message headers
  message.sender.name = "Ibrahim";
  message.sender.email = emailAccount;
  message.subject = "Test sending Email";
  message.addRecipient("Ali Ahmed", emailReciever);
  // message.addRecipient("name2", "email2");

  // message.addCc("email3");
  // message.addBcc("email4");

  // Set the message content
  message.text.content = "This is simple plain text message";


  // Declare the attachment data
  SMTP_Attachment att;

  // Set the attatchment info
  att.descr.filename = "/home/ibrahim/Pictures/Screenshots/dronetakeoff.png";

  // Set the transfer encoding to base64
  att.descr.transfer_encoding = Content_Transfer_Encoding::enc_base64;
  // We set the content encoding to match the above greenImage data
  att.descr.content_encoding = Content_Transfer_Encoding::enc_base64;

  // Add attachment to the message
  message.addAttachment(att);

  // Set debug option
  smtp.debug(1);

  // Set the callback function to get the sending results
  smtp.callback(smtpCallback);

  // Connect to the server
  smtp.connect(&config);

  // Start sending Email and close the session
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

}

void smtpCallback(SMTP_Status status)
{
 
  Serial.println(status.info());

  if (status.success())
  {
    Serial.println("Message sent successfuly");
  }
}


void loop(){
  // Do nothing
}