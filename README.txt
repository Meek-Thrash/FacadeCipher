This is a facade for a simpler use of the AES256 class from the Arduino Cryptography Library 
developed by Rhys Weatherley: https://rweather.github.io/arduinolibs/crypto.html;
This facade class works ONLY with the AES256 class of the Arduino Cryptographic Library.

THIS CLASS IS A FACADE SO TO USE IT YOU NEED TO INSTALL SOME HEADER FILE FROM THE ARDUINO CRYPTOGRAPHIC LIBRARY
(https://rweather.github.io/arduinolibs/crypto.html);
ESPECIALLY YOU NEED TO MANUALLY ADD TO YOUR ARDUINO LIBRARIES THE FOLLOWING FILES:

AES.h				        https://rweather.github.io/arduinolibs/AES_8h_source.html
AES256.cpp			    https://rweather.github.io/arduinolibs/AES256_8cpp_source.html
AESCommon.cpp		    https://rweather.github.io/arduinolibs/AESCommon_8cpp_source.html
BlockCipher.cpp		  https://rweather.github.io/arduinolibs/BlockCipher_8cpp_source.html
BlockCipher.h		    https://rweather.github.io/arduinolibs/BlockCipher_8h_source.html
Crypto.cpp			    https://rweather.github.io/arduinolibs/Crypto_8cpp_source.html
Crypto.h			      https://rweather.github.io/arduinolibs/Crypto_8h_source.html
ProgMemUtil.h		    https://github.com/rweather/arduinolibs/blob/master/libraries/Crypto/utility/ProgMemUtil.h



Instead of encrypting and decrypting every block manually this class encrypts and decrypts the whole
plaintext/encrypted message; this class provides two functions to encrypt and decrypt String messages, too.
In addition this class provides two different constructors to create a FacadeCipher object passing as 
argument a String encryption key rather the a uint8_t array encryption key;
both constructors create a 256 bit "cleaned" encryption key starting from the encryption key passed as
argument to the constructor.

I'm not really a cryptography expert but I had to use the Arduino Cryptography Library for a project
and I thought it would have been great to encrypt and decrypt the whole message with just one function;
then i thought I would have appreciated to encrypt and decrypt String messages and managing String encryption
keys as well as uint8_t array encryption keys.






DOCUMENTATION:

The class provides two constructors;
One constructor receives as input a pointer to a uint8_t array containing the encryption key provided by the user
and the length of the "dirty" encryption key;
the encryption key is processed to be a 32 byte key (this facade works only with with AES256!).
The constructor initialises an AES256 object and set the password;
a global variable keyOk is set to true or false if the initialisation is gone ok or wrong.
in the constructor the block size of the cipher is extracted, too.

The second constructor does the same things, but receives a String as input containing the "dirty"
encryption key;

The destructor clears all the sensitive data;

The encrypt function receives as input a pointer to a uint8_t array containing the plaintext, the size of the array containing the plaintext, 
a uint8_t array to store the encrypted message and the length of the array to sotre the encrypted message; the encrypted message
could be longer then the plaintext because of padding values: internally the function pads the message with 0s until 
the length of the message is a multiple of the block size of the cipher.

The decrypt function receives as input a pointer to a uint8_t array containing the encrypted message, the size of the array containing the encrypted
message and a uint8_t array to store the decrypted message; the length of the array to store the decrypted message
is the same size of the encrypted message -> is taken for granted that the encrypted message is already padded to be ok
with the block size of the cipher.

The function encryptString receives as input a String containing the plaintext and returns a String containing
the encrypted message;

the decryptString function receives as input a String containing the encrypted message and returns a String containing
the decrypted message.
