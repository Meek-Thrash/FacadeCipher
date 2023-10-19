/*
This is a simple example showing how to use the FacadeCipher class to encrypt and decrypt messages coded as uint8_t arrays
*/


#include <FacadeCipher.h>

#define DIRTY_ENC_KEY_LENGTH           19

//Declare a FacadeCipher object
FacadeCipher* myCipher;

//Test encryption key as uint8_t array, useful for the first constructor of the FacadeCipher class
uint8_t encryptionKeyArr[DIRTY_ENC_KEY_LENGTH] = {'V', 'e', 'r', 'y', 'U', 's', 'e', 'l', 'e', 's', 's', 'P', 'a', 's', 's', 'w', 'o', 'r', 'd'};

//Test encryption key as String, useful for the second costructor
String encryptionKeyStr = "VeryUselessPassword";

//Plaintext as uint8_t array
uint8_t plainTxtArr[29] = {'N', 'o', 't', ' ', 'y', 'o', 'u', 'r', ' ', 'u', 's', 'u', 'a', 'l', ' ', 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '?', '_'};



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



  //CALCULATE THE LENGTH OF THE PADDING FOR plainTxtArr TO BE OK WITH THE BLOCKSIZE OF THE CIPHER
  int missingBlocks = myCipher->blockSize - (sizeof(plainTxtArr) % myCipher->blockSize);
  int paddedMsgLen = sizeof(plainTxtArr) + missingBlocks;

  //CREATE A uint8_t ARRAY TO STORE THE ENCRYPTED MSG; THE SIZE OF THE ARRAY IS THE FIRST MULTIPLE OF THE BLOCK SIZE GREATER THEN THE plainTxtArr SIZE
  uint8_t encrypted[paddedMsgLen] = {};


  //ENCRYPT THE WHOLE MESSAGE
  myCipher->encrypt(plainTxtArr, sizeof(plainTxtArr), encrypted, paddedMsgLen);


  //CREATE A uint8_t ARRAY TO STORE THE DECRYPTED MSG; THE SIZE OF THE ARRAY IS THE SAME AS THE ENCRYPTED MESSAGE
  uint8_t decrypted[paddedMsgLen] = {};

  //DECRYPT THE WHOLE MESSAGE
  myCipher->decrypt(encrypted, paddedMsgLen, decrypted);



  //PRINTING THE MESSAGES TO THE CONSOLE

  //Print plaintext
  Serial.print("Plaintext:");
  for(int i = 0; i< sizeof(plainTxtArr); i++)
    Serial.print(plainTxtArr[i]);
  Serial.println(";");

  //Print the encrypted message
  Serial.print("Encrypted message:");
  for(int i = 0; i< sizeof(encrypted); i++)
    Serial.print(encrypted[i]);
  Serial.println(";");

  //Print the WHOLE decrypted message
  Serial.print("Integral decrypted message (contains padding characters):");
  //ITERATING FROM 0 TO paddedMsgLen WILL PRINT TO CONSOLE EVEN THE PADDING CHARACTERS
  for(int i = 0; i< paddedMsgLen; i++)                              
    Serial.print(decrypted[i]);
  Serial.println(";");

  //Print the decrypted message keeping the original length of the inMsg
  Serial.print("Decrypted message same as the input msg:");
  //TO KEEP THE LENGTH OF THE ORIGINAL MSG WITHOUT THE PADDING CHARS YOU HAVE TO ITERATE FROM 0 TO sizeof(plainTxtArr)
  for(int i = 0; i< sizeof(plainTxtArr); i++)                             
    Serial.print(decrypted[i]);
  Serial.println(";");

  //DESTRUCTOR
  myCipher->~FacadeCipher();
}

void loop()
{
}
