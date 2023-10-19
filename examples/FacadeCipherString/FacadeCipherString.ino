/*
This is a simple example showing how to use the FacadeCipher class to encrypt String messages
*/


#include <FacadeCipher.h>

#define DIRTY_ENC_KEY_LENGTH           19

//Declare a FacadeCipher object
FacadeCipher* myCipher;

//Test encryption key as uint8_t array, useful for thew first constructor
uint8_t encryptionKeyArr[DIRTY_ENC_KEY_LENGTH] = {'V', 'e', 'r', 'y', 'U', 's', 'e', 'l', 'e', 's', 's', 'P', 'a', 's', 's', 'w', 'o', 'r', 'd'};

//Test encryption key as String, useful for the second constructor
String encryptionKeyStr = "VeryUselessPassword";

//Plaintext as String
String plainTxtString = "Not Your Usual Hello World!?_";



void setup() 
{
  Serial.begin(9600);

  //CONSTRUCTOR
  //One constructor receives as input argument the encryption key as uint8_t array and the length of the array
  myCipher = new FacadeCipher(encryptionKeyArr, DIRTY_ENC_KEY_LENGTH);

  //A second constructor receives as input argument the encryption key as String (uncomment the next line to use the second constructor)
  //myCipher = new FacadeCipher(encryptionKeyStr);


  //CHECK THE VALIDITY OF THE ENCRYPTION KEYWORD
  Serial.println("Keyword ok: " + String(myCipher->keyOk));


  //ENCRYPT A STRING MSG
  String encryptedString = myCipher->encryptString(plainTxtString);

  //DECRYPT A STRING MSG
  String decryptedString = myCipher->decryptString(encryptedString);


  //PRINT THE STRING MESSAGES TO THE CONSOLE
  Serial.println("Plaintext string: " + plainTxtString);
  Serial.println("Encrypted string: " + encryptedString);
  Serial.println("Decrypted string: " + decryptedString);


  //DESTRUCTOR
  myCipher->~FacadeCipher();
}

void loop()
{
}
